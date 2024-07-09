#include "main.h"

GameServer::GameServer(QObject *parent)
    : QTcpServer(parent)
{
    // Initialize game state with example entities
    gameState = QJsonArray();
    for(int i = 0; i < 22; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            game_field[i][j] = 0;
        }
    }
}

void GameServer::startGameServer()
{
    if (listen(QHostAddress::Any, 8080)) {
        qDebug() << "Game server started on port 8080";
    } else {
        qDebug() << "Game server failed to start";
    }
}

void GameServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    if (socket->setSocketDescriptor(socketDescriptor)) {
        clients.append(socket);
        clientMap[socketDescriptor] = socket;
        connect(socket, &QTcpSocket::readyRead, this, &GameServer::readyRead);
        connect(socket, &QTcpSocket::disconnected, this, &GameServer::clientDisconnected);
        qDebug() << "New client connected with descriptor:" << socketDescriptor;
    } else {
        qDebug() << "Failed to set socket descriptor:" << socket->errorString();
        delete socket;
    }
}

void GameServer::readyRead()
{
    qDebug() << "data cathced";
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket) return;

    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject request = doc.object();

    processRequest(socket, request);
}

void GameServer::processRequest(QTcpSocket *socket, const QJsonObject &request)
{
    qDebug() << "processRequest called with socket:" << socket << "and request:" << request;

    QString action = request["action"].toString();
    qDebug() << "Action parsed from request:" << action;

    if (action == "add")
    {
        double doubleValue = request["x"].toDouble();
        int x = static_cast<int>(doubleValue);

        doubleValue = request["y"].toDouble();
        int y = static_cast<int>(doubleValue);

        doubleValue = request["character"].toDouble();
        int character = static_cast<int>(doubleValue);

        qDebug() << "The add action called";
        QJsonObject newEntity = request["entity"].toObject();
        qDebug() << "New entity parsed from request:" << newEntity;
        gameState.append(newEntity);
        qDebug() << "New entity added to game state, broadcasting updated game state";
        broadcastGameState();

        qDebug() << "before change : " << game_field[x][y];
        if(game_field[request["x"].toInt()][request["y"].toInt()] == 0)
        {
            game_field[x][y] = character;
            QJsonObject gameStateUpdate;
            gameStateUpdate["action"] = "add_char";
            gameStateUpdate["character"] = request["character"];
            gameStateUpdate["x"] = request["x"];
            gameStateUpdate["y"] = request["y"];
            gameStateUpdate["game_state"]=gameState;
            qDebug() << "send data";
            QJsonDocument responseDoc(gameStateUpdate);
            QByteArray responseData = responseDoc.toJson();
            socket->write(responseData);
            socket->flush();
        }
    }
    else {
        qDebug() << "Unknown action received:" << action;
    }

    qDebug() << "processRequest completed for socket:" << socket;
}

void GameServer::sendGameStateToClient(QTcpSocket *socket)
{
    QJsonObject gameStateUpdate;
    gameStateUpdate["action"] = "update";
    gameStateUpdate["game_state"] = gameState;

    QJsonDocument responseDoc(gameStateUpdate);
    QByteArray responseData = responseDoc.toJson();
    socket->write(responseData);
    socket->flush();
}

void GameServer::broadcastGameState()
{
    QJsonObject gameStateUpdate;
    gameStateUpdate["action"] = "update";
    gameStateUpdate["game_state"] = gameState;

    QJsonDocument responseDoc(gameStateUpdate);
    QByteArray responseData = responseDoc.toJson();
    for (QTcpSocket *client : clients) {
        client->write(responseData);
        client->flush();
    }
}

void GameServer::clientDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket) return;

    clients.removeOne(socket);
    clientMap.remove(socket->socketDescriptor());
    socket->deleteLater();
    qDebug() << "Client disconnected";
}

void GameServer::updateGameState()
{
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    for (int i = 0; i < gameState.size(); ++i) {
        QJsonObject entity = gameState[i].toObject();

        if (entity["type"].toString() == "zombie") {
            qint64 lastMove = entity["last_move"].toVariant().toLongLong();
            int moveDelay = entity["move_delay"].toInt();

            if (currentTime - lastMove >= moveDelay) {
                // Update zombie position
                entity["x"] = entity["x"].toInt() - 1;
                entity["last_move"] = currentTime;

                // Update the game state array
                gameState[i] = entity;
            }
        }
    }

    // Broadcast updated game state to all clients
    broadcastGameState();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    GameServer server;
    server.startGameServer();

    // Periodically update game state
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &server, &GameServer::updateGameState);
    timer.start(1000); // Update every second

    return a.exec();
}

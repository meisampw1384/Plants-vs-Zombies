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
    mainTimer=new QTimer(this);
    sunTimer=new QTimer(this);
    brainTimer=new QTimer(this);
    connect(mainTimer, &QTimer::timeout, this, &GameServer::updateGameState);
    connect(sunTimer, &QTimer::timeout, this, &GameServer::add_sun);
    connect(brainTimer, &QTimer::timeout, this, &GameServer::add_brain);
}

void GameServer::startGameServer()
{
    if (listen(QHostAddress::Any, 8080)) {
        qDebug() << "Game server started on port 8080";
    } else {
        qDebug() << "Game server failed to start";
    }
}
GameServer server;


void GameServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    if (socket->setSocketDescriptor(socketDescriptor)) {
        clients.append(socket);
        clientMap[socketDescriptor] = socket;
        mainTimer->start(1000); // Update every second
        sunTimer->start(5000);  // Add sun every 5 seconds
        brainTimer->start(5000);


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
    else if (action == "delete")
    {
        QString type = request["type"].toString();
        int x = request["x"].toInt();
        int y = request["y"].toInt();

        if (type == "sun" || type == "brain")
        {
            // Find and remove the entity from gameState
            for (int i = 0; i < gameState.size(); ++i) {
                QJsonObject entity = gameState[i].toObject();
                if (entity["type"].toString() == type &&
                    entity["x"].toInt() == x &&
                    entity["y"].toInt() == y) {
                    qDebug()<<"deleted"<<entity;
                    gameState.removeAt(i);
                    qDebug() << "Removed" << type << "at" << x << "," << y;
                    broadcastGameState();
                    break;
                    // Assuming only one entity per position
                }
            }
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
//broadcast of the  update of the map
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



void GameServer::add_sun()
{
    int x = QRandomGenerator::global()->bounded(2, 7);
    int y = QRandomGenerator::global()->bounded(1, 6); // Assuming y ranges from 1 to 6

    // Create the sun entity
    QJsonObject sun;
    sun["type"] = "sun";
    sun["x"] = x;
    sun["y"] = y;
    sun["value"] = 25;
    sun["timestamp"] = QDateTime::currentMSecsSinceEpoch();

    // Add the sun entity to the game state
    gameState.append(sun);

    broadcastGameState();
}
void GameServer::add_brain()
{
    int x = QRandomGenerator::global()->bounded(8, 11);
    int y = QRandomGenerator::global()->bounded(1, 6); // Assuming y ranges from 1 to 6

    QJsonObject brain;
    brain["type"] = "brain";
    brain["x"] = x;
    brain["y"] = y;
    brain["value"] = 25;
    brain["timestamp"] = QDateTime::currentMSecsSinceEpoch();


    gameState.append(brain);

    broadcastGameState();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    server.startGameServer();

    // Periodically update game state
 // Update every second

    return a.exec();
}

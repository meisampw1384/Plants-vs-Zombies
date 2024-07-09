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
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket) return;

    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject request = doc.object();

    processRequest(socket, request);
}

void GameServer::processRequest(QTcpSocket *socket, const QJsonObject &request)
{
    QString action = request["action"].toString();

    if (action == "add")
    {
        double doubleValue = request["x"].toDouble();
        int x = static_cast<int>(doubleValue);

        doubleValue = request["y"].toDouble();
        int y = static_cast<int>(doubleValue);

        QJsonObject entity = request["entity"].toObject();
        doubleValue = entity["id"].toDouble();
        int ID = static_cast<int>(doubleValue);

        QJsonObject newEntity = request["entity"].toObject();
        gameState.append(newEntity);
        broadcastGameState();

        if(game_field[request["x"].toInt()][request["y"].toInt()] == 0)
        {
            game_field[x][y] = ID;
            qDebug() << "ID in game field : " << game_field[x][y];
            QJsonObject gameStateUpdate;
            gameStateUpdate["action"] = "add_char";
            gameStateUpdate["character"] = request["character"];
            gameStateUpdate["x"] = request["x"];
            gameStateUpdate["y"] = request["y"];
            gameStateUpdate["game_state"]=gameState;
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
                    gameState.removeAt(i);
                    qDebug() << "Removed" << type << "at" << x << "," << y;
                    broadcastGameState();
                    break;  // Assuming only one entity per position
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

        if (entity["type"].toString() == "zombie")
        {
            if(entity["health"].toInt() < 0)
            {
                gameState.removeAt(i);
                continue;
            }
            qint64 lastMove = entity["last_move"].toVariant().toLongLong();
            int moveDelay = entity["move_delay"].toInt();
            double doubleValue = entity["x"].toDouble();
            int x = static_cast<int>(doubleValue);

            doubleValue = entity["y"].toDouble();
            int y = static_cast<int>(doubleValue);

            if(entity["x"].toInt() - 1 != 1)
            {
                if(game_field[x - 1][y] == 0)
                {
                    if (currentTime - lastMove >= moveDelay){
                        // Update zombie position
                        entity["x"] = entity["x"].toInt() - 1;
                        entity["last_move"] = currentTime;

                        doubleValue = entity["id"].toDouble();
                        int ID = static_cast<int>(doubleValue);

                        game_field[x][y] = 0;
                        game_field[x - 1][y] = ID;

                        // Update the game state array
                        gameState[i] = entity;
                    }
                }
                else
                {
                    if (currentTime - lastMove >= moveDelay)
                    {
                        for (int i = 0; i < gameState.size(); ++i)
                        {
                            QJsonObject find = gameState[i].toObject();

                            double doubleValue = find["id"].toDouble();
                            int check_id = static_cast<int>(doubleValue);

                            if(check_id == game_field[x - 1][y] and find["type"] == "plant")
                            {
                                find["health"] = find["health"].toInt() - entity["damage"].toInt();
                                gameState[i] = find;
                                break;
                            }

                        }
                    }

                }
            }
        }

        else if(entity["type"].toString() == "plant")
        {
            if(entity["health"].toInt() < 0)
            {
                gameState.removeAt(i);

                double doubleValue = entity["x"].toDouble();
                int x = static_cast<int>(doubleValue);

                doubleValue = entity["y"].toDouble();
                int y = static_cast<int>(doubleValue);

                game_field[x][y] = 0;
                continue;
            }
//            if(entity["subtype"] == "boomerang")
//            {

//            }
//            else if(entity["subtype"] == "jalpeno")
//            {

//            }
//            else if(entity["subtype"] == "peashooter")
//            {

//            }
//            else if(entity["subtype"] == "twopeashooter")
//            {

//            }
//            else if(entity["subtype"] == "walnut")
//            {

//            }
//            else if(entity["subtype"] == "plummine")
//            {

//            }
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
    GameServer server;
    server.startGameServer();

    // Periodically update game state
    QTimer timer;

    QTimer sun_timer;
    QObject::connect(&sun_timer,&QTimer::timeout,&server,&GameServer::add_sun);
    sun_timer.start(5000);

    QTimer brain_timer;
    QObject::connect(&brain_timer,&QTimer::timeout,&server,&GameServer::add_brain);
    brain_timer.start(5000);

    QObject::connect(&timer, &QTimer::timeout, &server, &GameServer::updateGameState);

    timer.start(1000); // Update every second

    return a.exec();
}

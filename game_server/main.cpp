#include "main.h"

GameServer::GameServer(QObject *parent)
    : QTcpServer(parent)
{
    // Initialize game state with example entities
    gameState = QJsonArray();
    bullets_COOR = QJsonArray();
    clientRoleCounter=0;
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
    updateTimer = new QTimer(this);

    connect(mainTimer, &QTimer::timeout, this, &GameServer::TIME_broadcaster);
    connect(sunTimer, &QTimer::timeout, this, &GameServer::add_sun);
    connect(brainTimer, &QTimer::timeout, this, &GameServer::add_brain);
    connect(updateTimer, &QTimer::timeout, this, &GameServer::updateGameState);
    remainingTime = 210;
}

void GameServer::TIME_broadcaster()
{
    remainingTime --;
    QJsonObject request;
    request["action"] ="time";
    request["remaining"]=remainingTime;

    QJsonDocument doc(request);
    QByteArray data = doc.toJson();

    for (QTcpSocket *client : clients) {
        client->write(data);
        client->flush();
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
    QTcpSocket *new_socket = new QTcpSocket(this);
    if (new_socket->setSocketDescriptor(socketDescriptor)) {
        clients.append(new_socket);
        qDebug() << "New client connected with descriptor:" << socketDescriptor;

        // Assign roles to clients
        if (clientRoleCounter == 0) {
            clientRoles[new_socket] = "zombie";
            qDebug() << "Client assigned to control zombies.";
        } else if (clientRoleCounter == 1) {
            clientRoles[new_socket] = "plant";
            qDebug() << "Client assigned to control plants.";
        }

        clientRoleCounter++;

        if (clients.size() == 2) {
            mainTimer->start(1000); // Update every second
            sunTimer->start(5000);  // Add sun every 5 seconds
            brainTimer->start(5000); // Add brain every 5 seconds
            updateTimer->start(1000);
        }

        connect(new_socket, &QTcpSocket::readyRead, this, &GameServer::readyRead);
        connect(new_socket, &QTcpSocket::disconnected, this, &GameServer::clientDisconnected);
        connect(new_socket, &QTcpSocket::connected, this, [=]() {
            qDebug() << "Socket connected with descriptor:" << socketDescriptor;
        });
    } else {
        qDebug() << "Failed to set socket descriptor:" << new_socket->errorString();
        delete new_socket;
    }
}

void GameServer::readyRead()
{
    socket = qobject_cast<QTcpSocket *>(sender());
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
    if ((entity["type"]=="plant"&&clientRoles[socket]=="plant") || (entity["type"]=="zombie"&&clientRoles[socket]=="zombie")){
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
    }

    else if (action == "delete")
    {
        QString type = request["type"].toString();
        int x = request["x"].toInt();
        int y = request["y"].toInt();

        if ((clientRoles[socket]=="plant" && type == "sun") || (clientRoles[socket]=="zombie" && type == "brain"))
        {
            // Find and remove the entity from gameState
            for (int i = 0; i < gameState.size(); ++i) {
                QJsonObject entity = gameState[i].toObject();
                if (entity["type"].toString() == type &&
                    entity["x"].toInt() == x &&
                    entity["y"].toInt() == y) {
                    qDebug()<<"deleted"<<entity;
                    gameState.removeAt(i--);
                    qDebug() << "Removed" << type << "at" << x << "," << y;
                    broadcastGameState();
                    break;
                    // Assuming only one entity per position
                }
            }
        }
    }
    else if (action=="get_role"){
        QString role;
        role=clientRoles[socket];
        QJsonObject respond;
        respond["action"]="get_role";
        respond["role"]=role;
        qDebug()<<"get_role";
        QJsonDocument responseDoc(respond);
        QByteArray responseData = responseDoc.toJson();
        for (QTcpSocket *client : clients){
            client->write(responseData);
            client->flush();
        }
    }
    else {
        qDebug() << "Unknown action received:" << action;
    }

    qDebug() << "processRequest completed for socket:" << socket;
}



void GameServer::broadcastGameState()
{
    QJsonObject gameStateUpdate;
    gameStateUpdate["action"] = "update";
    gameStateUpdate["game_state"] = gameState;
    gameStateUpdate["bullets"] = bullets_COOR;

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
    clientRoles.remove(socket);
    socket->deleteLater();
    qDebug() << "Client disconnected";
    clientRoleCounter--;


    gameState = QJsonArray();
    std::fill(&game_field[0][0], &game_field[0][0] + sizeof(game_field) / sizeof(int), 0);

}

void GameServer::updateGameState()
{
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    for (int i = 0; i < gameState.size(); ++i) {
        QJsonObject entity = gameState[i].toObject();

        if (entity["type"].toString() == "zombie")
        {
            double doubleValue = entity["x"].toDouble();
            int x = static_cast<int>(doubleValue);

            doubleValue = entity["y"].toDouble();
            int y = static_cast<int>(doubleValue);

            if(entity["health"].toInt() < 0)
            {
                gameState.removeAt(i);
                game_field[x][y] = 0;
                continue;
            }

            qint64 lastMove = entity["last_move"].toVariant().toLongLong();
            int moveDelay = entity["move_delay"].toInt();

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
                        for (int j = 0; j < gameState.size(); ++j)
                        {
                            QJsonObject find = gameState[j].toObject();

                            double doubleValue = find["id"].toDouble();
                            int check_id = static_cast<int>(doubleValue);

                            if(check_id == game_field[x - 1][y] and find["type"] == "plant")
                            {
                                find["health"] = find["health"].toInt() - entity["damage"].toInt();
                                gameState[j] = find;
                                break;
                            }

                        }
                    }

                }
            }
        }

        else if(entity["type"].toString() == "plant")
        {
            QJsonObject bullet;

            double doubleValue = entity["x"].toDouble();
            int x = static_cast<int>(doubleValue);

            doubleValue = entity["y"].toDouble();
            int y = static_cast<int>(doubleValue);

            doubleValue = entity["id"].toDouble();
            int ID = static_cast<int>(doubleValue);

            if(entity["health"].toInt() < 0)
            {
                gameState.removeAt(i);
                game_field[x][y] = 0;
                continue;
            }

            qint64 lastMove = entity["last_move"].toVariant().toLongLong();
            int firing_rate = entity["firing_rate"].toInt();
            if (currentTime - lastMove >= firing_rate){
                if(entity["subtype"] == "boomerang")
                {

                    for(int z = x; z < FIELD_WIDTH; z++)
                    {
                        if(game_field[z][y] != 0 and game_field[z][y] != ID)
                        {
                            for (int j = 0; j < gameState.size(); ++j)
                            {
                                QJsonObject find = gameState[j].toObject();

                                double doubleValue = find["id"].toDouble();
                                int check_id = static_cast<int>(doubleValue);

                                if(check_id == game_field[z][y] and find["type"] == "zombie")
                                {
                                    find["health"] = find["health"].toInt() - 15;
                                    gameState[j] = find;
                                    break;
                                }

                            }

                        }
                    }

                    bullet["s_x"] = x;
                    bullet["s_y"] = y;
                    bullet["e_x"] = FIELD_WIDTH;
                    bullet["e_y"] = FIELD_HEIGHT;
                    bullets_COOR.append(bullet);
                }
                else if(entity["subtype"] == "jalpeno")
                {
                    for(int z = 0; z < FIELD_WIDTH; z++)
                    {
                        if(game_field[z][y] != 0 and game_field[z][y] != ID)
                        {
                            for (int j = 0; j < gameState.size(); ++j)
                            {
                                QJsonObject find = gameState[j].toObject();

                                double doubleValue = find["id"].toDouble();
                                int check_id = static_cast<int>(doubleValue);

                                if(check_id == game_field[z][y] and find["type"] == "zombie")
                                {
                                    find["health"] = find["health"].toInt() - 300;
                                    gameState[j] = find;
                                    break;
                                }

                            }
                        }
                    }
                    gameState.removeAt(i);
                    game_field[x][y] = 0;
                }
                else if(entity["subtype"] == "peashooter")
                {
                    QJsonObject bullet;
                    bullet["s_x"] = x;
                    bullet["s_y"] = y;

                    int flag = 1;
                    for(int z = 0; z < FIELD_WIDTH and flag; z++)
                    {
                        if(game_field[z][y] != 0 and game_field[z][y] != ID)
                        {
                            for (int j = 0; j < gameState.size(); ++j)
                            {
                                QJsonObject find = gameState[j].toObject();

                                double doubleValue = find["id"].toDouble();
                                int check_id = static_cast<int>(doubleValue);

                                if(check_id == game_field[z][y] and find["type"] == "zombie")
                                {
                                    find["health"] = find["health"].toInt() - 15;
                                    gameState[j] = find;
                                    flag = 0;

                                    double doubleValue = find["x"].toDouble();
                                    int fx = static_cast<int>(doubleValue);

                                    doubleValue = find["y"].toDouble();
                                    int fy = static_cast<int>(doubleValue);

                                    bullet["e_x"] = fx;
                                    bullet["e_y"] = fy;
                                    bullets_COOR.append(bullet);

                                    break;

                                }

                            }

                        }
                    }
                }
                else if(entity["subtype"] == "twopeashooter")
                {
                    bullet["s_x"] = x;
                    bullet["s_y"] = y;
                    int flag = 1;
                    for(int z = 0; z < FIELD_WIDTH and flag; z++)
                    {
                        if(game_field[z][y] != 0 and game_field[z][y] != ID)
                        {
                            for (int j = 0; j < gameState.size(); ++j)
                            {
                                QJsonObject find = gameState[j].toObject();

                                double doubleValue = find["id"].toDouble();
                                int check_id = static_cast<int>(doubleValue);

                                if(check_id == game_field[z][y] and find["type"] == "zombie")
                                {
                                    find["health"] = find["health"].toInt() - 40;
                                    gameState[j] = find;
                                    flag = 0;

                                    double doubleValue = find["x"].toDouble();
                                    int fx = static_cast<int>(doubleValue);

                                    doubleValue = find["y"].toDouble();
                                    int fy = static_cast<int>(doubleValue);

                                    bullet["e_x"] = fx;
                                    bullet["e_y"] = fy;
                                    bullets_COOR.append(bullet);

                                    break;
                                }

                            }

                        }
                    }
                }
                else if(entity["subtype"] == "plummine")
                {
                    qDebug() << "plummine : ";

                    for (int j = 0; j < gameState.size(); ++j)
                    {
                        QJsonObject find = gameState[j].toObject();

                        double doubleValue = find["x"].toDouble();
                        int z_x = static_cast<int>(doubleValue);

                        doubleValue = find["y"].toDouble();
                        int z_y = static_cast<int>(doubleValue);

                        if((z_y <= y + 1 and z_y >= y - 1) and (z_x <= x + 1 and z_x >= x - 1) and find["type"] == "zombie")
                        {
                            find["health"] = find["health"].toInt() - 200;
                            gameState[j] = find;
                        }
                    }
                    gameState.removeAt(i);
                    game_field[x][y] = 0;
                }
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

    if (clientRoles[socket]=="plant")
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

    if (clientRoles[socket]=="zombie")
        gameState.append(brain);

    broadcastGameState();
}





int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    GameServer server;
    server.startGameServer();

    // Periodically update game state
 // Update every second

    return a.exec();
}

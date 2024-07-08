#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>
#include <QCoreApplication>
#include <QDebug>
#include <QMap>

class GameServer : public QTcpServer
{
    Q_OBJECT

public:
    GameServer(QObject *parent = nullptr);
    void startGameServer();
    void updateGameState();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void readyRead();
    void clientDisconnected();

private:
    void processRequest(QTcpSocket *socket, const QJsonObject &request);
    void handleMoveRequest(const QJsonObject &request);
    void sendGameStateToClient(QTcpSocket *client);
    void broadcastGameState();

    QList<QTcpSocket *> clients;
    QJsonArray gameState;
    QMap<qintptr, QTcpSocket *> clientMap;
    int game_field[22][6];
};

const int FIELD_WIDTH = 22;
const int FIELD_HEIGHT = 6;

#endif // GAME_SERVER_H

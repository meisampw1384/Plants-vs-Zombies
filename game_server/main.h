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

class GameServer : public QTcpServer
{
    Q_OBJECT

public:
    GameServer(QObject *parent = nullptr);
    void startGameServer();
    void updateGameState();

private slots:
    void incomingConnection(qintptr socketDescriptor) override;
    void readyRead();
    void clientDisconnected();
    void broadcastGameState();

private:
    void processRequest(QTcpSocket *socket, const QJsonObject &request);
    void handleMoveRequest(const QJsonObject &request);

    QList<QTcpSocket *> clients;
    QJsonArray gameState;
};

#endif // GAME_SERVER_H

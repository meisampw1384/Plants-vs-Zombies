#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>
#include <QRandomGenerator>
#include <QCoreApplication>
#include <QDebug>
#include <QMap>
#include <mutex>

class GameServer : public QTcpServer
{
    Q_OBJECT

public:
    GameServer(QObject *parent = nullptr);
    void startGameServer();
    void updateGameState();
    void add_sun();
    void add_brain();
    void TIME_broadcaster();
    void end_of_game_broadcast();
    void send_rule();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void readyRead();
    void clientDisconnected();

private:
    void update_count_down();
    void processRequest(QTcpSocket *socket, const QJsonObject &request);
    void sendGameStateToClient(QTcpSocket *client);
    void broadcastGameState();


    QList<QTcpSocket *> clients;
    QList<QTcpSocket *> winner;
    QJsonArray gameState;
    QJsonArray bullets_COOR;
    QMap<qintptr, QTcpSocket *> clientMap;
    int game_field[22][6];
    QTcpSocket *socket;
    QTimer *mainTimer;        // Main game update timer
    QTimer *sunTimer;         // Timer for generating suns
    QTimer *brainTimer;
    QTimer *updateTimer;
    QMap<QTcpSocket*, QString> clientRoles;
    int clientRoleCounter;
    int remainingTime;
    int round_of_game;
    int flag_zombie_reach;
    std::mutex mtx;

};

const int FIELD_WIDTH = 22;
const int FIELD_HEIGHT = 6;

#endif // GAME_SERVER_H

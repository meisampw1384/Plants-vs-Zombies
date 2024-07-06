#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>
#include <QJsonArray>
#include <QJsonObject>

namespace Ui {
class game;
}

class game : public QMainWindow
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = nullptr);
    void set_ip(QString _ip);
    void set_port(int _port);
    ~game();

private slots:
    void updateCountdown();
    void onReadyRead();
    void onDisconnected();
    void onConnected();
    void sendMoveRequest(const QString &entityType, int entityId, const QString &direction);
    void processResponse(const QJsonObject &response);

private:
    Ui::game *ui;
    QTcpSocket *socket;
    QTimer *timer;
    int remainingTime;
    QJsonArray gameState;
    QString ip;
    int port;

    void connect_to_server(const QString &ip, int port);
    void updateGameState(const QJsonArray &gameState);
    void setupUI();

};

#endif // GAME_H

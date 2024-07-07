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
    ~game();

    void set_ip(QString _ip);
    void set_port(int _port);

private slots:
    void onConnected();
    void onDisconnected();
    void updateCountdown();
    void onReadyRead();
    void on_pushButton_clicked();

    void on_astro_Z_2_clicked();

    void on_wallnut_P_clicked();

    void on_twopeashoot_P_2_clicked();

    void on_peashoot_P_clicked();

    void on_Jalo_P_clicked();

    void on_boom_P_clicked();

    void on_astro_Z_clicked();

    void on_bucket_Z_clicked();

    void on_leaf_Z_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_twopeashoot_P_clicked();

private:
    Ui::game *ui;
    QTcpSocket *socket;
    QTimer *timer;
    int remainingTime;
    QString ip;
    int port;
    QString role;  // New attribute to store the role assigned by the server

    void connect_to_server(const QString &ip, int port);
    void processResponse(const QJsonObject &response);
    void updateGameState(const QJsonArray &gameState);
    void setupUI();
    void sendMoveRequest(const QString &entityType, int entityId, const QString &direction);
};

#endif // GAME_H

#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>
#include <QJsonArray>
#include <QJsonObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

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
    void set_role(QString _role);

private slots:
    void onConnected();
    void onDisconnected();
    void updateCountdown();
    void onReadyRead();
    void on_pushButton_clicked();

    void on_Reg_zombie_pushbutton_clicked();
    void on_tall_Z_Pushbutton_clicked();

    void on_purple_pushbutton_clicked();

    void on_leaf_Z_pushbutton_clicked();

    void on_bucket_Z_pushbutton_clicked();

    void on_astro_Z_pushbutton_clicked();

    void on_boom_Pushbutton_clicked();

    void on_Jalo_P_button_clicked();

    void on_peashoot_Pushbutton_clicked();

    void on_twopeashoot_Pushbutton_clicked();

    void on_wallnut_Pushbutton_clicked();

    void on_Plum_mine_pushbutton_clicked();

private:
    Ui::game *ui;
    QTcpSocket *socket;
    QTimer *timer;
    int remainingTime;
    QString ip;
    int port;
    QString role;
    QGraphicsScene *scene;
    QMap<int, QGraphicsPixmapItem*> entities;

    void connect_to_server(const QString &ip, int port);
    void processResponse(const QJsonObject &response);
    void updateGameState(const QJsonArray &gameState);
    void setupUI();
    void sendMoveRequest(const QString &entityType, int entityId, const QString &direction);
    void addEntity(int id, const QString &type, int x, int y);
    void updateEntity(int id, int x, int y);
};

#endif // GAME_H

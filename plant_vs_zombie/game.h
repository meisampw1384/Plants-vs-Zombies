#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>
#include <QGraphicsScene>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QGraphicsView>
#include <QFile>
#include "zombies.h"
#include "plants.h"
#include "characters.h"
#include "plants.h"
#include "zombies.h"
#include "bullet.h"
#include "customgraphicscene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QPropertyAnimation>
#include <QVBoxLayout>


namespace Ui {
class game;
}

class game : public QMainWindow
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = nullptr);

    void set_ip(QString _ip);
    void get_role();
    void set_port(int _port);
    void set_userName(QString _user_name);
    void set_role(QString _role);
    void setSocket(QTcpSocket *sock);
    void setupUI();

    QString get_userName();
    ~game();
public slots:
    void onDisconnected();
    void onConnected();
    void updateGameState(const QJsonArray &gameState, const QJsonArray &bullets);
    void onReadyRead();

private slots:

    // Add button click slots here
    void on_tall_Z_Pushbutton_clicked();
    void on_Reg_zombie_pushbutton_clicked();
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

    void onFieldClicked(const QPointF &position);
    void onBrainClicked(const QPointF &pos);
    void onSunClicked(const QPointF &pos);

private:
    Ui::game *ui;
    QTcpSocket *socket;
    QTimer *timer;
    QTimer *moveTimer;
    QJsonArray gameState;
    QJsonArray bullets;
    CustomGraphicsScene *scene;
    int remainingTime;
    QString ip;
    int port;
    QString role;
    QString userName;

    enum CharacterType {
        None,
        TallZombie,
        RegZombie,
        PurpleZombie,
        LeafZombie,
        BucketZombie,
        AstroZombie,
        BoomPlant,
        JalapenoPlant,
        PeashooterPlant,
        TwoPeashooterPlant,
        WalnutPlant,
        PlumMinePlant
    };

    CharacterType selectedCharacterType;

    void add_character(Characters *ch);
    void addCharacterAtPosition(int x, int y);
};

#endif // GAME_H

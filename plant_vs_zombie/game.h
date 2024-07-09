#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>
#include <QGraphicsScene>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "zombies.h"
#include "plants.h"
#include "characters.h"
#include "plants.h"
#include "zombies.h"
#include "customgraphicscene.h"
#include <QGraphicsPixmapItem>

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

    void set_role(QString _role);
    ~game();
public slots:
    void onConnected();
    void onDisconnected();
    void updateCountdown();
    void updateGameState(const QJsonArray &_game_state);
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

private:
    Ui::game *ui;
    QTcpSocket *socket;
    QTimer *timer;
    QTimer *moveTimer;
    QJsonArray gameState;
    CustomGraphicsScene *scene;
    int remainingTime;
    QString ip;
    int port;
    QString role;

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
    void setupUI();
    void addCharacterAtPosition(int x, int y);
};

#endif // GAME_H

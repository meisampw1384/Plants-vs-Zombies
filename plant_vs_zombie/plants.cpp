#include "plants.h"
#include <QPixmap>

plants::plants(int x, int y, int health, int attackPower,int _firing_rate , QString type, const QString &description, QGraphicsItem *parent)
    : Characters(x, y, health, attackPower, type, description),firing_rate(_firing_rate)
{ // Assuming each cell is 50x50 pixels
    if (type == "walnut") {
        setPixmap(QPixmap("../images/optimized for game/walnut op.png"));
    } else if (type == "peashooter") {
        setPixmap(QPixmap("../images/optimized for game/peashooter op.png"));
    } else if (type == "twopeashooter") {
        setPixmap(QPixmap("../images/optimized for game/two_peashooter op.png"));
    } else if (type == "plummine") {
        setPixmap(QPixmap("../images/optimized for game/plum mine op.png"));
    } else if (type == "jalpeno") {
        setPixmap(QPixmap("../images/optimized for game/jalapino op.png"));
    } else if (type == "boomerang") {
        setPixmap(QPixmap("../images/optimized for game/boomrang op.png"));
    } else {
        qDebug()<<"the picture is not here";
    }
}

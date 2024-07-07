#include "plants.h"
#include <QPixmap>

plants::plants(int x, int y, int health, int attackPower, int id, QString type, const QString &description, QGraphicsItem *parent)
    : Characters(x, y, health, attackPower, id, type, description)
{
    setPos(x * 50, y * 50); // Assuming each cell is 50x50 pixels
    if (type == "walnut") {
        setPixmap(QPixmap("../images/opimized pictures/walnut op.png"));
    } else if (type == "peashooter") {
        setPixmap(QPixmap("../images/peashooter.png"));
    } else if (type == "twopeashooter") {
        setPixmap(QPixmap("../images/opimized pictures/two_peashooter op.png"));
    } else if (type == "plummine") {
        setPixmap(QPixmap("../images/opimized pictures/plum mine op.png"));
    } else if (type == "jalpeno") {
        setPixmap(QPixmap("../images/opimized pictures/jalapino op.png"));
    } else if (type == "boomerang") {
        setPixmap(QPixmap("../images/opimized pictures/boomrang op.png"));
    } else {
        qDebug()<<"the picture is not here";
    }
}

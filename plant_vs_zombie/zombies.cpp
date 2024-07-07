#include "zombies.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>

zombies::zombies(int x, int y, int health, int attackPower, int id, QString type, const QString &description, int movementDelay, int timeBetweenAttacks, QGraphicsItem *parent)
    : Characters(x, y, health, attackPower, id, type, description), movementDelay(movementDelay), timeBetweenAttacks(timeBetweenAttacks)
{
    setPos(x * 50, y * 50); // Assuming each cell is 50x50 pixels
    if (type == "buckethead") {
        setPixmap(QPixmap(":/images/opimized pictures/Bucket head op.png"));
    } else if (type == "regular") {
        setPixmap(QPixmap(":/images/opimized pictures/regular op.png"));
    } else if (type == "tall") {
        setPixmap(QPixmap(""));
    } else if (type == "leafhead") {
        setPixmap(QPixmap(":/images/opimized pictures/leaf hair op.png"));
    } else if (type == "astronaut") {
        setPixmap(QPixmap(":/images/opimized pictures/astronaut op.png"));
    } else if (type == "purplehair") {
        setPixmap(QPixmap(":/images/opimized pictures/purple hair op.png"));
    } else {
        qDebug()<<"there is no picture!";
    }
}

void zombies::moveLeft()
{
    if (getX() > 0)
    {
        setX(getX() - 1);
    }
}

int zombies::getMovementDelay() const
{
    return movementDelay;
}

int zombies::getTimeBetweenAttacks() const
{
    return timeBetweenAttacks;
}

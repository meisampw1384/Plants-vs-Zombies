#include "zombies.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>

zombies::zombies(int x, int y, int health, int attackPower, QString type, const QString &description, float movementDelay, float timeBetweenAttacks, QGraphicsItem *parent)
    : Characters(x, y, health, attackPower, type, description), movementDelay(movementDelay), timeBetweenAttacks(timeBetweenAttacks)
{
    if (type == "buckethead") {
        setPixmap(QPixmap("../images/opimized pictures/Bucket head op.png"));
    } else if (type == "regular") {
        setPixmap(QPixmap("../images/opimized pictures/regular op.png"));
    } else if (type == "tall") {
        setPixmap(QPixmap("../images/opimized pictures/tall op.png"));
    } else if (type == "leafhead") {
        setPixmap(QPixmap("../images/opimized pictures/leaf hair op.png"));
    } else if (type == "astronaut") {
        setPixmap(QPixmap("../images/opimized pictures/astronaut op.png"));
    } else if (type == "purplehair") {
        setPixmap(QPixmap("../images/opimized pictures/purple hair op.png"));
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

float zombies::getMovementDelay() const
{
    return movementDelay;
}

float zombies::getTimeBetweenAttacks() const
{
    return timeBetweenAttacks;
}

void zombies::setMovementDelay(float movement_delay)
{
    movementDelay=movement_delay;
}
void zombies::setTimeBetweenAttacks(float time_attacks){
    timeBetweenAttacks=time_attacks;
}

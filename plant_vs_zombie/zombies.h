#ifndef ZOMBIES_H
#define ZOMBIES_H

#include "characters.h"
#include <QGraphicsPixmapItem>

class zombies : public Characters
{
private:
    int movementDelay;
    int timeBetweenAttacks;

public:
    zombies(int x, int y, int health, int attackPower, int id, QString type, const QString &description, int movementDelay, int timeBetweenAttacks, QGraphicsItem *parent = nullptr);

    // Override moveLeft to specify zombie's movement behavior
    void moveLeft();

    // Accessors for additional zombie-specific attributes
    int getMovementDelay() const;
    int getTimeBetweenAttacks() const;
};

#endif // ZOMBIES_H

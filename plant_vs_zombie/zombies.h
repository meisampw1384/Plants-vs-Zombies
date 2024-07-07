#ifndef ZOMBIES_H
#define ZOMBIES_H

#include "characters.h"
#include <QGraphicsPixmapItem>

class zombies : public Characters
{
private:
    float movementDelay;
    float timeBetweenAttacks;

public:
    zombies(int x, int y, int health, int attackPower,  QString type, const QString &description, float movementDelay, float timeBetweenAttacks, QGraphicsItem *parent = nullptr);

    // Override moveLeft to specify zombie's movement behavior
    void moveLeft();

    // Accessors for additional zombie-specific attributes
    float getMovementDelay() const;
    float getTimeBetweenAttacks() const;
    void setMovementDelay(float movement_delay);
    void setTimeBetweenAttacks(float time_attacks);
};

#endif // ZOMBIES_H

#ifndef PLANTS_H
#define PLANTS_H

#include "characters.h"
#include <QGraphicsPixmapItem>

class plants : public Characters
{
public:
    plants(int x, int y, int health, int attackPower, int id, QString type, const QString &description, QGraphicsItem *parent = nullptr);
};

#endif // PLANTS_H

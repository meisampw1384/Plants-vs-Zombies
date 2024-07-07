#ifndef PLANTS_H
#define PLANTS_H

#include "characters.h"
#include <QGraphicsPixmapItem>

class plants : public Characters
{
public:
    plants(int x, int y, int health, int attackPower,int _firing_rate,  QString type, const QString &description, QGraphicsItem *parent = nullptr);
private:
    int firing_rate;
};

#endif // PLANTS_H

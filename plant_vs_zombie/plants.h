#ifndef PLANTS_H
#define PLANTS_H
#include "characters.h"

class plants : Characters
{
private:
    int firing_rate;
public:
    plants(int x, int y, int H, int AP, QString D, int FR);
    int & GS_COOR_x();
    int & GS_COOR_y();
    int & GS_Health();
    int G_Attack_Power();
    QString G_Description();
    int G_Firing_rate();
};

#endif // PLANTS_H

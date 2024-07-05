#ifndef ZOMBIES_H
#define ZOMBIES_H

#include "characters.h"

class zombies : Characters
{
private:
    int movment_delay;
    int time_between_attacks;
public:
    zombies(int x, int y, int H, int AP, QString D, int MD, int TBA);
    int & GS_COOR_x();
    int & GS_COOR_y();
    int & GS_Health();
    int & GS_Attack_Power();
    QString G_Description();
    int G_Move_delay();
    int G_time_beetwen();
};

#endif // ZOMBIES_H

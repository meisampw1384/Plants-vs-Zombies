#include "zombies.h"

zombies::zombies(int x, int y, int H, int AP, QString D, int MD, int TBA) : Characters(x, y, H, AP, D), movment_delay(MD), time_between_attacks(TBA)
{
}

int & zombies::GS_COOR_x()
{
    return COOR_x;
}

int & zombies::GS_COOR_y()
{
    return COOR_y;
}

int & zombies::GS_Health()
{
    return Health;
}

int & zombies::GS_Attack_Power()
{
    return Attack_power;
}

QString zombies::G_Description()
{
    return Description;
}

int zombies::G_Move_delay()
{
    return movment_delay;
}


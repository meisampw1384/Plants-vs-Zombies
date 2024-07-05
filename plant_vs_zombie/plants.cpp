#include "plants.h"

plants::plants(int x, int y, int H, int AP, QString D, int FR) : Characters(x, y, H, AP, D), firing_rate(FR)
{
}

int & plants::GS_COOR_x()
{
    return COOR_x;
}

int & plants::GS_COOR_y()
{
    return COOR_y;
}

int & plants::GS_Health()
{
    return Health;
}

int plants::G_Attack_Power()
{
    return Attack_power;
}

QString plants::G_Description()
{
    return Description;
}

int plants::G_Firing_rate()
{
    return firing_rate;
}

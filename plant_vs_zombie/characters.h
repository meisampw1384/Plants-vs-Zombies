#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <QString>

class Characters
{
protected:
    int COOR_x;
    int COOR_y;
    int Health;
    int Attack_power;
    QString Description;
public:
    Characters(int x, int y, int H, int AP, QString D);
    ~Characters();

};

#endif // CHARACTERS_H

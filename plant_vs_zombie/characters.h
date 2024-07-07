#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <QString>
#include <QGraphicsPixmapItem>

class Characters : public QGraphicsPixmapItem
{
protected:
    int coorX;
    int coorY;
    int health;
    int id;
    static int gen_id;
    int attackPower;
    QString type;
    QString description;

public:
    Characters(int x, int y, int health, int attackPower,QString type ,const QString &description, QGraphicsItem *parent = nullptr);
    virtual ~Characters();

    int getX() const;
    void setX(int x);

    int getY() const;
    void setY(int y);

    int getHealth() const;
    void setHealth(int health);

    int getAttackPower() const;
    void setAttackPower(int attackPower);

    QString getDescription() const;
    void setDescription(const QString &description);

    void setPosition(int x, int y);
    int get_id();
    QString get_type();
    void set_id(int id);
    void set_type(QString type);
};

#endif // CHARACTERS_H


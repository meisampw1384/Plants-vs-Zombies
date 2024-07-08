#include "characters.h"

int Characters::gen_id=0;

Characters::Characters(int x, int y, int health, int attackPower,QString type, const QString &description, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), coorX(x), coorY(y), health(health), attackPower(attackPower),type(type), description(description) {
    setPos(coorX * 77, coorY * 72);
    id=gen_id+1;
    gen_id++;
}

Characters::~Characters() {
}

int Characters::getX() const {
    return coorX;
}

void Characters::setX(int x) {
    coorX = x;
    setPos(coorX * 77, coorY * 72);
}

int Characters::getY() const {
    return coorY;
}

void Characters::setY(int y) {
    coorY = y;
    setPos(coorX * 77, coorY * 72);
}

int Characters::getHealth() const {
    return health;
}

void Characters::setHealth(int health) {
    this->health = health;
}

int Characters::getAttackPower() const {
    return attackPower;
}

void Characters::setAttackPower(int attackPower) {
    this->attackPower = attackPower;
}

QString Characters::getDescription() const {
    return description;
}

void Characters::setDescription(const QString &description) {
    this->description = description;
}

void Characters::setPosition(int x, int y) {
    coorX = x;
    coorY = y;
    setPos(coorX * 77, coorY * 72);
}

int Characters::get_id()
{
    return id;
}

QString Characters::get_type()
{
    return type;
}

void Characters::set_id(int id)
{
    id=id;
}

void Characters::set_type(QString type)
{
    type=type;
}

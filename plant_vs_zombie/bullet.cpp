#include "bullet.h"

Bullet::Bullet(qreal x, qreal y, qreal width, qreal height, const QColor &color, QGraphicsItem *parent)
    : QGraphicsEllipseItem(x, y, width, height, parent)
{
    setBrush(QBrush(color));
}

QPointF Bullet::pos() const {
    return QGraphicsEllipseItem::pos();
}

void Bullet::setPos(const QPointF &pos) {
    QGraphicsEllipseItem::setPos(pos);
}

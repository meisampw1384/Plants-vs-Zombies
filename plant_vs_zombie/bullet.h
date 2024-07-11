#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QPropertyAnimation>
#include <QBrush>
#include <QColor>

class Bullet : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    Bullet(qreal x, qreal y, qreal width, qreal height, const QColor &color, QGraphicsItem *parent = nullptr);

    QPointF pos() const;
    void setPos(const QPointF &pos);
};

#endif // BULLET_H

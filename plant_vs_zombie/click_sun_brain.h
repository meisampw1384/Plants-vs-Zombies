// click_sun_brain.h

#ifndef CLICK_SUN_BRAIN_H
#define CLICK_SUN_BRAIN_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class click_sun_brain : public QGraphicsScene
{
    Q_OBJECT

public:
    click_sun_brain(QObject *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void sunClicked();
    void brainClicked();
};

#endif // CLICK_SUN_BRAIN_H

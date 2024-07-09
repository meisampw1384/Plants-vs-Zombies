
#include "customgraphicscene.h"
#include <QGraphicsItem>

CustomGraphicsScene::CustomGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
}

void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());

    if (item) {
        if (item->data(Qt::UserRole) == "sun") {
            emit sunClicked(event->scenePos());
        } else if (item->data(Qt::UserRole) == "brain") {
            emit brainClicked(event->scenePos());
        }
    }

    emit sceneClicked(event->scenePos());
    QGraphicsScene::mousePressEvent(event);
}

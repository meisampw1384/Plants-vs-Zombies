
#include "customgraphicscene.h"

CustomGraphicsScene::CustomGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
}

void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sceneClicked(event->scenePos());
    QGraphicsScene::mousePressEvent(event);
}



#include "click_sun_brain.h"

click_sun_brain::click_sun_brain(QObject *parent)
    : QGraphicsScene(parent)
{
    // Initialize your scene if necessary
}

void click_sun_brain::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Determine if sun or brain is clicked based on event->scenePos()
        // Example: Checking a rectangular area
        QRectF sunRect(100, 100, 50, 50); // Example rectangular area for sun
        QRectF brainRect(200, 200, 50, 50); // Example rectangular area for brain

        if (sunRect.contains(event->scenePos())) {
            emit sunClicked();
        } else if (brainRect.contains(event->scenePos())) {
            emit brainClicked();
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

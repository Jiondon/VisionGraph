#include "visiongraphscene.h"
#include "qdebug.h"

VisionGraphScene::VisionGraphScene(QObject *parent):
    QGraphicsScene(parent)
{
}

void VisionGraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signal_MouseMove(event->scenePos().x(),event->scenePos().y());
    QGraphicsScene::mouseMoveEvent(event);
}

void VisionGraphScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signal_MousePress(event->scenePos().x(),event->scenePos().y());
    QGraphicsScene::mousePressEvent(event);

}


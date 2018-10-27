#include "visionitem.h"
#include <QDebug>

VisionItem::VisionItem(QGraphicsItem *parent):QGraphicsItem(parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

bool VisionItem::getPosInArea(qreal x, qreal y)
{
    return m_bInArea;
}

void VisionItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"visionItem mousePressEvent";
    setSelected(true);
    m_bSelectedStatus = !m_bSelectedStatus;
//    emit signal_clicked(this,m_bSelectedStatus);
//    emit signal_press();

}


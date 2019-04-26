#include "visiontextitem.h"

VisionTextItem::VisionTextItem(VisionItem *parent) : VisionItem(parent)
{

}

void VisionTextItem::setData(VGRegion vgRegion, QString textName)
{
    m_vgRegion = vgRegion;
    m_strText = textName;

    //通过vgRegion计算rect
//    this->setPos();
}

void VisionTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void VisionTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void VisionTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void VisionTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

QRectF VisionTextItem::boundingRect() const
{
    return QRectF(0,0,100,100);
}

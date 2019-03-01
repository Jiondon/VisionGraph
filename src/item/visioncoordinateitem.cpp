#include "visioncoordinateitem.h"

VisionCoordinateItem::VisionCoordinateItem(bool bEdit, QColor color, QGraphicsItem *parent) : QGraphicsItem(parent)
{

}

void VisionCoordinateItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen = QPen(m_borderColor,0);
    painter->setPen(pen);

    painter->rotate(m_angle);

    //绘制交叉的坐标系
    painter->drawLine(QPointF(0,0),QPointF(0+m_iLength,0));
    painter->drawLine(QPointF(0+m_iLength,0),QPointF(0+m_iLength-3,0-2));
    painter->drawLine(QPointF(0+m_iLength,0),QPointF(0+m_iLength-3,0+2));
//    painter->drawLine(QPointF(m_width-10,0),QPointF(m_width-10,m_height));

    painter->drawLine(QPointF(0,0),QPointF(0,0+m_iLength));
    painter->drawLine(QPointF(0,0+m_iLength),QPointF(0-2,0+m_iLength-3));
    painter->drawLine(QPointF(0,0+m_iLength),QPointF(0+2,0+m_iLength-3));
}

QRectF VisionCoordinateItem::boundingRect() const
{
    return QRectF(-1,-1,m_iLength+4,m_iLength+4);
}

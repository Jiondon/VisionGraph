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

    //绘制交叉的坐标系
    painter->drawLine(QPointF(m_pointF.x()-m_iLength,m_pointF.y()),QPointF(m_pointF.x()+m_iLength,m_pointF.y()));

    painter->drawLine(QPointF(m_pointF.x()+m_iLength,m_pointF.y()),QPointF(m_pointF.x()+m_iLength-3,m_pointF.y()-2));
    painter->drawLine(QPointF(m_pointF.x()+m_iLength,m_pointF.y()),QPointF(m_pointF.x()+m_iLength-3,m_pointF.y()+2));
//    painter->drawLine(QPointF(m_width-10,0),QPointF(m_width-10,m_height));

    painter->drawLine(QPointF(m_pointF.x(),m_pointF.y()-m_iLength),QPointF(m_pointF.x(),m_pointF.y()+m_iLength));

    painter->drawLine(QPointF(m_pointF.x(),m_pointF.y()-m_iLength),QPointF(m_pointF.x()-2,m_pointF.y()-m_iLength+3));
    painter->drawLine(QPointF(m_pointF.x(),m_pointF.y()-m_iLength),QPointF(m_pointF.x()+2,m_pointF.y()-m_iLength+3));
}

QRectF VisionCoordinateItem::boundingRect() const
{
    return QRectF(m_pointF-QPointF(m_iLength,m_iLength),m_pointF+QPointF(m_iLength,m_iLength));
}

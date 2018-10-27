#include "visionpoint.h"

VisionPoint::VisionPoint(VisionItem *parent) : VisionItem(parent)
{

}

void VisionPoint::setPointF(QPointF pointF)
{
    m_pointF = pointF;
}

void VisionPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    QPen pen = QPen(QColor(255,0,0),0);
    painter->setPen(pen);
    painter->setBrush(Qt::red);
    painter->drawEllipse(m_pointF,1,1);
//    painter->drawEllipse(QPointF(m_pointF.x()+2,m_pointF.y()),1,1);

}

QRectF VisionPoint::boundingRect() const
{
    return QRectF(m_pointF,m_pointF);
}

#include "visionpoint.h"
#include "../control/color.h"

VisionPoint::VisionPoint(VisionItem *parent) : VisionItem(parent)
{
    m_borderColor = borderColor;
    m_brushColor = brushColor;
    m_selectedColor = m_selectedColor;
}

void VisionPoint::setPointF(QPointF pointF)
{
    m_pointF = pointF;
}

void VisionPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen = QPen(m_borderColor,0);
    painter->setPen(pen);
    painter->setBrush(Qt::red);
    painter->drawEllipse(m_pointF,1,1);
//    painter->drawEllipse(QPointF(m_pointF.x()+2,m_pointF.y()),1,1);

}

QRectF VisionPoint::boundingRect() const
{
    return QRectF(m_pointF,m_pointF);
}

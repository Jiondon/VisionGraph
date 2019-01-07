#include "visionarrow.h"
#include "../control/color.h"

VisionArrow::VisionArrow(QObject *parent) : QObject(parent)
{

    m_borderColor = borderColor;
    m_brushColor = brushColor;
    m_selectedColor = m_selectedColor;
}

void VisionArrow::setPointF(QPointF pointF)
{
    m_pointF = pointF;
}

void VisionArrow::setArrowLength(int iLength)
{
    m_iLength = iLength;
}

void VisionArrow::setColor(QColor color)
{
    m_borderColor = color;
}

QVector<QPointF> VisionArrow::getPoints(){
    QVector<QPointF> vec_p;
    vec_p.append(m_pointF);
    return vec_p;
}

void VisionArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen = QPen(m_borderColor,0);
    painter->setPen(pen);
//    painter->setBrush(Qt::red);

    //绘制交叉的坐标系
    painter->drawLine(QPointF(m_pointF.x()-m_iLength,m_pointF.y()),QPointF(m_pointF.x()+m_iLength,m_pointF.y()));

    painter->drawLine(QPointF(m_pointF.x()+m_iLength,m_pointF.y()),QPointF(m_pointF.x()+m_iLength-3,m_pointF.y()-2));
    painter->drawLine(QPointF(m_pointF.x()+m_iLength,m_pointF.y()),QPointF(m_pointF.x()+m_iLength-3,m_pointF.y()+2));
//    painter->drawLine(QPointF(m_width-10,0),QPointF(m_width-10,m_height));

    painter->drawLine(QPointF(m_pointF.x(),m_pointF.y()-m_iLength),QPointF(m_pointF.x(),m_pointF.y()+m_iLength));

    painter->drawLine(QPointF(m_pointF.x(),m_pointF.y()-m_iLength),QPointF(m_pointF.x()-2,m_pointF.y()-m_iLength+3));
    painter->drawLine(QPointF(m_pointF.x(),m_pointF.y()-m_iLength),QPointF(m_pointF.x()+2,m_pointF.y()-m_iLength+3));
//    painter->drawLine(QPointF(m_width-10,0),QPointF(m_width-10,m_height));
}

QRectF VisionArrow::boundingRect() const
{
    return QRectF(m_pointF-QPointF(m_iLength,m_iLength),m_pointF+QPointF(m_iLength,m_iLength));
}

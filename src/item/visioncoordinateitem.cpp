#include "visioncoordinateitem.h"
#include "../control/color.h"

VisionCoordinateItem::VisionCoordinateItem(bool bEdit, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor, VisionItem *parent) : VisionItem(parent)
{
    if(color_enable){
        m_borderColor = borderColor;
    }else{
        m_borderColor = borderColor;
    }

    m_bEdit = false;
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
    return QRectF(-m_iLength-2,-m_iLength-2,2*m_iLength+4,2*m_iLength+4);
}

void VisionCoordinateItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_bEdit){
        QGraphicsItem::mouseMoveEvent(event);
    }else{
        return;
    }
}

void VisionCoordinateItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_bEdit){
        QGraphicsItem::mousePressEvent(event);
    }else{
        return;
    }
}

void VisionCoordinateItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_bEdit){
        QGraphicsItem::mouseReleaseEvent(event);
    }else{
        return;
    }
}

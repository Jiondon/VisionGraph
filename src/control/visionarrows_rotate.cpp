#include "visionarrows_rotate.h"

VisionArrows_Rotate::VisionArrows_Rotate(qreal x, qreal y, qreal w, qreal h, QColor penColor, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    m_x = x;m_y = y;m_width = w;m_height = h;
    if(w<10)
        m_width = 10;
    if(h<10)
        m_height = 10;
    m_penColor = penColor;
    this->setPos(x,y);
    setAcceptHoverEvents(true);
//    setTransformOriginPoint(m_width/2,m_height/2);  //设置旋转的原点为中心点
}


void VisionArrows_Rotate::setRect(qreal x, qreal y, qreal w, qreal h)
{
    m_x = x;m_y = y;m_width = w;m_height = h;
    this->setPos(x,y);
}

void VisionArrows_Rotate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)
    painter->setPen(QPen(QBrush(QColor(255,0,0)),0));
    painter->drawLine(QPointF(0,m_height/2),QPointF(m_width,m_height/2));
    painter->drawLine(QPointF(m_width-10,0),QPointF(m_width,m_height/2));
    painter->drawLine(QPointF(m_width-10,m_height),QPointF(m_width,m_height/2));
    painter->drawLine(QPointF(m_width-10,0),QPointF(m_width-10,m_height));
}

QRectF VisionArrows_Rotate::boundingRect() const
{
    QRectF rect = QRectF(0,0,m_width,m_height);
    return rect;
}

void VisionArrows_Rotate::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void VisionArrows_Rotate::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug()<<"hover move event";
//    this->setCursor(Qt::UpArrowCursor);
//    emit signalHoverEnter();

}

void VisionArrows_Rotate::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->scene()->views().at(0)->setCursor(Qt::ArrowCursor);
    emit signalHoverLeave();
}

void VisionArrows_Rotate::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    this->scene()->views().at(0)->setCursor(Qt::UpArrowCursor);
    emit signalHoverEnter();
}

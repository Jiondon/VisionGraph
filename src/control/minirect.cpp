#include "minirect.h"
#include <QDebug>
#include <QPainter>
#include <QBrush>
#include <QCursor>
#include "color.h"

MiniRect::MiniRect(qreal x, qreal y, qreal w, qreal h, QColor penColor, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    m_x = x;m_y = y;m_width = w;m_height = h;
    m_penColor = penColor;
    this->setPos(x,y);
    setAcceptHoverEvents(true);
    setTransformOriginPoint(m_width/2,m_height/2);  //设置旋转的原点为中心点
}

void MiniRect::setRect(qreal x, qreal y, qreal w, qreal h)
{
    m_x = x;m_y = y;m_width = w;m_height = h;
    this->setPos(x,y);
}

void MiniRect::setIndex(int index)
{
    m_index = index;
}

void MiniRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setPen(QPen(borderColor,0));
    painter->setBrush(QBrush(borderColor));  //此处填充和边框保持一致，原因自己想
    painter->drawRect(QRectF(0,0,m_width,m_height));
}

QRectF MiniRect::boundingRect() const
{
    QRectF rect = QRectF(0,0,m_width,m_height);
    return rect;
}

void MiniRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void MiniRect::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug()<<"hover move event";
    emit signalIndex(m_index);
}

void MiniRect::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit signalIndex(-1);
}

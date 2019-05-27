#include "minirect.h"
#include <QDebug>
#include <QPainter>
#include <QBrush>
#include <QCursor>
#include "color.h"

MiniRect::MiniRect(qreal x, qreal y, qreal w, qreal h, QColor borderColor, QColor selectedColor, QColor brushColor, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    m_borderColor = borderColor;
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;

    m_x = x;m_y = y;m_width = w;m_height = h;
    m_penColor = borderColor;
    this->setPos(x,y);
    setAcceptHoverEvents(true);
//    setTransformOriginPoint((m_width/2)*(1/this->scene()->views().at(0)->matrix().m22()),(m_height/2)*(1/this->scene()->views().at(0)->matrix().m22()));  //设置旋转的原点为中心点
    setTransformOriginPoint((m_width/2),(m_height/2));  //设置旋转的原点为中心点
}

void MiniRect::setBrushEnable(bool brushEnable)
{
    m_bBrushEnable = brushEnable;
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

    if(this->transformOriginPoint() != QPointF(boundingRect().center())){
        setTransformOriginPoint(QPointF(boundingRect().center()));  //设置旋转的原点为中心点
    }

    painter->setPen(QPen(m_selectedColor,1*(1/this->scene()->views().at(0)->matrix().m22())));
    if(m_bBrushEnable){
        painter->setBrush(QBrush(m_selectedColor));  //此处填充和边框保持一致，原因自己想
    }
    qreal x = m_width/2-(m_width/2)*(1/this->scene()->views().at(0)->matrix().m22());
    qreal y = m_height/2-(m_height/2)*(1/this->scene()->views().at(0)->matrix().m22());
    qreal w = m_width*(1/this->scene()->views().at(0)->matrix().m22());
    qreal h = m_height*(1/this->scene()->views().at(0)->matrix().m22());

    painter->drawRect(QRectF(x,y,w,h));
}

QRectF MiniRect::boundingRect() const
{
    QRectF rect;
    if(this->scene()->views().at(0)->matrix().m22() > 1){
         rect = QRectF(0,0,m_width,m_height);
    }else{
        //缩小后，由于需要保持item大小，故有效区域需要放大--采用放大后的部分--即绘制的部分
        qreal x = m_width/2-(m_width/2)*(1/this->scene()->views().at(0)->matrix().m22());
        qreal y = m_height/2-(m_height/2)*(1/this->scene()->views().at(0)->matrix().m22());
        qreal w = m_width*(1/this->scene()->views().at(0)->matrix().m22());
        qreal h = m_height*(1/this->scene()->views().at(0)->matrix().m22());
        rect = QRectF(x,y,w,h);
    }
    return rect;
}

void MiniRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void MiniRect::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug()<<"hover move event";
    qreal x = m_width/2-(m_width/2)*(1/this->scene()->views().at(0)->matrix().m22());
    qreal y = m_height/2-(m_height/2)*(1/this->scene()->views().at(0)->matrix().m22());
    qreal w = m_width*(1/this->scene()->views().at(0)->matrix().m22());
    qreal h = m_height*(1/this->scene()->views().at(0)->matrix().m22());
    QRectF rf(x,y,w,h);
    if(rf.contains(event->pos())){
        emit signalIndex(m_index);
    }
}

void MiniRect::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit signalIndex(-1);
}

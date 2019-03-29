#include "visioncrosspointitem.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "../control/color.h"

VisionCrossPointItem::VisionCrossPointItem(bool edit, qreal length,bool color_enable, QColor color, VisionItem *parent) : VisionItem(parent)
{
    if(color_enable){
        m_borderColor = color;
    }else{
        m_borderColor = borderColor;
    }
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;
    m_bEdit = edit;
    m_length = length;
    if(m_bEdit){
        setSelectedStatus(true);
    }else{
        setSelectedStatus(false);
    }
    setAcceptHoverEvents(true);
    m_type = ItemType::Paint_CrossPoint;
}

VisionCrossPointItem::VisionCrossPointItem(QPointF pointF, VisionItem *parent) : VisionItem(parent)
{
    m_pointF = pointF;
    setAcceptHoverEvents(true);
    m_type = ItemType::Paint_CrossPoint;
}

VisionCrossPointItem::VisionCrossPointItem(qreal x, qreal y, VisionItem *parent) : VisionItem(parent)
{
    m_pointF = QPointF(x,y);
    setAcceptHoverEvents(true);
    m_type = ItemType::Paint_CrossPoint;
}

void VisionCrossPointItem::setPoint(qreal x, qreal y)
{
    m_pointF = QPointF(x,y);
}

void VisionCrossPointItem::setPoint(QPointF pointF)
{
    m_pointF = pointF;
}

QPointF VisionCrossPointItem::getPoint()
{
    return m_pointF;
}

bool VisionCrossPointItem::getPosInArea(qreal x, qreal y)
{
    if(boundingRect().contains(x,y)){
        return true;
    }else{
        return false;
    }
}

QVector<QPointF> VisionCrossPointItem::getPoints()
{
    QVector<QPointF> vec_p;
    vec_p.append(m_pointF);
    return vec_p;
}

QRectF VisionCrossPointItem::boundingRect() const
{
    QRectF rf = QRectF(m_pointF.x()-m_length*(1/g_scale),m_pointF.y()-m_length*(1/g_scale),2*m_length*(1/g_scale),2*m_length*(1/g_scale));
    return rf;
}

void VisionCrossPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    if(option->state & QStyle::State_Selected){
        painter->setPen(QPen(QBrush(m_selectedColor),g_penWidth*(1/g_scale)));
        setSelectedStatus(true);
    }else{
        painter->setPen(QPen(QBrush(m_borderColor),g_penWidth*(1/g_scale)));
        setSelectedStatus(false);
    }

//    painter->setPen(QPen(QBrush(QColor(255,0,0)),0));
    painter->drawLine(QPointF(m_pointF.x(),m_pointF.y()-m_length*(1/g_scale)),QPointF(m_pointF.x(),m_pointF.y()+m_length*(1/g_scale)));
    painter->drawLine(QPointF(m_pointF.x()-m_length*(1/g_scale),m_pointF.y()),QPointF(m_pointF.x()+m_length*(1/g_scale),m_pointF.y()));

}

void VisionCrossPointItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    if(boundingRect().contains(event->scenePos())){
        qDebug()<<"in area";
        setSelectedStatus(true);
    }else{
        qDebug()<<"out area";
        setSelectedStatus(false);
    }

    this->scene()->update();
}

void VisionCrossPointItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    this->setPoint(event->scenePos());
    this->scene()->update();
}

void VisionCrossPointItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    if(!boundingRect().contains(QPointF(event->scenePos().x(),event->scenePos().y()))){
        emit signal_clicked(this,true,true,event->scenePos().x(),event->scenePos().y());
        return;
    }
    emit signal_clicked(this,true,false,event->scenePos().x(),event->scenePos().y());
    QGraphicsItem::mouseReleaseEvent(event);

}

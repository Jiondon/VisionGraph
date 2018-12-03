#include "visioncrosspointitem.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "../control/color.h"

VisionCrossPointItem::VisionCrossPointItem(bool edit, VisionItem *parent) : VisionItem(parent)
{
    m_borderColor = borderColor;
    m_brushColor = brushColor;
    m_selectedColor = m_selectedColor;
    m_bEdit = edit;
    setAcceptHoverEvents(true);
    m_type = ItemType::CrossPoint;
}

VisionCrossPointItem::VisionCrossPointItem(QPointF pointF, VisionItem *parent) : VisionItem(parent)
{
    m_pointF = pointF;
    setAcceptHoverEvents(true);
    m_type = ItemType::CrossPoint;
}

VisionCrossPointItem::VisionCrossPointItem(qreal x, qreal y, VisionItem *parent) : VisionItem(parent)
{
    m_pointF = QPointF(x,y);
    setAcceptHoverEvents(true);
    m_type = ItemType::CrossPoint;
}

void VisionCrossPointItem::setPoint(qreal x, qreal y)
{
    m_pointF = QPointF(x,y);
}

void VisionCrossPointItem::setPoint(QPointF pointF)
{
    m_pointF = pointF;
}

bool VisionCrossPointItem::getPosInArea(qreal x, qreal y)
{
    if(boundingRect().contains(x,y)){
        return true;
    }else{
        return false;
    }
}

QRectF VisionCrossPointItem::boundingRect() const
{
    QRectF rf = QRectF(m_pointF.x()-2,m_pointF.y()-2,4,4);
    return rf;
}

void VisionCrossPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    if(option->state & QStyle::State_Selected){
        painter->setPen(QPen(QBrush(m_selectedColor),0));
        setEdit(true);
    }else{
        painter->setPen(QPen(QBrush(m_borderColor),0));
        setEdit(false);
    }

//    painter->setPen(QPen(QBrush(QColor(255,0,0)),0));
    painter->drawLine(QPointF(m_pointF.x(),m_pointF.y()-2),QPointF(m_pointF.x(),m_pointF.y()+2));
    painter->drawLine(QPointF(m_pointF.x()-2,m_pointF.y()),QPointF(m_pointF.x()+2,m_pointF.y()));

}

void VisionCrossPointItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    if(boundingRect().contains(event->scenePos())){
        qDebug()<<"in area";
        setSelected(true);
    }else{
        qDebug()<<"out area";
        setSelected(false);
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

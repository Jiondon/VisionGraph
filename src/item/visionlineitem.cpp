#include "visionlineitem.h"
#include <QDebug>
#include <QPainterPath>

#include "../control/color.h"

VisionLineItem::VisionLineItem(QPointF p1, QPointF p2, bool bEdit, qreal penWidth, QColor penColor, VisionItem *parent) : VisionItem(parent)
{
    m_pointF1 = p1;m_pointF2 = p2;
    m_penColor = penColor;
    m_penWidth = penWidth;
    m_bEditStatus = bEdit;
    m_type = ItemType::Line;
    if(m_bEditStatus){
        m_bSelected = true;
    }else{
        m_bSelected = true;
    }
    setEdit(m_bSelected);

    m_miniRect1 = new MiniRect(m_pointF1.x()-5,m_pointF1.y()-5,10,10,QColor(255,0,0),this);
    m_miniRect1->setIndex(1);
    connect(m_miniRect1,SIGNAL(signalIndex(int)),this,SLOT(slotMiniRectIndex(int)));
    m_miniRect2 = new MiniRect(m_pointF2.x()-5,m_pointF2.y()-5,10,10,QColor(255,0,0),this);
    m_miniRect2->setIndex(2);
    connect(m_miniRect2,SIGNAL(signalIndex(int)),this,SLOT(slotMiniRectIndex(int)));
    updateRect(m_pointF1,m_pointF2);
}

void VisionLineItem::setLine(QPointF p1, QPointF p2)
{
    m_pointF1 = p1;
    m_pointF2 = p2;
    m_miniRect1->setRect(m_pointF1.x()-5,m_pointF1.y()-5,10,10);
    m_miniRect2->setRect(m_pointF2.x()-5,m_pointF2.y()-5,10,10);

    updateRect(m_pointF1,m_pointF2);
}

void VisionLineItem::setEditStatus(bool edit)
{
    m_bEditStatus = edit;
}

void VisionLineItem::setPenWidth(qreal penWidth)
{
    m_penWidth = penWidth;
}

void VisionLineItem::setPenColor(QColor color)
{
    m_penColor = color;
}

bool VisionLineItem::getPosInArea(qreal x, qreal y)
{

    qreal A = m_pointF2.y() - m_pointF1.y();
    qreal B = m_pointF1.x() - m_pointF2.x();
    qreal C = m_pointF2.x()*m_pointF1.y() - m_pointF1.x()*m_pointF2.y();

    qreal l = fabs(A*x + B*y + C)/sqrt(A*A+B*B);
    if( l < 5 || this->cursor().shape() == Qt::SizeAllCursor){
        return true;
    }else{
        return false;
    }
}

QRectF VisionLineItem::boundingRect() const
{
    return QRectF(m_x-5,m_y-5,m_width+10,m_height+10);
}

void VisionLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    if(option->state & QStyle::State_Selected){
        painter->setPen(QPen(QBrush(selectedColor),0));

    }else{
        painter->setPen(QPen(QBrush(borderColor),0));

    }
//    if(pen)
    qDebug()<<painter->clipPath().currentPosition();
    painter->drawLine(m_pointF1,m_pointF2);
    painter->drawLine(QPointF(m_pointF2.x()-10,m_pointF2.y()-5),m_pointF2);
    painter->drawLine(QPointF(m_pointF2.x()-10,m_pointF2.y()+5),m_pointF2);

    if(!m_bEditStatus)
        return;

    //绘制编辑框
    if(option->state & QStyle::State_Selected){
        m_miniRect1->show();
        m_miniRect2->show();
        m_bSelected = true;
        setEdit(m_bSelected);
    }else{
        m_miniRect1->hide();
        m_miniRect2->hide();
        m_bSelected = false;
        setEdit(m_bSelected);
    }
}

void VisionLineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //            A = Y2 - Y1
    //            B = X1 - X2
    //            C = X2*Y1 - X1*Y2
    QGraphicsItem::mousePressEvent(event);

    if(!m_bEditStatus)
        return;

    qreal A = m_pointF2.y() - m_pointF1.y();
    qreal B = m_pointF1.x() - m_pointF2.x();
    qreal C = m_pointF2.x()*m_pointF1.y() - m_pointF1.x()*m_pointF2.y();
    m_lastPointF = event->scenePos();
    qreal l = fabs(A*event->scenePos().x() + B*event->scenePos().y() + C)/sqrt(A*A+B*B);

    qDebug()<<"l:: "<<l<<A<<B<<C;
    if(l < 5 || this->cursor().shape() == Qt::SizeAllCursor){
        qDebug()<<"in area";
        setSelected(true);
    }else{
        qDebug()<<"out area";
        setSelected(false);
//        m_iIndex = -1;
        this->scene()->update();
        return;
    }
    this->scene()->update();
}

void VisionLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEditStatus)
        return;

    if(!m_bSelected)
        return;

//    QGraphicsItem::mouseMoveEvent(event);
    QPointF disPointF = event->scenePos()-m_lastPointF;
    m_lastPointF = event->scenePos();
    if(m_iIndex == 1){
        m_pointF1 = event->scenePos();
    }else if(m_iIndex == 2){
        m_pointF2 = event->scenePos();
    }else{
        //移动整体
        m_pointF1 = m_pointF1 + disPointF;
        m_pointF2 = m_pointF2 + disPointF;
    }
    updateRect(m_pointF1,m_pointF2);
    this->scene()->update();
}

void VisionLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEditStatus)
        return;

    qreal A = m_pointF2.y() - m_pointF1.y();
    qreal B = m_pointF1.x() - m_pointF2.x();
    qreal C = m_pointF2.x()*m_pointF1.y() - m_pointF1.x()*m_pointF2.y();

    qreal l = fabs(A*event->scenePos().x() + B*event->scenePos().y() + C)/sqrt(A*A+B*B);
    if( l < 5 || this->cursor().shape() == Qt::SizeAllCursor){
        emit signal_clicked(this,true,true,event->scenePos().x(),event->scenePos().y());
        QGraphicsItem::mouseReleaseEvent(event);
    }else{
        emit signal_clicked(this,true,false,event->scenePos().x(),event->scenePos().y());
        return;
    }
}

void VisionLineItem::updateRect(QPointF p1, QPointF p2)
{
    if(p1.x() < p2.x()){
        m_x = p1.x();
    }else{
        m_x = p2.x();
    }

    if(p1.y() < p2.y()){
        m_y = p1.y();
    }else{
        m_y = p2.y();
    }
    m_width = fabs(p1.x()-p2.x());
    m_height = fabs(p1.y()-p2.y());

    m_miniRect1->setPos(m_pointF1.x()-5,m_pointF1.y()-5);
    m_miniRect2->setPos(m_pointF2.x()-5,m_pointF2.y()-5);

}

void VisionLineItem::slotMiniRectIndex(int index)
{
    if(index == 1){
        //移动点1
        m_iIndex = 1;
        this->scene()->views().at(0)->setCursor(Qt::SizeAllCursor);
    }else if(index == 2){
        //移动点2
        m_iIndex = 2;
        this->scene()->views().at(0)->setCursor(Qt::SizeAllCursor);
    }else{
        //恢复正常
        m_iIndex = -1;
        this->scene()->views().at(0)->setCursor(viewCursor);
    }
}

#include "visionchainitem.h"
#include <QCursor>
#include <QDebug>
#include <QList>

#include "../control/color.h"

VisionChainItem::VisionChainItem(bool edit, bool bClosed, QObject *parent) : QObject(parent)
{
//    setAcceptHoverEvents(true);
    m_borderColor = borderColor;
    m_brushColor = brushColor;
    m_selectedColor = m_selectedColor;

    m_pointFColor = borderColor;
    m_lstChainPoint.clear();
    m_bEdit = edit;
    m_bClosed = bClosed;
}


void VisionChainItem::setChainPos(QList<qreal> lst_x, QList<qreal> lst_y)
{
    if(lst_x.count() <= 1){
        //data error; if count is 1,then it is a point
        qDebug()<<"setChainPos is error and Pos is null";
        return;
    }

    for(int i=0;i<lst_x.count();i++){
        m_lstChainPoint.append(QPointF(lst_x[i],lst_y[i]));
        MiniRect* rectItem = new MiniRect(lst_x[i]-2.5,lst_y[i]-2.5,5,5,QColor(255,0,0),this);
        rectItem->hide();
        m_lstMiniRect.append(rectItem);
    }

    m_lst_x = lst_x;m_lst_y = lst_y;
    //获取链表的最大最小值--排序
    qSort(lst_x.begin(), lst_x.end());
    qSort(lst_y.begin(), lst_y.end());
    m_x1 = lst_x[0];m_x2 = lst_x[lst_x.count()-1];m_y1 = lst_y[0];m_y2 = lst_y[lst_y.count()-1];
    update();
}

void VisionChainItem::setChainPos(QList<QPointF> lst_p)
{
    if(lst_p.count() <= 1){
        //data error; if count is 1,then it is a point
        qDebug()<<"setChainPos is error and Pos is null";
        return;
    }

    m_lstChainPoint = lst_p;
    for(int i=0;i<lst_p.count();i++){
        m_lst_x.append(lst_p[i].x());
        m_lst_y.append(lst_p[i].y());
        MiniRect* rectItem = new MiniRect(lst_p[i].x()-2.5,lst_p[i].y()-2.5,5,5,QColor(255,0,0),this);
        rectItem->hide();
        m_lstMiniRect.append(rectItem);
    }
//    m_lst_x = lst_x;m_lst_y = lst_y;
    //获取链表的最大最小值--排序
    qSort(m_lst_x.begin(), m_lst_x.end());
    qSort(m_lst_y.begin(), m_lst_y.end());
    m_x1 = m_lst_x[0];m_x2 = m_lst_x[m_lst_x.count()-1];m_y1 = m_lst_y[0];m_y2 = m_lst_y[m_lst_y.count()-1];
    update();
}

bool VisionChainItem::addPointF(QPointF pointF)
{
    m_lstPointF.append(pointF);
    if(boundingRect().contains(pointF)){
        return true;
    }else{
        return false;
    }
}

bool VisionChainItem::removePointF(QPointF pointF)
{
    if(m_lstPointF.contains(pointF)){
        m_lstPointF.removeOne(pointF);
        return true;
    }else{
        return false;
    }
}

void VisionChainItem::setPointFColor(const QColor &color)
{
    m_pointFColor = color;
}

QList<QPointF> VisionChainItem::getChainPoints()
{
    return m_lstPointF;
}

QVector<QPointF> VisionChainItem::getPoints()
{
    return m_lstChainPoint.toVector();
}


void VisionChainItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 反走样
    painter->setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色
    if(m_selected){
        painter->setPen(QPen(QBrush(m_selectedColor),0));
        painter->setBrush(m_selectedColor);
    }else{
        painter->setPen(QPen(QBrush(m_borderColor),0));
        painter->setBrush(m_borderColor);
    }

    // 绘制直线
    QPointF p1,p2;
    qreal d = 3;
    if(m_bClosed){
        //是封闭图形
        for(int i =0;i<m_lstChainPoint.count();i++){
            if(i == m_lstChainPoint.count()-1){
                p1=m_lstChainPoint[i];
                p2=m_lstChainPoint[0];
            }else{
                p1=m_lstChainPoint[i];
                p2=m_lstChainPoint[i+1];
            }
            painter->drawLine(p1,p2);

            qreal alph = atan2(p2.y()-p1.y(), p2.x()-p1.x());
            painter->translate(p2);
            qreal angle = (alph*180)/3.14159;
            painter->rotate(angle);
            painter->drawLine(QPointF(-(d*2),-d),QPointF(0,0));
            painter->drawLine(QPointF(-(d*2),+d),QPointF(0,0));
            painter->drawLine(QPointF(-(d*2),+d),QPointF(-(d*2),-d));

            painter->rotate(-angle);
            painter->translate(QPointF(-p2.x(),-p2.y()));
        }
    }else{
        //不是封闭图形
        for(int i =0;i<m_lstChainPoint.count()-1;i++){
            p1=m_lstChainPoint[i];
            p2=m_lstChainPoint[i+1];

            painter->drawLine(p1,p2);

            qreal alph = atan2(p2.y()-p1.y(), p2.x()-p1.x());
            painter->translate(p2);
            qreal angle = (alph*180)/3.14159;
            painter->rotate(angle);
            painter->drawLine(QPointF(-(d*2),-d),QPointF(0,0));
            painter->drawLine(QPointF(-(d*2),+d),QPointF(0,0));
            painter->drawLine(QPointF(-(d*2),+d),QPointF(-(d*2),-d));

            painter->rotate(-angle);
            painter->translate(QPointF(-p2.x(),-p2.y()));
        }
    }


    //绘制添加的点
    painter->setPen(QPen(QBrush(m_pointFColor),0));
    for(int j=0;j<m_lstPointF.count();j++){
        painter->drawLine(QPointF(m_lstPointF[j].x(),m_lstPointF[j].y()-1),QPointF(m_lstPointF[j].x(),m_lstPointF[j].y()+1));
        painter->drawLine(QPointF(m_lstPointF[j].x()-1,m_lstPointF[j].y()),QPointF(m_lstPointF[j].x()+1,m_lstPointF[j].y()));
    }


    //绘制矩形框  -- 每个点绑定一个矩形框
    if(m_selected){
        for(int i=0;i<m_lstMiniRect.count();i++){
            m_lstMiniRect[i]->show();
        }
    }else{
        for(int i=0;i<m_lstMiniRect.count();i++){
            m_lstMiniRect[i]->hide();
        }
    }
}

QRectF VisionChainItem::boundingRect() const
{
    //根据坐标绘制一个矩形将线条包住
    if(m_x1 <= m_x2)
    {
        if(m_y1 <= m_y2){
            return QRectF(m_x1,m_y1,m_x2-m_x1,m_y2-m_y1);
        }else{
            return QRectF(m_x1,m_y2,m_x2-m_x1,m_y1-m_y2);
        }
    }else{
        if(m_y1 <= m_y2){
            return QRectF(m_x2,m_y1,m_x1-m_x2,m_y2-m_y1);
        }else{
            return QRectF(m_x2,m_y2,m_x1-m_x2,m_y1-m_y2);
        }
    }
}

void VisionChainItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug()<<"mouse move line";
    QGraphicsItem::mouseMoveEvent(event);
}

void VisionChainItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug()<<"mouse release event";
    QGraphicsItem::mouseReleaseEvent(event);

}

void VisionChainItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

    if(m_selected){
        m_selected = false;
    }else{
        m_selected = true;
    }
    update();
}

//void VisionChainItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
//{
//}

//void VisionChainItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
//{
////    setCursor(QCursor(Qt::CrossCursor));
//}

//void VisionChainItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
//{
////    setCursor(QCursor(Qt::ArrowCursor));
////    qDebug()<<"hover leave";
//}

QRectF VisionChainItem::addRect()
{
    if(m_x1 <= m_x2)
    {
        if(m_y1 <= m_y2){
            return QRectF(m_x1,m_y1,m_x2-m_x1,m_y2-m_y1);
        }else{
            return QRectF(m_x1,m_y2,m_x2-m_x1,m_y1-m_y2);
        }
    }else{
        if(m_y1 <= m_y2){
            return QRectF(m_x2,m_y1,m_x1-m_x2,m_y2-m_y1);
        }else{
            return QRectF(m_x2,m_y2,m_x1-m_x2,m_y1-m_y2);
        }
    }
}


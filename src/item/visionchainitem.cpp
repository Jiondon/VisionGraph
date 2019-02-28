#include "visionchainitem.h"
#include <QCursor>
#include <QDebug>
#include <QList>

#include "../control/color.h"

VisionChainItem::VisionChainItem(bool bClosed, bool edit, QColor color, QObject *parent) : QObject(parent)
{
//    setAcceptHoverEvents(true);
    m_borderColor = borderColor;
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;

    m_pointFColor = borderColor;
    m_lstChainPoint.clear();
    m_bEdit = edit;
    if(m_bEdit){
        setSelectedStatus(true);
    }else{
        setSelectedStatus(false);
    }
    m_bClosed = bClosed;

    m_polygonF = new QPolygonF;;
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
        rectItem->setIndex(i);
        QObject::connect(rectItem,SIGNAL(signalIndex(int)),this,SLOT(slotMiniRectIndex(int)));
        rectItem->hide();
        m_lstMiniRect.append(rectItem);
    }
    m_polygonF->clear();
    m_polygonF->append(m_lstChainPoint.toVector());

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

    m_polygonF->clear();
    m_polygonF->append(m_lstChainPoint.toVector());

    for(int i=0;i<lst_p.count();i++){
        m_lst_x.append(lst_p[i].x());
        m_lst_y.append(lst_p[i].y());
        MiniRect* rectItem = new MiniRect(lst_p[i].x()-2.5,lst_p[i].y()-2.5,5,5,QColor(255,0,0),this);
        rectItem->setIndex(i);
//        rectItem->setBrushEnable(false);
        QObject::connect(rectItem,SIGNAL(signalIndex(int)),this,SLOT(slotMiniRectIndex(int)));
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

bool VisionChainItem::getPosInArea(qreal x, qreal y){
    if(m_polygonF->containsPoint(QPointF(x,y),Qt::OddEvenFill)){
        return true;
    }else{
        return false;
    }
}


void VisionChainItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 反走样
    painter->setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色
    if(option->state & QStyle::State_Selected){
        painter->setPen(QPen(QBrush(m_selectedColor),0));
        painter->setBrush(m_selectedColor);
    }else{
        painter->setPen(QPen(QBrush(m_borderColor),0));
        painter->setBrush(m_borderColor);
    }

    // 绘制直线
    QPointF p1,p2;
    qreal d = 2; //箭头方向的大小基数
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
//            painter->drawPolygon({QPointF(-(d*2),-d),QPointF(0,0),QPointF(-(d*2),+d)});

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
//            painter->drawPolygon({QPointF(-(d*2),-d),QPointF(0,0),QPointF(-(d*2),+d)});

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


    if(!m_bEdit)
        return;

    //绘制矩形框  -- 每个点绑定一个矩形框
    if(option->state & QStyle::State_Selected){
        for(int i=0;i<m_lstMiniRect.count();i++){
            m_lstMiniRect[i]->show();
        }
        m_bSelected = true;
    }else{
        for(int i=0;i<m_lstMiniRect.count();i++){
            m_lstMiniRect[i]->hide();
        }
        m_bSelected = false;
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
    if(m_bEdit && m_bSelected){
        QPointF disPoint = event->scenePos() - m_lastPointF;
        if(m_iIndex == -1){
            //整体拖动
//            QGraphicsItem::mouseMoveEvent(event);  //采用Qt本身的拖动，数据不会跟着变化，只会改变pos属性，
            for(int i=0;i<m_lstChainPoint.count();i++){
                m_lstChainPoint[i] = m_lstChainPoint[i] + disPoint;
                m_lstMiniRect[i]->setRect(m_lstChainPoint[i].x()-2.5,m_lstChainPoint[i].y()-2.5,5,5);
            }
        }else{
            //拖动某一个点
            m_lstChainPoint[m_iIndex] = event->scenePos();
            m_lstMiniRect[m_iIndex]->setRect(event->scenePos().x()-2.5,event->scenePos().y()-2.5,5,5);
        }

        m_polygonF->clear();
        m_polygonF->append(m_lstChainPoint.toVector());

        updateData();
    }
    m_lastPointF = event->scenePos();
    this->scene()->update();
}

void VisionChainItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    if(!m_polygonF->containsPoint(event->scenePos(),Qt::OddEvenFill)){
        emit signal_clicked(this,true,false,event->scenePos().x(),event->scenePos().y());
        return;
    }
    emit signal_clicked(this,true,true,event->scenePos().x(),event->scenePos().y());
    QGraphicsItem::mouseReleaseEvent(event);

}

void VisionChainItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

    if(!m_bEdit)
        return;

    if(m_polygonF->containsPoint(event->pos(),Qt::OddEvenFill)){
        setSelectedStatus(true);
    }else{
        setSelectedStatus(false);
    }

    m_lastPointF = event->scenePos();
    this->scene()->update();
}

void VisionChainItem::updateData()
{
    for(int i=0;i<m_lstChainPoint.count();i++){
        m_lst_x.append(m_lstChainPoint[i].x());
        m_lst_y.append(m_lstChainPoint[i].y());
    }
//    m_lst_x = lst_x;m_lst_y = lst_y;
    //获取链表的最大最小值--排序
    qSort(m_lst_x.begin(), m_lst_x.end());
    qSort(m_lst_y.begin(), m_lst_y.end());
    m_x1 = m_lst_x[0];m_x2 = m_lst_x[m_lst_x.count()-1];m_y1 = m_lst_y[0];m_y2 = m_lst_y[m_lst_y.count()-1];
}

void VisionChainItem::slotMiniRectIndex(int index)
{
//    qDebug()<<index;
    m_iIndex = index;
    if(index == -1){
        this->scene()->views().at(0)->setCursor(viewCursor);
    }else{
        this->scene()->views().at(0)->setCursor(Qt::SizeAllCursor);
    }
}


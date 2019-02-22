#include "visionarcitem.h"
#include <QDebug>

#define Pi 3.1415926


VisionArcItem::VisionArcItem(bool bEdit, QColor color, VisionItem *parent) : VisionItem(parent)
{
    m_borderColor = borderColor;
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;

    m_bEdit = bEdit;
    if(m_bEdit){
        setSelectedStatus(true);
    }else{
        setSelectedStatus(false);
    }
}

void VisionArcItem::setPointFs(QPointF sP, QPointF mP, QPointF fP)
{
    m_p1 = sP;
    m_p2 = mP;
    m_p3 = fP;
    //生成对应的boundingRect范围
    detailData(sP,mP,fP);
    m_x = m_center.x() - m_r;
    m_y = m_center.y() - m_r;
    this->setPos(m_x,m_y);
    initMiniRect();
}

QVector<QPointF> VisionArcItem::getPoints()
{
    QVector<QPointF> vec_p;
    vec_p.append(m_p1);
    vec_p.append(m_p2);
    vec_p.append(m_p3);
    return vec_p;
}

bool VisionArcItem::getPosInArea(qreal x, qreal y){
    //x,y是外部坐标，
    //在圆弧的范围内要满足两个条件：1，点在圆弧附近，误差设为5；2，点的角度要在m_angle到m_angle+m_spanAngle范围角度误差也设为5
    double d = hypot(m_center.x()-x,m_center.y()-y) - m_r;
    double x1 = x-m_center.x();
    double y1 = y-m_center.y();
    double angle = acos((x1)/(hypot(x1,y1)));
    //(x1,y1)表示原点为圆心，r半斤的圆上的一点，y1<0 表示在三四象限，
    if(y1 < 0){
        angle = 2*Pi - angle;
    }else{
        angle = angle;
    }
    //转换角度为数学坐标系，并转化为具体度数
    angle = 360-angle*180/Pi;

    qDebug()<<d<<angle<<m_angle<<m_angle+m_spanAngle;
    if(fabs(d) < 5){
        if(m_angle+m_spanAngle <= 360 && (angle >= (m_angle-5) && angle < (m_angle+m_spanAngle+5))){
            qDebug()<<"arc in area";
            return true;
        }else if(m_angle+m_spanAngle > 360 && (angle >= (m_angle-5) && angle < 360)){
            qDebug()<<"arc in area";
            return true;
        }else if(m_angle+m_spanAngle > 360 && (angle >= 0 && angle < (m_angle+m_spanAngle-360+5))){
            qDebug()<<"arc in area";
            return true;
        }else{
            qDebug()<<"arc out area";
            return false;
        }
    }else{
        qDebug()<<"arc out area";
        return false;
    }
}

void VisionArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);
    if(option->state & QStyle::State_Selected){
        painter->setPen(QPen(QBrush(m_selectedColor),0));
    }else{
        painter->setPen(QPen(QBrush(m_borderColor),0));
    }

    painter->drawArc(QRectF(0,0,2*m_r,2*m_r),m_angle*16,m_spanAngle*16);

    if(!m_bEdit)
        return;

    if(option->state & QStyle::State_Selected){
        m_sMiniRect->show();
        m_mMiniRect->show();
        m_fMiniRect->show();
    }else{
        m_sMiniRect->hide();
        m_mMiniRect->hide();
        m_fMiniRect->hide();

        //todo 中间的编辑点调整到中间位置
//        m_p2 = m_arc_center;
//        m_mMiniRect->setRect(m_p2.x()-2.5,m_p2.y()-2.5,5,5);
    }
}

QRectF VisionArcItem::boundingRect() const
{
    QRectF rf = QRectF(0,0,2*m_r,2*m_r);
    return rf;
}

void VisionArcItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    if(!m_bSelected)
        return;

    //在执行QGraphicsItem的时候。会自动的进行pos的重新设置
    QGraphicsItem::mouseMoveEvent(event);

    if(m_iIndex == -1){
        QPointF disPoint = event->scenePos() - m_lastPoint_Press;
        m_lastPoint_Press = event->scenePos();
        //整体move
        m_p1 = m_p1 + disPoint;
        m_p2 = m_p2 + disPoint;
        m_p3 = m_p3 + disPoint;
    }else{
        //移动某一个点
        if(m_iIndex == 1){
            m_p1 = event->scenePos();
        }else if(m_iIndex == 2){
            m_p2 = event->scenePos();
        }else if(m_iIndex == 3){
            m_p3 = event->scenePos();
        }
    }
    detailData(m_p1,m_p2,m_p3);
    m_x = m_center.x() - m_r;
    m_y = m_center.y() - m_r;
    m_sMiniRect->setRect(m_p1.x()-2.5-m_x,m_p1.y()-2.5-m_y,5,5);
    m_mMiniRect->setRect(m_p2.x()-2.5-m_x,m_p2.y()-2.5-m_y,5,5);
    m_fMiniRect->setRect(m_p3.x()-2.5-m_x,m_p3.y()-2.5-m_y,5,5);
    this->setPos(m_x,m_y);
    this->scene()->update();
}

void VisionArcItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    QGraphicsItem::mousePressEvent(event);


    if(!getPosInArea(event->scenePos().x(),event->scenePos().y())){
        setSelectedStatus(false);
        return;
    }

    setSelectedStatus(true);
    m_lastPoint_Press = event->scenePos();
}

void VisionArcItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    if(!getPosInArea(event->scenePos().x(),event->scenePos().y())){
        return;
    }

    double x=event->scenePos().x();
    double y=event->scenePos().y();
    double d = hypot(m_center.x()-x,m_center.y()-y) - m_r;
    double x1 = x-m_center.x();
    double y1 = y-m_center.y();
    double angle = acos((x1)/(hypot(x1,y1)));
    //(x1,y1)表示原点为圆心，r半斤的圆上的一点，y1<0 表示在三四象限，
    if(y1 < 0){
        angle = 2*Pi - angle;
    }else{
        angle = angle;
    }
    //转换角度为数学坐标系，并转化为具体度数
    angle = 360-angle*180/Pi;

    qDebug()<<d<<angle<<m_angle<<m_angle+m_spanAngle;
    if(fabs(d) < 5){
        if(m_angle+m_spanAngle <= 360 && (angle >= (m_angle-5) && angle < (m_angle+m_spanAngle+5))){
            qDebug()<<"arc in area";
            emit signal_clicked(this,true,false,event->scenePos().x(),event->scenePos().y());
            QGraphicsItem::mouseReleaseEvent(event);
            return ;
        }else if(m_angle+m_spanAngle > 360 && (angle >= (m_angle-5) && angle < 360)){
            qDebug()<<"arc in area";
            emit signal_clicked(this,true,false,event->scenePos().x(),event->scenePos().y());
            QGraphicsItem::mouseReleaseEvent(event);
            return ;
        }else if(m_angle+m_spanAngle > 360 && (angle >= 0 && angle < (m_angle+m_spanAngle-360+5))){
            qDebug()<<"arc in area";
            emit signal_clicked(this,true,false,event->scenePos().x(),event->scenePos().y());
            QGraphicsItem::mouseReleaseEvent(event);
            return ;
        }else{
            qDebug()<<"arc out area";
            emit signal_clicked(this,true,true,event->scenePos().x(),event->scenePos().y());
            return ;
        }
    }else{
        qDebug()<<"arc out area";
        emit signal_clicked(this,true,true,event->scenePos().x(),event->scenePos().y());
        return ;
    }

    emit signal_clicked(this,true,true,event->scenePos().x(),event->scenePos().y());

}

void VisionArcItem::initMiniRect()
{
    if(m_sMiniRect == NULL){
        m_sMiniRect = new MiniRect(m_p1.x()-2.5-m_x,m_p1.y()-2.5-m_y,5,5,QColor(255,0,0),this);
        m_sMiniRect->setIndex(1);
        QObject::connect(m_sMiniRect,SIGNAL(signalIndex(int)),this,SLOT(slotMiniRectIndex(int)));
        m_sMiniRect->hide();
    }else{
        m_sMiniRect->setRect(m_p1.x()-2.5-m_x,m_p1.y()-2.5-m_y,5,5);
    }

    if(m_mMiniRect == NULL){
        m_mMiniRect = new MiniRect(m_p2.x()-2.5-m_x,m_p2.y()-2.5-m_y,5,5,QColor(255,0,0),this);
        m_mMiniRect->setIndex(2);
        QObject::connect(m_mMiniRect,SIGNAL(signalIndex(int)),this,SLOT(slotMiniRectIndex(int)));
        m_mMiniRect->hide();
    }else{
        m_mMiniRect->setRect(m_p2.x()-2.5-m_x,m_p2.y()-2.5-m_y,5,5);
    }

    if(m_fMiniRect == NULL){
        m_fMiniRect = new MiniRect(m_p3.x()-2.5-m_x,m_p3.y()-2.5-m_y,5,5,QColor(255,0,0),this);
        m_fMiniRect->setIndex(3);
        QObject::connect(m_fMiniRect,SIGNAL(signalIndex(int)),this,SLOT(slotMiniRectIndex(int)));
        m_fMiniRect->hide();
    }else{
        m_fMiniRect->setRect(m_p3.x()-2.5-m_x,m_p3.y()-2.5-m_y,5,5);
    }
}

bool VisionArcItem::detailData(QPointF sP, QPointF mP, QPointF fP)
{
    //三点确定一个圆,硬解，可得到表达式（三点一线的时候，则无法形成圆）
    double x1 = sP.x(), x2 = mP.x(), x3 = fP.x();
    double y1 = sP.y(), y2 = mP.y(), y3 = fP.y();
    double a = x1 - x2;
    double b = y1 - y2;
    double c = x1 - x3;
    double d = y1 - y3;
    double e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2.0;
    double f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2.0;
    double det = b * c - a * d;

    if((x1 == x2 && x1 == x3) || (y1 == y2 && y1 == y3))
    {
        //三点一线,
        return false;
    }

    double x0 = -(d * e - b * f) / det;
    double y0 = -(a * f - c * e) / det;
    m_center.setX(x0);
    m_center.setY(y0);
    m_r = hypot(x1 - x0, y1 - y0);

    //计算每个点和圆心所形成的的角度
    double angle1 = acos((x1-x0)/(hypot((x1-x0),(y1-y0))));
    double angle2 = acos((x2-x0)/(hypot((x2-x0),(y2-y0))));
    double angle3 = acos((x3-x0)/(hypot((x3-x0),(y3-y0))));
    if(y1-y0 < 0){
        angle1 = 2*Pi - angle1;
    }else{
        angle1 = angle1;
    }
    if(y3-y0 < 0){
        angle3 = 2*Pi - angle3;
    }else{
        angle3 = angle3;
    }

    if(y2-y0 < 0){
        angle2 = 2*Pi - angle2;
    }else{
        angle2 = angle2;
    }

    //上面计算的角度是基于QGraphicsView中的坐标，需要进行转换为数学坐标中的角度
    angle1 = 360-angle1*180/Pi;
    angle2 = 360-angle2*180/Pi;
    angle3 = 360-angle3*180/Pi;

//    qDebug()<<angle1<<angle2<<angle3;
    if(angle1 < angle3){
        //1是起点，3是终点
        if(angle2 < angle3 && angle2 > angle1){
            //2在中间，1-2-3
            m_angle = angle1;
            m_spanAngle = angle3 - angle1;
        }else{
            // 2在1-3外面   3-2-1
            m_angle = angle3;
            m_spanAngle = 360-(angle3 - angle1);
        }
    }else{
        //3是起点，1是终点  正方向--  3-2-1
        if(angle2 < angle1 && angle2 > angle3){
            //3-2-1
            m_angle = angle3;
            m_spanAngle = angle1 - angle3;
        }else{
            //1-2-3
            m_angle = angle1;
            m_spanAngle = 360-(angle1 - angle3);
        }
    }
//    m_arc_center = m_center + QPointF(m_r*cos((m_angle+m_spanAngle/2)),m_r*sin((m_angle+m_spanAngle/2)));
//    qDebug()<<m_angle<<m_spanAngle;
    return true;
}

void VisionArcItem::slotMiniRectIndex(int index)
{
    m_iIndex = index;
    if(index == -1){
        this->scene()->views().at(0)->setCursor(viewCursor);
    }else{
        this->scene()->views().at(0)->setCursor(Qt::SizeAllCursor);
    }
}

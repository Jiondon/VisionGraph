#include "visionarcitem.h"
#include <QDebug>

#define Pi 3.1415926


VisionArcItem::VisionArcItem(bool bEdit, QColor color, VisionItem *parent) : VisionItem(parent)
{

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
}

QVector<QPointF> VisionArcItem::getPoints()
{
    QVector<QPointF> vec_p;
    vec_p.append(m_p1);
    vec_p.append(m_p2);
    vec_p.append(m_p3);
    return vec_p;
}

void VisionArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(QBrush(Qt::red),0));

//    painter->drawLine(QPointF(m_pointF.x()-m_iLength,m_pointF.y()),QPointF(m_pointF.x()+m_iLength,m_pointF.y()));

    painter->drawArc(boundingRect(),m_angle*16,m_spanAngle*16);

    painter->drawLine(m_center,m_p1);
    painter->setPen(QPen(QBrush(Qt::green),0));
    painter->drawLine(m_center,m_p2);
    painter->setPen(QPen(QBrush(Qt::blue),0));
    painter->drawLine(m_center,m_p3);

//    painter->drawRect(boundingRect());
//    painter->drawEllipse(boundingRect());

}

QRectF VisionArcItem::boundingRect() const
{
    QRectF rf = QRectF(m_x,m_y,2*m_r,2*m_r);
    return rf;
}

void VisionArcItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void VisionArcItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void VisionArcItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

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

//    if( fabs(det) < 1e-5)
//    {
//        radius = -1;
//        return QPointF(0,0);
//    }

    double x0 = -(d * e - b * f) / det;
    double y0 = -(a * f - c * e) / det;
    m_center.setX(x0);
    m_center.setY(y0);
    m_r = hypot(x1 - x0, y1 - y0);

    //
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

    qDebug()<<angle1<<angle2<<angle3;
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

    qDebug()<<m_angle<<m_spanAngle;
    return true;
}

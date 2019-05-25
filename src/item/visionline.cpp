#include "visionline.h"
#include "../control/color.h"


#include <QGraphicsScene>
#include <QGraphicsView>


VisionLine::VisionLine(bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor, VisionItem *parent) : VisionItem(parent)
{
    if(color_enable){
        m_borderColor = borderColor;
    }else{
        m_borderColor = borderColor;
    }
    m_borderColor = borderColor;
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;
}

void VisionLine::setLine(QLineF lineF)
{
    m_lineF = lineF;
    m_style = SINGLE;
}

void VisionLine::setLines(QList<QLineF> lstLineF)
{
    if(lstLineF.count() <= 0){
        m_lineF = QLineF(0,0,0,0);
        m_style = SINGLE;
    }else if(lstLineF.count() == 1){
        m_lineF = lstLineF.first();
        m_style = SINGLE;
    }else{
        m_lstLineF = lstLineF;
        m_style = MULTI;
    }
}

QVector<QPointF> VisionLine::getPoints()
{
    QVector<QPointF> vec_p;
//    if(m_style == MULTI){
//        for(int i=0;i<m_lstLineF.count();i++){
//            vec_p.append(m_lstPointF[i]);
//        }
//    }else{
//        vec_p.append(m_pointF);
//    }
    return vec_p;
}

bool VisionLine::getPosInArea(qreal x, qreal y)
{
    return false;
}

void VisionLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen = QPen(m_borderColor,g_penWidth*(1/this->scene()->views().at(0)->matrix().m22()));
    painter->setPen(pen);
//    painter->setBrush(Qt::red);
    if(m_style == SINGLE){
        painter->drawLine(m_lineF);
    }else{
        painter->drawLines(m_lstLineF.toVector());
    }
}

QRectF VisionLine::boundingRect() const
{
    if(m_style == SINGLE){
        return QRectF(m_lineF.p1(),m_lineF.p2());
    }else{
        return QRectF(m_lstLineF.first().p1(),m_lstLineF.last().p2());
    }
}

void VisionLine::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    return;
}

void VisionLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    return;
}

void VisionLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    return;
}

#include "visionpoint.h"
#include "../control/color.h"

VisionPoint::VisionPoint(bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor, VisionItem *parent) : VisionItem(parent)
{
    m_type = ItemType::Paint_Point;
    if(color_enable){
        m_borderColor = borderColor;
    }else{
        m_borderColor = borderColor;
    }
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;
    setEnabled(false);
}

void VisionPoint::setPointF(QPointF pointF)
{
    m_style = SINGLE;
    m_pointF = pointF;
}

void VisionPoint::setPointFs(QList<QPointF> lstP)
{
    if(lstP.count() <= 0){
        m_pointF = QPointF(0,0);
        m_style = SINGLE;

    }else if(lstP.count() == 1){
        m_pointF = lstP.first();
        m_style = SINGLE;

    }else{
        m_lstPointF = lstP;
        m_style = MULTI;

    }
}

QVector<QPointF> VisionPoint::getPoints(){
    QVector<QPointF> vec_p;
    if(m_style == MULTI){
        for(int i=0;i<m_lstPointF.count();i++){
            vec_p.append(m_lstPointF[i]);
        }
    }else{
        vec_p.append(m_pointF);
    }
    return vec_p;
}

bool VisionPoint::getPosInArea(qreal x, qreal y)
{
    return false;
}

void VisionPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen = QPen(m_borderColor,g_penWidth*(1/g_scale));
    painter->setPen(pen);
//    painter->setBrush(Qt::red);
//    painter->drawEllipse(m_pointF,1,1);
//    painter->drawEllipse(QPointF(m_pointF.x()+2,m_pointF.y()),1,1);
    if(m_style == SINGLE){
        painter->drawPoint(m_pointF);
    }else{
        painter->drawPoints(m_lstPointF.toVector());
    }
}

QRectF VisionPoint::boundingRect() const
{
    if(m_style == SINGLE){
        return QRectF(m_pointF-QPointF(1,1),m_pointF+QPointF(1,1));
    }else{
        return QRectF(m_lstPointF.first()-QPointF(1,1),m_lstPointF.last()+QPointF(1,1));
    }
}

void VisionPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    return;
}

void VisionPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   return;
}

void VisionPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    return;
}

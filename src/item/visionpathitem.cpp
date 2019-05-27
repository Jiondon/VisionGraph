#include "visionpathitem.h"
#include "../control/color.h"
#include <QDebug>

VisionPathItem::VisionPathItem(bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor, VisionItem *parent) : VisionItem(parent)
{
    if(color_enable){
        m_borderColor = borderColor;
    }else{
        m_borderColor = borderColor;
    }
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;

    setFlag(QGraphicsItem::ItemIsMovable,false);
    m_type = ItemType::Paint_Poly;
    setSelectedStatus(false);
}

VisionPathItem::~VisionPathItem()
{

}

void VisionPathItem::setPointFs(QVector<QVector<QPointF>> vec_vec_pointF)
{
    m_vec_vecPointF = vec_vec_pointF;

    //获取最小的x，y以及最大的x，y
    for(int i=0;i<vec_vec_pointF.count();i++){
        QPolygonF poly;
        poly.clear();
        for(int j=0;j<vec_vec_pointF.at(i).count();j++){
            m_polygonF_temp.append(vec_vec_pointF.at(i).at(j));
            poly.append(vec_vec_pointF.at(i).at(j));
        }
        m_vec_polygonF.append(poly);
    }
}

bool VisionPathItem::getPosInArea(qreal x, qreal y)
{
    return true;
}

void VisionPathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(QBrush(m_borderColor),g_penWidth*(1/this->scene()->views().at(0)->matrix().m22())));

    for(int i=0;i<m_vec_polygonF.count();i++){
        painter->drawPolyline(m_vec_polygonF.at(i));
    }
//    painter->setPen(QPen(QBrush(QColor(0,255,0)),g_penWidth*(1/this->scene()->views().at(0)->matrix().m22())));
//    painter->drawRect(boundingRect());
}

QRectF VisionPathItem::boundingRect() const
{
    QRectF rf = QRectF(m_polygonF_temp.boundingRect().x()-5,m_polygonF_temp.boundingRect().y()-5,
                       m_polygonF_temp.boundingRect().width()+10,m_polygonF_temp.boundingRect().height()+10);
    return rf;
}


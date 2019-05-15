﻿#include "visiontextitem.h"

VisionTextItem::VisionTextItem(VisionItem *parent) : VisionItem(parent)
{

}

void VisionTextItem::setData(VGRegion vgRegion, QString textName)
{
    m_vgRegion = vgRegion;
    m_strText = textName;

    QLineF lineF;
    m_vecLines.clear();
    for(int i=0;i<m_vgRegion.arrayPointRun.size();i++){
        VGPointRun pointRun = m_vgRegion.arrayPointRun.at(i);
        lineF.setPoints((QPointF(pointRun.x,pointRun.y)),
                        (QPointF(pointRun.x+pointRun.length,pointRun.y)));
        m_vecLines.append(lineF);
    }
    //通过vgRegion计算rect

//    this->setPos();
}

void VisionTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen = QPen(QColor(255,0,0),g_penWidth*(1/g_scale));
    painter->setPen(pen);

    QVector<QLineF> vecLines;
    for(int i=0;i<m_vecLines.size();i++){
        QLineF lineF = QLineF((m_vecLines.at(i).p1()),(m_vecLines.at(i).p2()));
        vecLines.append(lineF);
    }
    painter.drawLines(vecLines);
}

void VisionTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void VisionTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void VisionTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

QRectF VisionTextItem::boundingRect() const
{
    return QRectF(0,0,100,100);
}

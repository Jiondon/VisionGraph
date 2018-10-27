#include "lineitem.h"

LineItem::LineItem(QGraphicsItem *parent):
    QGraphicsItem(parent)
{
    penColor = QColor(255,0,0);//black
    penWidth = 1;
}

QRectF LineItem::boundingRect() const
{
    return QRectF(m_x1,m_y1,m_x2,m_y2);
}

void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)
//    QGraphicsItem::paint(painter,option,widget);

//    int cnt = this->scene()->views().count();
//    for (int i =0;i<cnt;i++)
//    {
//        QGraphicsView *view = this->scene()->views().at(i);
//        QMatrix matrix = view->matrix();
//        qreal scale = matrix.m11();
//        qreal width = penWidth/scale;

//        painter->setPen(QPen(QBrush(penColor),width,penStyle));
////        painter->drawLine(QLineF(m_x1,m_y1,m_x2,m_y2));
//        painter->drawLines(m_lstPointF);
//    }
}

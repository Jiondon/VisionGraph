/****************************************************************************
** @brief       基于VIsionItem类封装的line类
** @note        单纯的绘制一条线，没有任何其他的变化，（类似于VisionLineItem）
** @author      xiaodongLi
** @date        create:2018-09-28
****************************************************************************/


#ifndef LINEITEM_H
#define LINEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QColor>
#include <QPointF>

class LineItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit LineItem(QGraphicsItem *parent = 0);

    /**
     * @brief       设置线的位置及大小
     */
    void setLine(qreal x1,qreal y1,qreal x2,qreal y2)
    {
        m_x1 = x1;
        m_y1 = y1;
        m_x2 = x2;
        m_y2 = y2;
    }

    /**
     * @brief       获得线的信息
     * @note        浮点
     */
    QLineF getPoint()
    {
        return QLine(m_x1,m_y1,m_x2,m_y2);
    }

    /**
     * @brief       设置画笔(线条)颜色
     * @param       color
     */
    void setPenColor(QColor color)
    {
        penColor = color;
    }

    /**
     * @brief       设置画笔(线条)宽度
     * @param       width
     */
    void setPenWidth(qreal width)
    {
        penWidth = width;
    }

    /**
     * @brief       设置画笔(线条)Style
     * @param       width
     */
    void setPenStyle(Qt::PenStyle style){
        penStyle = style;
    }

    /**
     * @brief       设置多条线的信息
     * @param       参数为点的集合，两两配对成线
     */
    void setLines(QList<QPointF> pointF){
        m_lstPointF = pointF;
    }

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    qreal m_x1,m_y1,m_x2,m_y2;
    QColor penColor;//画笔颜色 默认黑色
    qreal penWidth;//画笔宽度 默认1
    Qt::PenStyle penStyle = Qt::SolidLine;
    QList<QPointF> m_lstPointF;
};


#endif // LINEITEM_H

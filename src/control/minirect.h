/****************************************************************************
** @brief       矩形框
** @note        主要是作为其他的item在编辑状态下，提供一个可调节的有效控件
** @author      xiaodongLi
** @date        create:2018-09-28
** @example     矩形框的编辑情况下的边框上的八个小矩形
****************************************************************************/



#ifndef MINIRECT_H
#define MINIRECT_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QColor>
#include <QStyleOptionGraphicsItem>

class MiniRect : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MiniRect(qreal x,qreal y,qreal w,qreal h,QColor penColor = QColor(255,0,0),QGraphicsItem *parent = 0);

    /**
     * @brief  小矩形填充颜色使能
     */
    void setBrushEnable(bool brushEnable = true);

    /**
     * @brief  设置rectangle的x,y,w,h
     */
    void setRect(qreal x,qreal y,qreal w,qreal h);

    /**
     * @brief   标记--在存在多个miniRect的时候，方便进行单独处理
     */
    void setIndex(int index);

signals:
    void signalIndex(int index);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    int m_index = 0;
    qreal m_x = 0;
    qreal m_y = 0;
    qreal m_width = 0;
    qreal m_height = 0;

    QColor m_penColor = QColor(255,0,0);

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

    bool m_bBrushEnable = true;

public slots:
};

#endif // MINIRECT_H

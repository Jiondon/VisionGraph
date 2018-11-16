/****************************************************************************
** @brief       line类
** @note        可编辑的line，绘制完成后，可修改线的起点和终点，带有箭头的表示方向，默认起点指向终点
** @author      xiaodongLi
** @date        create:2018-09-28
** @example
****************************************************************************/


#ifndef VISIONLINEITEM_H
#define VISIONLINEITEM_H

#include <QObject>
#include <QPainter>
#include "../control/visionitem.h"
#include "../control/minirect.h"

class VISIONGRAPHSHARED_EXPORT VisionLineItem : public VisionItem
{
    Q_OBJECT
public:

    /**
     * @brief       构造函数
     * @param       对line的一些属性进行设置
     * @param       p1 p2 起点和终点 bEdit控制该line是否是可编辑的（起点终点可更改），penWidth penColor画笔的属性
     */
    explicit VisionLineItem(QPointF p1 = QPointF(0,0),QPointF p2 = QPointF(0,0),bool bEdit = true,qreal penWidth = 0,
                            QColor penColor = QColor(0,0,0),VisionItem *parent = 0);

    /**
     * @brief       设置线的起点和终点
     * @param       p1 p2 起点和终点
     */
    void setLine(QPointF p1,QPointF p2);


    /**
     * @brief       设置线的编辑属性
     * @param       bEdit控制该line是否是可编辑的（起点终点可更改）
     */
    void setEditStatus(bool edit);

    /**
     * @brief       设置画笔宽度
     */
    void setPenWidth(qreal penWidth);

    /**
     * @brief       设置画笔颜色
     */
    void setPenColor(QColor color);

    /**
     * @brief       判断点（x,y）是否在该item内
     * @param       bool
     */
    bool getPosInArea(qreal x, qreal y);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

private:
    qreal m_x=0;qreal m_y;qreal m_width=0;qreal m_height=0;
    QPointF m_pointF1 = QPointF(0,0);
    QPointF m_pointF2 = QPointF(0,0);
    qreal m_penWidth = 0;
    QColor m_penColor = QColor(0,0,0);
    bool m_bEditStatus = false;
    bool m_bSelected = false;

    int m_iIndex = -1;
    MiniRect* m_miniRect1 = nullptr;
    MiniRect* m_miniRect2 = nullptr;

    qreal m_angle = 0;  //角度
    QPointF m_lastPointF;

private:

    /**
     * @brief       miniRect的刷新---主要是调整位置
     * @param       编辑模式下，会更改miniRect的位置---miniRect跟随line的起点和终点变化而变化
     */
    void updateRect(QPointF p1,QPointF p2);

private slots:

    /**
     * @brief       控制miniRect的下标
     * @param       编辑模式下，确认鼠标所控制的miniRect的下标
     */
    void slotMiniRectIndex(int index);

public slots:
};

#endif // VISIONLINEITEM_H

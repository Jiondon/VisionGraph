/****************************************************************************
** @brief       自定义椭圆类
** @note        绘制后，可对该椭圆进行编辑（缩放，旋转等）
** @author      xiaodongLi
** @date        create:2018-09-28
** @example
****************************************************************************/


#ifndef VISIONELLIPSEITEM_H
#define VISIONELLIPSEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QFocusEvent>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTransform>
#include <QPainterPath>
#include "../control/visionitem.h"
#include "../control/minirect.h"
#include "../control/visionarrows_rotate.h"

/**
 * @brief       椭圆形自定义控件
 * @author      kuainq
 * @date        create:20180208
 * @note        暂时没有添加可编辑椭圆
 */
class VISIONGRAPHSHARED_EXPORT VisionEllipseItem : public VisionItem
{
    Q_OBJECT
public:
    VisionEllipseItem(bool rotation = false,VisionItem *parent = 0);
    /**
     * @brief       设置矩形
     */
    void setRect(qreal x,qreal y,qreal width,qreal height);
    void setRect(QRectF rf);

    /**
     * @brief       获得矩形框大小
     * @return      矩形
     */
    QRect getRect()
    {
        return QRect(m_x,m_y,m_width,m_height);
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
     * @brief       获得矩形的基础大小，不添加可选框的尺寸
     * @return      矩形框基础尺寸
     */
    QRectF getBaseRect()
    {
        return QRectF(m_x,m_y,m_width,m_height);
    }

    /**
     * @brief       获得椭圆的旋转角度
     * @return      角度 、、 角度可能需要进行转换才可直接使用
     */
    qreal getAngle()
    {
        return m_angle;
    }

    QPainterPath getPainterPath();   //暂时无用


    /**
     * @brief       判断点（x,y）是否在该item内
     * @param       bool
     */
    bool getPosInArea(qreal x, qreal y);

signals:


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

private:
    qreal m_x = 0,m_y = 0,m_width = 0,m_height = 0;//矩形
    qreal m_centerX = 0;qreal m_centerY = 0;

    QPointF m_pointF1 = QPoint(0,0);
    QPointF m_pointF2 = QPoint(0,0);
    QPointF m_pointF3 = QPoint(0,0);
    QPointF m_pointF4 = QPoint(0,0);

    QColor penColor;//画笔颜色 默认黑色
    qreal penWidth;//画笔宽度 默认1

    QPointF lastPoint;  //scenePos
    QPointF lastPointF; //pos

    DirecCursor  directCursor = normal_rect;

    qreal m_angle = 0;  //旋转的角度

    bool m_bCircle = false;
    bool m_bEdit = false;

    QTransform m_transform;

    QList<MiniRect* > m_lstRect;

    VisionArrows_Rotate* arrowsItem = NULL;  //箭头item  表示坐标方向的
    bool m_bRotation = false;  //旋转和非旋转
    int m_iIndex = -1;  //鼠标当前所处于的编辑框的下标 -1表示当前不处于编辑框中

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

private:
    void initItem(); //初始化编辑模式下的几个小矩形以及旋转的箭头控件
    void updateItem();  //出现拖动和缩放等操作的时候，更新item的位置
    void updatePointF();  //刷新矩形的四个顶点---
    void updateBoundingRect();

private slots:
    //点击编辑的小矩形的对应的小矩形的标志
    void slotIndex(int index);

    //进入旋转操作和离开旋转操作
    void slotArrowsItem();
    void slotArrowsItem_leave();

public slots:
};
#endif // VISIONELLIPSEITEM_H

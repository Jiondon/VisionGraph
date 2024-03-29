﻿/****************************************************************************
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
    explicit VisionLineItem(bool bEdit = true, QPointF p1 = QPointF(0,0), QPointF p2 = QPointF(0,0), qreal penWidth = 0,
                            bool color_enable = false,
                            QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160),
                            VisionItem *parent = 0);

    /**
     * @brief       设置线的起点和终点
     * @param       p1 p2 起点和终点
     */
    void setLine(QPointF p1,QPointF p2);

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

    /**
     * @brief       获取Line的P1
     * @param       QpointF
     */
    QPointF getP1(){
        return m_pointF1;
    }

    /**
     * @brief       获取Line的P2
     * @param       QpointF
     */
    QPointF getP2(){
        return m_pointF2;
    }

    /**
     * @brief       获取每个顶点
     * @param       point vec
     */
    QVector<QPointF> getPoints();

    VGSegment2D getData(){
        VGSegment2D segment2D;
        segment2D.optional = VG_ENABLE;
        VGPoint2D p1,p2;
        p1.x = m_pointF1.x();
        p1.y = m_pointF1.y();
        p2.x = m_pointF2.x();
        p2.y = m_pointF2.y();
        segment2D.point1 = p1;
        segment2D.point2 = p2;
        return segment2D;
    }

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void signalChanged(VisionItem* item);

private:
    qreal m_x=0;qreal m_y;qreal m_width=0;qreal m_height=0;
    QPointF m_pointF1 = QPointF(0,0);
    QPointF m_pointF2 = QPointF(0,0);
    qreal m_penWidth = 0;
    QColor m_penColor = QColor(0,0,0);

    int m_iIndex = -1;
    MiniRect* m_miniRect1 = nullptr;
    MiniRect* m_miniRect2 = nullptr;

    qreal m_angle = 0;  //角度
    QPointF m_lastPointF;

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

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

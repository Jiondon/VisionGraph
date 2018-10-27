﻿/****************************************************************************
** @brief       基于VisionItem类封装的point类
** @note        基于所在的点，绘制一个十字形状的表示所在的点
** @author      xiaodongLi
** @date        create:2018-09-28
****************************************************************************/



#ifndef VISIONCROSSPOINTITEM_H
#define VISIONCROSSPOINTITEM_H

#include <QObject>
#include <QStyleOptionGraphicsItem>
#include "../control/visionitem.h"

class VisionCrossPointItem : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionCrossPointItem(VisionItem *parent = 0);

    /**
     * @brief       构造的时候的参数为point
     */
    explicit VisionCrossPointItem(QPointF pointF,VisionItem *parent = 0);

    /**
     * @brief       构造的时候的参数为x，y
     */
    explicit VisionCrossPointItem(qreal x,qreal y,VisionItem *parent = 0);


    /**
     * @brief       设置点
     */
    void setPoint(qreal x,qreal y);

    /**
     * @brief       设置点
     */
    void setPoint(QPointF pointF);

    bool getPosInArea(qreal x, qreal y);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

private:
    QPointF m_pointF;

public slots:
};

#endif // VISIONCROSSPOINTITEM_H

/****************************************************************************
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

class VISIONGRAPHSHARED_EXPORT VisionCrossPointItem : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionCrossPointItem(bool edit = false,VisionItem *parent = 0);

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

    QPointF getPoint();

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

    bool m_bEdit = false;

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

public slots:
};

#endif // VISIONCROSSPOINTITEM_H

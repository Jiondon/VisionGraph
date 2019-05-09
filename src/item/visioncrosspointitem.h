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
    explicit VisionCrossPointItem(bool edit = false, qreal length = 5, bool color_enable = false,
                                  QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160),
                                  VisionItem *parent = 0);

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

    /**
     * @brief       获取每个顶点
     * @param       point vec
     */
    QVector<QPointF> getPoints();

    VGPoint2D getData(){
        VGPoint2D point2D;
        point2D.optional = VG_ENABLE;
        point2D.x = m_pointF.x();
        point2D.y = m_pointF.y();
        return point2D;
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
    QPointF m_pointF;

    qreal m_length = 5;
    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

public slots:
};

#endif // VISIONCROSSPOINTITEM_H

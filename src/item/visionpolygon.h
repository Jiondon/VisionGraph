/****************************************************************************
** @brief       自定义polygon
** @note        可编辑的多边形，
** @author      xiaodongLi
** @date        create:2018-09-28
** @example
****************************************************************************/


#ifndef VISIONPOLYGON_H
#define VISIONPOLYGON_H

#include <QObject>
#include <QPolygonF>
#include "../control/visionitem.h"

#include "../control/minirect.h"


class VISIONGRAPHSHARED_EXPORT VisionPolygon : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionPolygon(VisionItem *parent = 0);
    ~VisionPolygon();

    /**
     * @brief       多边形设置点集接口
     * @note        多边形的点集是随时变化的，在未绘制完成前，每次点击需要通过该接口更新数据
     * @param       pointFs 多边形点集， bFinished确定多边形是否绘制结束
     */
    void setPointFs(QVector<QPointF> pointFs,bool bFinished = false);

    /**
     * @brief       判断点（x,y）是否在该item内
     * @param       bool
     */
    bool getPosInArea(qreal x, qreal y);

    /**
     * @brief       获取多边形的每个顶点
     * @param       point vec
     */
    QVector<QPointF> getPointS(){
        return m_vecPointFs;
    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

signals:

private:

    qreal m_x = 0;
    qreal m_y = 0;
    QVector<QPointF> m_vecPointFs;
    QVector<QPointF> m_vecPointFs_temp;

    QList<MiniRect*> m_lstRect;
    int m_iIndex = -1;

    QPointF m_lastPointF;

    QPolygonF m_polygonF;
    QPolygonF m_polygonF_temp;


    bool m_bEdit = false;  //flag 选中未选中

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

private:
    void initMiniRect();
    void updateMiniRect();

private slots:
    void slotIndex(int index);

public slots:
};

#endif // VISIONPOLYGON_H

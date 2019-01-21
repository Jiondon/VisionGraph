#ifndef VISIONLINEITEMFITTING_H
#define VISIONLINEITEMFITTING_H

#include <QObject>
#include <QPainter>
#include "../control/visionitem.h"
#include "../control/minirect.h"

class VISIONGRAPHSHARED_EXPORT VisionLineItemFitting : public VisionItem
{
    Q_OBJECT
public:

    /**
     * @brief       构造函数
     * @param       对line的一些属性进行设置
     * @param       p1 p2 起点和终点 bEdit控制该line是否是可编辑的（起点终点可更改），penWidth penColor画笔的属性
     */
    explicit VisionLineItemFitting(bool bEdit = true,QPointF p1 = QPointF(0,0),QPointF p2 = QPointF(0,0),qreal length=0,
                                   qreal penWidth = 0,QColor penColor = QColor(0,0,0),VisionItem *parent = 0);

    /**
     * @brief       设置线的起点和终点
     * @param       p1 p2 起点和终点
     */
    void setLine(QPointF p1,QPointF p2);

    /**
     * @brief       设置线的fitting 长度
     * @param
     */
    void setLength(qreal length);


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

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void signalChanged(VisionItem* item);

private:
    qreal m_x=0;qreal m_y=0;qreal m_width=0;qreal m_height=0;
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

    qreal m_length = 0;  //线成面的长度
    bool m_bFitting = true;  //控件在初始的时候，处于可fitting状态
    QPolygonF m_polygonF;
private:

    /**
     * @brief       miniRect的刷新---主要是调整位置
     * @param       编辑模式下，会更改miniRect的位置---miniRect跟随line的起点和终点变化而变化
     */
    void updateRect(QPolygonF polygonF);

    void updatePolygon();

private slots:

    /**
     * @brief       控制miniRect的下标
     * @param       编辑模式下，确认鼠标所控制的miniRect的下标
     */
    void slotMiniRectIndex(int index);

public slots:
};


#endif // VISIONLINEITEMFITTING_H

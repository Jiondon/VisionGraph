#ifndef VISIONPOLYGONITEMFITTING_H
#define VISIONPOLYGONITEMFITTING_H

#include <QObject>
#include <QPolygonF>
#include "../control/visionitem.h"

#include "../control/minirect.h"


struct Line_Struct{
    QLineF line1;  //外部
    QLineF line2;  //内部
    QLineF line;
};

struct Point_Struct{
    QPointF p1;
    QPointF p2;
    QPointF p3;
    QPointF p4;
};

class VisionPolygonItemFitting : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionPolygonItemFitting(bool close = true,bool edit = true,qreal length = 0,QColor color = QColor(255,0,0),VisionItem *parent = 0);
    ~VisionPolygonItemFitting();

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
     * @brief       获取该类的close属性
     * @param       bool
     */
    bool isClosed()
    {
        return m_bClose;
    }

    /**
     * @brief       获取多边形的每个顶点
     * @param       point vec
     */
    QVector<QPointF> getPoints(){
        return m_vecPointFs;
    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void signalChanged(VisionItem* item);

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

    bool m_bClose = true; //多边形是否封闭变量控制

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

    bool m_bFitting = true;
    qreal m_length = 0;
    QPainterPath m_path;

    QList<QPolygonF> m_lstPoly;

    QPolygonF m_poly;
    QVector<QPointF> m_lstPointF;
    QVector<QPointF> m_lstPointF1;
    QList<Line_Struct> m_lstLineStruct;
    QList<QLineF> m_lstLine;

private:
    void initMiniRect();
    void updateMiniRect();

    //点的集合 两两形成直线，点p到每条直线的距离，并返回最小值    close表示点的集合是否首尾相连   close--true 首尾相连
    qreal getMinDistance(QVector<QPointF> vec_p,bool close,QPointF p);
    qreal getDistance(QPointF p1,QPointF p2,QPointF p);

    //获取两点之间线段的距离length的区域
    QPolygonF getPolygonLineFitting(QVector<QPointF> vec_p,bool close, qreal length);

    //获取顶点p1出的半圆，和p1p2直线
    QPolygonF getLineCircle(QPointF p1,QPointF p2,qreal length);


    //对lineStruct进行处理，保证lineStruct中line1和line相交的交点不在line上，line2与line相交的交点在line上
    //如果line1 line2和line平行，则不处理
    Line_Struct detailLine(Line_Struct lineStruct1, Line_Struct lineStruct2);

    //获取两点之间的圆弧
    QPolygonF drawArc(QPointF sP, QPointF fP, QPointF center, qreal r);

    //点集合，两两组合成线，两两线的交点返回  close，即点的集合是否首尾相连
    QVector<QPointF> getCrossP(QVector<QPointF> vec_p,bool close);

    //两条线的交点
    QPointF getLineCrossP(QPointF p1,QPointF p2,QPointF p3,QPointF p4);


    void updateData();

private slots:
    void slotIndex(int index);

public slots:
};
#endif // VISIONPOLYGONITEMFITTING_H

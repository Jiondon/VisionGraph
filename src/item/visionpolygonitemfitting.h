#ifndef VISIONPOLYGONITEMFITTING_H
#define VISIONPOLYGONITEMFITTING_H

#include <QObject>
#include <QPolygonF>
#include "../control/visionitem.h"

#include "../control/minirect.h"

class VisionPolygonItemFitting : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionPolygonItemFitting(bool close = true, bool edit = true, qreal length = 0, bool color_enable = false,
                                      QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160),
                                      VisionItem *parent = 0);
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

    VGPathFittingField getData(){
        VGPathFittingField vgPathFitting;

        VGPath vgPath;
        vector<VGPoint2D> vec_p;
        vec_p.clear();
        for(int i=0;i<m_vecPointFs.count();i++){
            VGPoint2D point2D;
            point2D.x = m_vecPointFs.at(i).x();
            point2D.y = m_vecPointFs.at(i).y();
            vec_p.push_back(point2D);
        }
        vgPath.arrayPoint2D = vec_p;
        vgPath.closed = m_bClose;

        vgPathFitting.axis = vgPath;
        vgPathFitting.width = m_length;
        return vgPathFitting;
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

//    QList<QPolygonF> m_lstPoly;
    QPolygonF m_polygonF_Fitting;

private:
    void initMiniRect();
    void updateMiniRect();

    //点的集合 两两形成直线，点p到每条直线的距离，并返回最小值    close表示点的集合是否首尾相连   close--true 首尾相连
    qreal getMinDistance(QVector<QPointF> vec_p,bool close,QPointF p);
    qreal getDistance(QPointF p1,QPointF p2,QPointF p);

    //获取两点之间线段的距离length的区域
    QPolygonF getPolygonLineFitting(QVector<QPointF> vec_p,bool close, qreal length);

    //获取p1p2直线的Fitting，length为Fitting的长度；
    QPolygonF getLineFitting(QPointF p1,QPointF p2,qreal length);

    //获取圆
    QPolygonF getCircle(QPointF p,qreal r);

    void updateData();

private slots:
    void slotIndex(int index);

public slots:
};

#endif // VISIONPOLYGONITEMFITTING_H

﻿/****************************************************************************
** @brief       自定义polygon
** @note        可编辑的多边形，或者折线（折线封闭的话，即为多边形），统称为多边形，折线为未封闭的多边形
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

///  后期优化采用模板进行设置数据参数
class VISIONGRAPHSHARED_EXPORT VisionPolygon : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionPolygon(bool close = true, bool edit = true, bool color_enable = false, QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160),
                           VisionItem *parent = 0);
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

    VGPath getData(){
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
        return vgPath;
    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

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

private:
    void initMiniRect();
    void updateMiniRect();

private slots:
    void slotIndex(int index);

public slots:
};

#endif // VISIONPOLYGON_H

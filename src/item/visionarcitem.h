/****************************************************************************
** @brief       基于VisionItem类封装的圆弧
** @note        三点形成一条圆弧，起点中点终点，（三点在编辑情况下可变化，变化后新的圆弧对三点进行重置）
** @author      xiaodongLi
** @date        create:2019-01-15
****************************************************************************/


#ifndef VISIONARCITEM_H
#define VISIONARCITEM_H

#include <QObject>
#include <QPainter>
#include "../control/color.h"
#include "../control/visionitem.h"
#include "../control/minirect.h"

class VisionArcItem : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionArcItem(bool bEdit = false, bool color_enable = false,
                           QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160), VisionItem *parent = 0);

    void setPointFs(QPointF sP = QPointF(0,0),QPointF mP = QPointF(0,0),QPointF fP = QPointF(0,0));
    void setArc(QPointF center,qreal r,qreal angle,qreal spanAngle);

    QVector<QPointF> getPoints();
    bool getPosInArea(qreal x, qreal y);

    VGArc2D getData(){
        VGArc2D vgArc;
        VGPoint2D centervgPoint;
        centervgPoint.x = m_center.x();
        centervgPoint.y = m_center.y();

        vgArc.center = centervgPoint;
        vgArc.radius = m_r;
        vgArc.startAngle = m_angle;
        vgArc.sweepAngle = m_spanAngle;
        return vgArc;
    }

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void signalChanged(VisionItem *item);

private:
    QPointF m_p1;
    QPointF m_p2;
    QPointF m_p3;

    qreal m_x;
    qreal m_y;
    qreal m_width;
    qreal m_height;

    QPointF m_center;
    double m_r;
    double m_angle;
    double m_spanAngle;


    MiniRect *m_sMiniRect = NULL;
    MiniRect *m_mMiniRect = NULL;
    MiniRect *m_fMiniRect = NULL;
    int m_iIndex = -1;

    QPointF m_lastPoint_Press;

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

private:

    void initMiniRect();
    //三点计算对应的圆心和直径，以及圆弧在圆中的角度范围
    bool detailData(QPointF sP,QPointF mP,QPointF fP);

public slots:
    void slotMiniRectIndex(int index);
};

#endif // VISIONARCITEM_H

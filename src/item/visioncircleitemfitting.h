#ifndef VISIONCIRCLEITEMFITTING_H
#define VISIONCIRCLEITEMFITTING_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QFocusEvent>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainterPath>
#include "../control/visionitem.h"
#include "../control/minirect.h"

class VisionCircleItemFitting : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionCircleItemFitting(bool edit = false, qreal length = 0, bool color_enable = false,
                                     QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160),
                                     VisionItem *parent = 0);

    /**
     * @brief       设置矩形
     */
    void setCircle(qreal x,qreal y,qreal width,qreal height);
    void setCircle(QPointF center,qreal r);
    void setCircle(QRectF rf);

    /**
     * @brief       获得矩形框大小
     * @return      矩形
     */
    QRect getRect()
    {
        return QRect(m_x,m_y,m_width,m_height);
    }


    /**
     * @brief       设置画笔(线条)颜色
     * @param       color
     */
    void setPenColor(QColor color)
    {
        penColor = color;
    }

    /**
     * @brief       设置画笔(线条)宽度
     * @param       width
     */
    void setPenWidth(qreal width)
    {
        penWidth = width;
    }

    /**
     * @brief       获得矩形的基础大小，不添加可选框的尺寸
     * @return      矩形框基础尺寸
     */
    QRectF getBaseRect()
    {
        return QRectF(m_x,m_y,m_width,m_height);
    }


    /**
     * @brief       判断点（x,y）是否在该item内
     * @param       bool
     */
    bool getPosInArea(qreal x, qreal y);


    /**
     * @brief       获取每个顶点（外切矩形）
     * @param       point vec
     */
    QVector<QPointF> getPoints();

    VGCircleFittingField getData(){
        VGCircleFittingField vgCircleFitting;

        VGCircle2D vgCircle2D;
        vgCircle2D.optional = VG_ENABLE;

        VGPoint2D vgPoint;
        vgPoint.optional = VG_ENABLE;
        vgPoint.x = m_x+m_width/2;
        vgPoint.y = m_y+m_width/2;
        vgCircle2D.center = vgPoint;   //

        vgCircle2D.radius = m_width/2;

        vgCircleFitting.axis = vgCircle2D;
        vgCircleFitting.width = m_length;

        return vgCircleFitting;
    }

signals:
    void signalChanged(VisionItem* item);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

private:
    qreal m_x = 0,m_y = 0,m_width = 0,m_height = 0;//正方形  //m_width m_height是等同的
    qreal m_centerX = 0;qreal m_centerY = 0;

    QColor penColor;//画笔颜色 默认黑色
    qreal penWidth;//画笔宽度 默认1

    QPointF lastPoint;  //scenePos
    QPointF lastPointF; //move pos

    DirecCursor  directCursor = normal_rect;


    QList<MiniRect* > m_lstRect;
    QList<QPointF> m_lstPointF;

    int m_iIndex = -1;  //鼠标当前所处于的编辑框的下标 -1表示当前不处于编辑框中

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

    bool m_bFitting = true;
    qreal m_length = 0;
    QPainterPath m_path;

private:
    void initItem(); //初始化编辑模式下的几个小矩形以及旋转的箭头控件
    void updateItem();  //出现拖动和缩放等操作的时候，更新item的位置

    QList<QPointF> rfToPoint(QRectF rf);
    QRectF pointsToRf(QList<QPointF> lstPointF);

    QRectF detailMove(int index,QPointF p);

private slots:
    //点击编辑的小矩形的对应的小矩形的标志
    void slotIndex(int index);

public slots:
};

#endif // VISIONCIRCLEITEMFITTING_H

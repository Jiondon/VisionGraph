/****************************************************************************
** @brief       自定义圆环
** @note        两个圆的结合
** @author      xiaodongLi
** @date        create:2018-09-28
** @example
****************************************************************************/

#ifndef VISIONRING_H
#define VISIONRING_H

#include <QObject>
#include <QGraphicsItem>
#include <QColor>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QPainterPath>
#include "../control/visionitem.h"
#include "../control/minirect.h"

//圆环控件  内圆和外圆
class VISIONGRAPHSHARED_EXPORT VisionRing : public VisionItem
{
    Q_OBJECT
public:
    //圆心，两个半径的方法处理
    explicit VisionRing(qreal centerX=0,qreal centerY=0,qreal r1=0,qreal r2=0,qreal penWidth=0,QColor penColor=QColor(255,0,0),VisionItem *parent = 0);
    //矩形框的内切圆
    VisionRing(QRectF rf1,QRectF rf2,qreal penWidth,QColor penColor=QColor(255,0,0),QGraphicsItem *parent = 0);
    void setDirection(int iDirection = 0);  //0--正向 -1反向
    QPainterPath getPainterPath();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
//    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:

private:

    qreal m_r1 = 0;
    qreal m_r2 = 0;

    qreal m_centerX = 0;  //相对于scene坐标系
    qreal m_centerY = 0;

    QRectF m_rf1;  //相对于scene坐标系
    QRectF m_rf2;

    qreal m_penWidth = 0;
    QColor m_penColor = QColor(255,0,0);

    qreal m_x = 0;  //相对于scene坐标系
    qreal m_y = 0;
    qreal m_width = 0;
    qreal m_height = 0;

    bool m_bSelected1 = false;  //rf1选中状态
    bool m_bSelected2 = false;  //rf2选中状态

    QPointF m_curPointF;
    QPointF m_lastPointF;

    QList<MiniRect*> m_lstRect;

    DirecCursor m_direcCursor = normal_rect;
    int m_iIndex = 1;   //标记是圆环1还是圆环2

    int m_iDirection = 0;  //方向 环2-->环1

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

private:
    void setItemPos();
    void initMiniRect();
    void updateMiniRect();

private slots:
    void slotIndex_MiniRect(int index);  //

public slots:
};

#endif // VISIONRING_H

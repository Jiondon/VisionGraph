#ifndef VISIONCHAINITEM_H
#define VISIONCHAINITEM_H

#include <QObject>
#include "../control/visionitem.h"
#include <QPainter>

class VISIONGRAPHSHARED_EXPORT VisionChainItem : public QObject , public VisionItem
{
    Q_OBJECT
public:
    explicit VisionChainItem(QObject *parent = 0);

    void setChainPos(QList<qreal> lst_x,QList<qreal> lst_y);//设置链的绘制的所有的点
    void setChainPos(QList<QPointF> lst_p);//设置链的绘制的所有的点

    bool addPointF(QPointF pointF);  //在范围内添加点,超过范围返回false
    bool removePointF(QPointF pointF);  //删除点,删除成功 true  失败（删除的点不存在） false

    QList<QPointF> getPointFs();  //获取在链上添加的点

    void setPointFColor(const QColor &color);

    QList<QPointF> getChainPoints();  //获取链的节点

signals:
    void signalMouse(qreal x,qreal y);
    void signalSelected(bool selected,int index);

protected:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    //鼠标悬停
//    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
//    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    QRectF addRect();  //根据起点和终点坐标绘制一个矩形将线条包住 的一个运算

private:
    QLineF m_lineF;

    qreal m_x1;
    qreal m_y1;
    qreal m_x2;
    qreal m_y2;

    QList<qreal> m_lst_x;
    QList<qreal> m_lst_y;


    bool m_selected = false;  //选中状态 false-未选中 true--选中
    int m_iIndex = 0; //线的索引,用来区分每根线

    QList<QPointF> m_lstPointF; //添加的点的集合
    QList<QPointF> m_lstChainPoint;  //链的节点

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

    QColor m_pointFColor;  //链上的点的颜色

};

#endif // VISIONCHAINITEM_H

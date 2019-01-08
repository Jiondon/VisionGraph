#ifndef VISIONCHAINITEM_H
#define VISIONCHAINITEM_H

#include <QObject>
#include "../control/visionitem.h"
#include "../control/minirect.h"
#include <QPainter>

class VISIONGRAPHSHARED_EXPORT VisionChainItem : public QObject , public VisionItem
{
    Q_OBJECT
public:
    explicit VisionChainItem(bool edit = true,bool bClosed = false,QObject *parent = 0);

    /**
     * @brief       设置链的绘制的所有的点
     */
    void setChainPos(QList<qreal> lst_x,QList<qreal> lst_y);
    void setChainPos(QList<QPointF> lst_p);

    /**
     * @brief       拆分链 -- 在链上某一处添加一点，todo
     * @param       实现有难度，暂时不做
     */
    void splitChain(QPointF splitPoint){}

    /**
     * @brief       合并 -- 将链上的两点之间的所有的点合并，todo
     * @param       实现有难度，暂时不做
     */
    void mergeChain(QPointF mergePoint1,QPointF mergePoint2){}

    /**
     * @brief       在范围内添加点,
     * @return      超过范围（添加失败），返回false；范围内（添加成功）返回true
     */
    bool addPointF(QPointF pointF);

    /**
     * @brief       删除添加的点
     * @return      删除成功 true  失败（删除的点不存在） false
     */
    bool removePointF(QPointF pointF);

    /**
     * @brief       设置添加的点的颜色
     */
    void setPointFColor(const QColor &color);

    /**
     * @brief       获取在链上添加的点
     */
    QList<QPointF> getChainPoints();

    /**
     * @brief       获取绘制链的所有的顶点
     */
    QVector<QPointF> getPoints();

signals:
    void signalMouse(qreal x,qreal y);
    void signalSelected(bool selected,int index);

    void signalChanged(VisionItem* item);

protected:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF addRect();  //根据起点和终点坐标绘制一个矩形将线条包住 的一个运算
    void updateMiniRect();

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

    bool m_bEdit = true;   //和基类的edit区别开，
    bool m_bClosed = false;     //是否是封闭

    QList<QPointF> m_lstPointF; //添加的点的集合
    QList<QPointF> m_lstChainPoint;  //链的节点
    QList<MiniRect*> m_lstMiniRect;

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

    QColor m_pointFColor;  //链上的点的颜色

};

#endif // VISIONCHAINITEM_H

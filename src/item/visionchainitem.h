/****************************************************************************
** @brief       基于VisionItem类封装的链类
** @note        多个点相连形成的n条线段
** @author      xiaodongLi
** @date        create:2019-01-06
****************************************************************************/


#ifndef VISIONCHAINITEM_H
#define VISIONCHAINITEM_H

#include <QObject>
#include "../control/visionitem.h"
#include "../control/minirect.h"
#include <QPainter>

class VISIONGRAPHSHARED_EXPORT VisionChainItem : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionChainItem(bool bClosed = false, bool edit = true, bool color_enable = false,
                             QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160)
            , VisionItem *parent = 0);

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

    /**
     * @brief       判断点（x,y）是否在该item内
     * @param       bool
     */
    bool getPosInArea(qreal x,qreal y);

    VGPath getData(){
        VGPath vgPath;

        vector<VGPoint2D> vec_p;
        vec_p.clear();
        for(int i=0;i<m_lstChainPoint.count();i++){
            VGPoint2D point2D;
            point2D.x = m_lstChainPoint.at(i).x();
            point2D.y = m_lstChainPoint.at(i).y();
            vec_p.push_back(point2D);
        }
        vgPath.arrayPoint2D = vec_p;
        vgPath.closed = m_bClosed;
        return vgPath;
    }

signals:
    void signalChanged(VisionItem* item);

protected:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    void updateData();  //数据刷新---当某些数据变化的时候，对应的rect，等其他属性刷新

    void updateMiniRect();
    qreal getMinDistance(QVector<QPointF> vec_p, bool close, QPointF p);
    qreal getDistance(QPointF p1, QPointF p2, QPointF p);

private:
    QLineF m_lineF;

    qreal m_x1;
    qreal m_y1;
    qreal m_x2;
    qreal m_y2;

    QList<qreal> m_lst_x;
    QList<qreal> m_lst_y;


    int m_iIndex = -1; //标记链被选中后的小矩形框的index （-1表示，鼠标不在矩形框中，其他数值表示鼠标在对应的index小矩形框上）

    bool m_bClosed = false;

    QList<QPointF> m_lstPointF; //添加的点的集合
    QList<QPointF> m_lstChainPoint;  //链的节点
    QList<MiniRect*> m_lstMiniRect;

    QPointF m_lastPointF;  //

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

    QColor m_pointFColor;  //链上的点的颜色
    ItemType m_type;

    QPolygonF *m_polygonF = nullptr;

private slots:
    /**
     * @brief       控制miniRect的下标
     * @param       编辑模式下，确认鼠标所控制的miniRect的下标
     */
    void slotMiniRectIndex(int index);
};

#endif // VISIONCHAINITEM_H

/****************************************************************************
** @brief       自定义View类
** @note        主要是针对view的重绘函数进行重载
** @author      xiaodongLi
** @date        create:2018-09-28
** @example
****************************************************************************/


#ifndef VISIONGRAPHVIEW_H
#define VISIONGRAPHVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QFocusEvent>
#include "../control/visionitem.h"

#include "XVBase.h"
#include "XVCreateRegion.h"
#include "XVCombineRegions.h"
#include <QDebug>

class VisionGraphView : public QGraphicsView
{
    Q_OBJECT
public:
    VisionGraphView(QWidget *parent =0);

    /**
     * @brief       当鼠标移动时候触发
     * @param       重写MouseMoveEvent事件，拖动和绘制
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief       当鼠标按下时候触发
     * @param       记录坐标
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief       当鼠标松开时候触发
     */
    void mouseReleaseEvent(QMouseEvent *event);

    /**
     * @param        缩放事件触发
     */
    void wheelEvent(QWheelEvent *event);

    /**
     * @param       view中的鼠标的样式控制
     */
    void enterEvent(QEvent *event);

    /**
     * @param       view的重绘函数的重载
     */
    void paintEvent(QPaintEvent* event);

    /**
     * @brief       修改绘制的item时候触发
     * @param       在使用鼠标移动进行绘制任意区域的时候，鼠标本身的大小作为绘制要素之一
     * @param       绘制不同的item，有不同的鼠标样式
     */
    void setPainterCursorR(qreal qR){
        setItemType(m_itemType);
        m_qCircleR = qR;
    }

    /**
     * @brief       设置记录当前所要绘制的item
     */
    void setItemType(ItemType type){
        m_bPainter = true;
        m_itemType = type;
        if(m_itemType == ItemType::Point || m_itemType == ItemType::NoPoint){
            //修改鼠标为绘图样式
            QCursor cursor = QCursor(QPixmap(":/icon/cursor-size_Circle.png").scaled(m_qCircleR*2*m_scale,m_qCircleR*2*m_scale));
            this->setCursor(cursor);
        }else{
            this->setCursor(Qt::ArrowCursor);
        }
    }


    /**
     * @brief       view的缩放比例
     */
    void zoom(float scaleFactor);


    /**
     * @brief       撤销区域生成
     */
    void back_region();


    /**
     * @brief       恢复区域生成
     */
    void front_region();


    /**
     * @brief       清除view的绘制数据
     */
    void clearPainter();

    /**
     * @brief       获取当前绘制在view的区域
     * @param       XVRegion
     */
    XVRegion getRegion(){
        return m_region;
    }

signals:
    void signal_Move(QPointF pointF);
    void signal_wheel(qreal delta);
    void signal_Item(ItemType type,QRectF rf);  //rect ellipse
    void signal_Item_poly(QVector<QPointF> vecPoint);  //
    void signal_Item_point(QPointF pointF);
    void signal_Item_Line(QLine line);

private:

    QVector<QLineF> m_lstLines;

    bool m_bPainter = true;   //绘制
    bool m_bPainter_Delect;  //删除绘制的区域
    bool m_bPress = false;  //记录鼠标的按下状态
    qreal m_qCircleR = 10;
    QPointF  m_lastPointF;  //记录上次的鼠标的点的位置


    QPointF m_pressPointF;   //在按下和松开的整体流程中，按下鼠标的坐标的点的位置
    QPointF m_pressPointF_scene;   //在按下和松开的整体流程中，按下鼠标的坐标的点的位置

    QPointF m_releasePointF;   //在按下和松开的整体流程中，松开鼠标的坐标的点的位置


    QList<QPointF> m_lstPoint;  //存放单次的连续的点的集合--一个区域

    QPainterPath  m_path_rect;  //矩形的path记录
    QPainterPath  m_path_ellipse;   //椭圆的path记录
    QPainterPath  m_path_polygon;   //多边形的path记录
    QPainterPath  m_path_region;   //任意区域的path记录
    QPainterPath  m_path;   //临时绘制的path -- 绘制过程中

    QVector<QPointF> m_vecPoint_Poly;  //记录多边形的操作的点
    QVector<QPointF> m_vecPoint_Region;  //记录任意区域的操作的点

    QLine m_Line;  //记录绘制的直线

    ItemType m_itemType = ItemType::Point;  //绘制的控件类型


    XVCreateRegionIn regionIn;
    QVector<QLineF> m_vecLines;
    XVRegion  m_region;  //记录绘制的区域  每一次新操作生成的区域，将和该区域进行并集或者差集运算

    QVector<XVRegion>  m_vecRegion;   //生成区域的记录
    int m_iIndex_Region = 0;   //撤销多少步的记录


    bool m_clearAll = false; //清除view中的所有绘制数据

    float m_scale = 1;

protected:

public slots:

    /**
     * @brief      临时绘制，绘制过程中的显示
     */
    void slot_updateItem(ItemType type,QPainterPath path);

    /**
     * @brief       接收临时绘制完成，将该次绘制的区域，通过算法进行转换转换
     */
    void slot_updatePath(bool selected, VisionItem *item, ItemType type, QRectF rf, QPointF leftTop, qreal angle);


    /**
     * @brief       接收临时绘制完成，将该次绘制的区域，通过算法进行转换转换
     */
    void slot_CreatePolygonF(bool selected, VisionItem *item, ItemType type, QVector<QPointF> vecPointF);



    /**
     * @brief       接收临时绘制完成，将该次绘制的区域，通过算法进行转换转换
     */
    XVRegion slot_CombineRegion(XVRegion region1,XVRegion region2,XVCombineRegionsType combineType);


    /**
     * @brief       多个VisionItem进行某一类逻辑运算
     */
//    XVRegion slot_CombineRegion(XVRegion region1,XVRegion region2,XVCombineRegionsType combineType);

private:
    /**
     * @brief       将算法提供的区域进行解析，处理成Qt可使用的数据
     * @return      Qt可绘制的链表线段
     */
    QVector<QLineF> analysis_region(XVRegion region);


    /**
     * @brief       算法转换绘制多边形
     * @return      多边形的区域
     */
    XVRegion createPolygon(QPolygonF polygonF);

//    /**
//     * @brief       算法绘制圆
//     * @return      圆的区域
//     */
//    XVRegion createCircle(QRectF rf);

    /**
     * @brief       算法绘制椭圆或者圆
     * @param       angle 旋转角度
     */
    XVRegion createEllipse(QRectF rf, QPointF leftTop, qreal angle);

    /**
     * @brief       算法绘制矩形
     */
    XVRegion createRectangle(QRectF rf,QPointF leftTop,qreal angle);

    /**
     * @brief       将生成的区域记录到vector中
     * @param       要考虑到在恢复到某一记录时，将该记录的后面的记录都清空
     * @param       region新插入的记录，index，恢复的记录在vector中的位置(倒序)，目前该参数是使用全局变量 m_iIndex_Region替换
     */
    void push_region(XVRegion region,int index = 0);
};

#endif // VISIONGRAPHVIEW_H

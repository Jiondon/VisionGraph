﻿/****************************************************************************
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
#include "./control/visionitem.h"

#include "XVBase.h"

#include <QDebug>
#include <QLabel>

#include "visiongraph_global.h"
#include "./control/color.h"

#include <QLibrary>

//using namespace XVCreateR;
enum Corner{
    topLeft,
    topRight,
    bottomRight,
    bottomLeft,
};

enum ViewModel{
    SelectModel,
    DragModel,
    PaintModel
};


struct XVRegionPair {
    XVRegion region;
    int value;
    QColor color;
};

enum XVCombineRegionsType{
    Union,
    Difference
};

class VISIONGRAPHSHARED_EXPORT VisionGraphView : public QGraphicsView
{
    Q_OBJECT
public:
    VisionGraphView(QWidget *parent =0);

    void setGraphType(GraphType type);

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
     * @param       鼠标进入view的事件触发
     */
    void enterEvent(QEvent *event);

    /**
     * @param       鼠标离开view的事件触发
     */
    void leaveEvent(QEvent *event);

    /**
     * @param       view的重绘函数的重载
     */
    void paintEvent(QPaintEvent* event);

//    virtual bool eventFilter(QObject *obj, QEvent *event);
public:

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
    void setItemType(ItemType type);


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
    XVRegion* getRegion(){
        if(!m_region.optional){
            return NULL;
        }
        return &m_region;
    }

    /**
     * @brief       设置View信息框的显示或者隐藏
     */
    void setViewInfo_Visible(bool bVisible);

    /**
     * @brief       设置View信息框的位置（四个拐角）
     */
    void setViewInfo_Pos(Corner corner);

    /**
     * @brief       设置View信息框的位置（任意位置）
     */
    void setViewInfo_Pos(qreal x,qreal y);

    /**
     * @brief       设置View信息框的大小
     */
    void setViewInfo_Size(QSize size);
    void setViewInfo_Size(qreal w,qreal h);


    /**
     * @brief       设置View信息框的文本
     */
    void setViewInfo_text(QString text);

    /**
     * @brief       设置View信息框的颜色（背景颜色和文本颜色）
     */
    void setViewInfo_Color(QColor backgroundColor,QColor textColor);

    /**
     * @brief       设置View的算法区域的大小
     */
    void setViewRegion_Size(qreal w,qreal h);

    /**
     * @brief       设置View的算法区域的Visible
     */
    void setViewRegion_Visible(bool bVisible);

    /**
     * @brief       设置View的算法区域的color
     */
    void setViewRegion_Color(const QColor &color);

    /**
     * @brief       恢复View的算法区域的初始位置--居中
     */
    void viewRegion_OriginPos();

    /**
     * @brief       在item中鼠标样式变化后，回到view后的鼠标样式恢复
     */
    void itemCursorToViewCursor();

    /**
     * @brief       region的初始化---region的初始赋值
     */
    void initRegion(XVRegion region);


    /**
     * @brief       多region的添加
     */
    void addRegion(XVRegionPair regionPair);

    /**
     * @brief       多region的删除
     */
    void removeRegion(XVRegionPair regionPair);

    /**
     * @brief       设置多region
     */
    void setRegions(QList<XVRegionPair> lstRegionPair);

    /**
     * @brief       获取多region
     */
    QList<XVRegionPair> getRegions()
    {
        return m_lstRegion;
    }

    /**
     * @brief       清空region
     */
    void clearRegion();

    void resize(const QSize &size);
    void resize(int w, int h);

    /**
     * @brief       自适应大小并居中，返回缩放的比例（放大或者缩小，1-正常大小）
     */
    qreal adjustSize(qreal w,qreal h);

    /**
     * @brief       获取某一点的像素值
     * @param
     */
    QColor getPixel(qreal x,qreal y);

    /**
     * @brief       控制view的坐标系的显示和隐藏
     * @param
     */
    void setCoordinateVisible(bool bVisible);

    /**
     * @brief       添加不可编辑的region，此region可以通过清空进行删除
     * @param
     */
    void updateRegion_UnEdit(XVRegion region);

    void setRegionColor(QColor borderColor = QColor(255,0,0),
                        QColor selectColor = QColor(255,0,0),
                        QColor brushColor = QColor(255,0,0,160),
                        QColor brushColor_unEdit = QColor(255,0,0,200));

signals:
    void signal_Move(QPointF pointF);
    void signal_wheel(qreal scale);  //通知外部缩放比例，外部进行数据更新
    void signal_wheelEevent(QWheelEvent *event);

    void signal_Item(ItemType type,QRectF rf);  //rect ellipse
    void signal_Item_poly(QVector<QPointF> vecPoint,ItemType type=ItemType::Paint_Poly);  //
    void signal_Item_point(QPointF pointF);
    void signal_Item_Line(QLine line);

    void signal_RegionItem();   //通知外部，区域发生变化，进行处理

private:

    GraphType m_graphType = GraphType::graphItem_unSelf;

    QVector<QLineF> m_lstLines;

    bool m_bPainter = true;   //绘制状态
    bool m_bPainter_Delect;  //删除绘制的区域
    bool m_bPress = false;  //表示当前开始收集鼠标事件--进行绘制
    qreal m_qCircleR = 10;
    QPointF  m_lastPointF;  //记录上次的鼠标的点的位置


    QPointF m_pressPointF;   //在按下和松开的整体流程中，按下鼠标的坐标的点的位置
    QPointF m_pressPointF_scene;   //在按下和松开的整体流程中，按下鼠标的坐标的点的位置

    QPointF m_releasePointF;   //在按下和松开的整体流程中，松开鼠标的坐标的点的位置

    QPointF m_movePointF;   //move事件的鼠标位置 view中的位置

    QList<QPointF> m_lstPoint;  //存放单次的连续的点的集合--一个区域

    QPainterPath  m_path_rect;  //矩形的path记录
    QPainterPath  m_path_ellipse;   //椭圆的path记录
    QPainterPath  m_path_polygon;   //多边形的path记录
    QPainterPath  m_path_region;   //任意区域的path记录
    QPainterPath  m_path;   //临时绘制的path -- 绘制过程中

    QVector<QPointF> m_vecPoint_Poly;  //记录多边形的操作的点
    QVector<QPointF> m_vecPoint_Region;  //记录任意区域的操作的点

    QLine m_Line;  //记录绘制的直线

    ItemType m_itemType = ItemType::Paint_Point;  //绘制的控件类型


//    XVCreateRegionIn regionIn;
//    XVCreateRegionOfInterestRegionIn  createRegionOfInterestRegionIn;
//    XVCreateBoxRegionIn               createBoxRegionIn             ;
//    XVCreateBoxBorderRegionIn         createBoxBorderRegionIn       ;
//    XVCreateEllipseRegionIn           createEllipseRegionIn         ;
//    XVCreateRingRegionIn              createRingRegionIn            ;
//    XVCreateCrossRegionIn             createCrossRegionIn           ;
//    XVCreateGridRegionIn              createGridRegionIn            ;
//    XVCreateCircleRegionIn            createCircleRegionIn          ;
//    XVCreatePolygonRegionIn           createPolygonRegionIn         ;
//    XVCreatePathBorderRegionIn        createPathBorderRegionIn      ;
//    XVCreateRectangleRegionIn         createRectangleRegionIn       ;
//    XVCreateRectangleBorderRegionIn   createRectangleBorderRegionIn ;
//    XVCreateSegmentRegionIn           createSegmentRegionIn         ;
//    XVCreateLineRegionIn              createLineRegionIn            ;


    QVector<QLineF> m_vecLines;
    XVRegion  m_region;  //记录绘制的区域  每一次新操作生成的区域，将和该区域进行并集或者差集运算
    QList<XVRegionPair> m_lstRegion;  //记录区域链表（多个区域）

    QVector<XVRegion>  m_vecRegion;   //生成区域的记录
    int m_iIndex_Region = 0;   //撤销多少步的记录


    bool m_clearAll = false; //清除view中的所有绘制数据

    float m_scale = 1;
    bool m_bZoom = false;  //false -- out缩小  true -- in放大

    QLabel *m_pMouseInfo_Label = NULL;  //跟随鼠标显示的信息

    QLabel *m_pLabelInfo = NULL;  //view的信息框

    Corner m_Corner = Corner::topLeft;

    QRectF m_frameRect = QRectF(0,0,800,600); //虚拟画布的设置--控制区域的范围
    bool m_bFrameVisible = true;  //算法区域是否显示出来
    QColor m_FrameColor = Qt::lightGray;   //算法区域的颜色

    bool m_bPress_Drag = false;  //提供给拖动进行控制，只有在按下的状态，拖动才有效

//    XVRegion m_Region_UnEdit;  //保存非编辑区域
    QList<QLineF> m_vecLines_unEdit;  //保存非编辑区域的直线

    bool isCoordinate = true;

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;
    QColor m_brushColor_unEdit;

    QLibrary m_lib_XVRegionAnalysis;


protected:

public slots:

    /**
     * @brief      临时绘制，绘制过程中的显示
     */
    void slot_updateItem(ItemType type,QPainterPath path);

    /**
     * @brief       接收临时绘制完成，将该次绘制的区域，通过算法进行转换转换
     */
    XVRegion slot_updatePath(bool selected, VisionItem *item, ItemType type, QRectF rf, QPointF leftTop, qreal angle);


    /**
     * @brief       接收临时绘制完成，将该次绘制的区域，通过算法进行转换转换
     */
    XVRegion slot_CreatePolygonF(bool selected, VisionItem *item, ItemType type, QVector<QPointF> vecPointF);



    /**
     * @brief       接收临时绘制完成，将该次绘制的区域，通过算法进行转换转换
     */
    XVRegion slot_CombineRegion(XVRegion region1,XVRegion region2,XVCombineRegionsType combineType);


    /**
     * @brief       多个VisionItem进行某一类逻辑运算
     */
//    XVRegion slot_CombineRegion(XVRegion region1,XVRegion region2,XVCombineRegionsType combineType);

    void slotUpdateViewInfo_Pos();

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
     * @brief       算法绘制直线
     */
    XVRegion createLine(QLine line);


    /**
     * @brief       将生成的区域记录到vector中
     * @param       要考虑到在恢复到某一记录时，将该记录的后面的记录都清空
     * @param       region新插入的记录，index，恢复的记录在vector中的位置(倒序)，目前该参数是使用全局变量 m_iIndex_Region替换
     */
    void push_region(XVRegion region,int index = 0);

    void detailMoveEvent(QMouseEvent *event);
    void detailPressEvent(QMouseEvent *event);

    QList<qreal> getArc(QPointF sP, QPointF mP, QPointF fP);

    QRectF detail_ellipse_InRectToOutRect(QRectF rf);

private slots:
    void slot_wheelEvent(QWheelEvent* event);

};

#endif // VISIONGRAPHVIEW_H

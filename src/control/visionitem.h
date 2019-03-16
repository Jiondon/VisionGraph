/****************************************************************************
** @brief       自定控件的基类
** @note
** @author      xiaodongLi
** @date        create:2018-09-28
** @example
****************************************************************************/

#ifndef VISIONITEM_H
#define VISIONITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include "VGBase.h"
#include "../visiongraph_global.h"

/**
 * @brief       枚举类型，item类型或者鼠标控制的类型（鼠标事件执行的对应的类型）-- 主要是绘图的view的状态的标记，包含了鼠标事件和绘制的item的记录等
 * @param       鼠标触发事件的所要执行的操作
 */
enum ItemType{
    No,   //选择状态
    Drag,  //拖动
    Zoom, //缩放状态

    Paint_LineFitting,


    Paint_Rect,  //矩形
    Paint_EllipseItem,  //圆或者椭圆
    Paint_CirCle,   //圆
    Paint_Arc,  //圆弧
    Paint_Poly,  //多边形
    Paint_Region,  //区域 -- 鼠标绘制，自动连接起始和结尾的区域，任意区域
    Paint_Line,  //线
    Paint_polyLine,  //折线
    Paint_Arrow,  //箭头（）
    Paint_Chain,   //链--（线和圆弧混用）
    Paint_CrossPoint,  //单独一个真正意义上的点
    Paint_Point,  //点
    Paint_NoPoint  //擦除item

};

/**
 * @brief       枚举类型  鼠标的样式方向--对应想要的鼠标事件
 */
enum DirecCursor
{
    normal_rect,
    left_rect,
    top_rect,
    right_rect,
    bottom_rect,  //标记点

    left_Top_rect,
    left_bottom_rect,
    right_top_rect,
    right_bottom_rect,

    arrowsUp
};

class VISIONGRAPHSHARED_EXPORT VisionItem : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    VisionItem(QGraphicsItem *parent = 0);

    /**
     * @brief       设置图形的类型
     * @param       QString
     */
     void setType(ItemType type){
         m_type = type;
     }

     /**
      * @brief       获取图形的类型
      * @param       QString
      */
    ItemType getType(){
        return m_type;
    }

    /**
     * @brief       设置item的状态
     * @param       bool
     */
    void setSelectedStatus(bool bSelected){
        setSelected(bSelected);
        m_bSelected = bSelected;
    }


    /**
     * @brief       获取item的选中状态
     * @param       bool
     */
    bool getSelectedStatus(){
        return m_bSelected;
    }

    /**
     * @brief       设置item的编辑状态
     * @param       bool
     */
    void setEdit(bool edit){
        m_bEdit = edit;
    }

    /**
     * @brief       获取item的编辑状态
     * @param       bool
     */
    bool getEdit(){
        return m_bEdit;
    }

    /**
     * @brief       设置item的Enable使能
     * @param       bool
     */
    void setItemEnable(bool enable){
        this->setEnabled(enable);
    }

    /**
     * @brief       获取item的Enable使能
     * @param       bool
     */
    bool getItemEnable(){
        return this->isEnabled();
    }

public:
    //虚函数
    /**
     * @brief       判断点（x,y）是否在该item内
     * @param       bool
     */
    virtual bool getPosInArea(qreal x,qreal y) = 0;

    /**
     * @brief       获取item的顶点--（圆（椭圆）的顶点为外切矩形）
     * @param       QVector<QPointF>
     */
    virtual QVector<QPointF> getPoints() = 0;


//    /**
//     * @brief       获取数据
//     * @param       XVGlobal
//     */
//    virtual XVGlobal getData() = 0;

signals:
    void signal_clicked(VisionItem* item,bool selected,bool bIn = true,qreal x=0,qreal y=0);
    void signal_ctrl(int eventStyle);  //事件类型
    void signal_press();   //用于提示item被点击

    /**
     * @brief       item绘制完成后触发
     * @param       将item的PainterPath传出去提供给其他的进行处理
     */
    void signal_painterInfo(ItemType type,QPainterPath rf);
//    void signal_painterInfo(ItemType type,QRectF rf,qreal angle);

    /**
     * @brief       当item的selected发生变化的事触发
     * @param       bool
     */
    void selectedChanged(bool selected,VisionItem* item,ItemType type, QRectF rf,QPointF left, qreal angle);

    void selectedChanged(bool selected,VisionItem* item,ItemType type, QVector<QPointF> vecPointF);

    /**
     * @brief       当item的boundingRect()发生变化的事触发,主要用于提供数据更新
     * @param
     */
    virtual void signalChanged(VisionItem* item) = 0;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    ItemType m_type;
    bool m_bEdit = false;
    bool m_bSelected = false;

};

#endif // VISIONITEM_H

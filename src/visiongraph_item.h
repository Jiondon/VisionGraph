/****************************************************************************
** @brief       VisionGraph,绘制模块的widget
** @note        会生成一个widget来进行展示绘制模块  item版本
** @author      xiaodongLi
** @date        create:2018-10-24
** @example
****************************************************************************/


#ifndef VISIONGRAPH_ITEM_H
#define VISIONGRAPH_ITEM_H

#include <QFrame>
#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "visiongraphtool.h"

#include <QLabel>
#include <QComboBox>
#include <QLayout>
#include <QAction>
#include <QToolBar>
#include <QSpinBox>
#include <QLineEdit>
#include "visiongraphwidget.h"

enum ItemModel{
    self,
    un_self
};

class VISIONGRAPHSHARED_EXPORT VisionGraph_Item : public QFrame
{
    Q_OBJECT
public:
    explicit VisionGraph_Item(ItemModel model = self,ToolButtonDirection toolButtonDirect = ToolButtonDirection::topDirection
            ,QWidget *parent = 0);
public:

    /**
     * @brief       添加rectangle  可旋转的矩形
     * @param       bEdit 表示编辑
     */
    void setSceneWidgetSize(QSize size);
    void setSceneWidgetSize(qreal w,qreal h);

    /**
     * @brief       添加rectangle  可旋转的矩形
     * @param       bEdit 表示编辑
     */
    void addRect(QRectF rf,bool bEdit = true);

    /**
     * @brief       添加椭圆
     * @param       默认是可编辑的，未添加不可编辑的椭圆
     */
    void addEllipse(QRectF rf);

    /**
     * @brief       添加线
     * @param       具体方法未实现
     */
    void addLine(QLine line);


    /**
     * @brief       添加线
     * @param       具体方法未实现
     */
    void addLines(QList<QLine> lstLine);


    /**
     * @brief       添加多边形
     * @param       点的集合，点的集合一次连接
     */
    void addPolygon(QVector<QPointF> vecPointF);

    /**
     * @brief       添加一个点
     * @param       具体方法未实现
     */
    void addPoint(QPointF pointF);


    /**
     * @brief       设置view的背景图片
     * @param
     */
    int setBkImg(QImage image);


    /**
     * @brief       设置toolButton的布局
     * @param
     */
    void setToolButton_Direction(ToolButtonDirection direct){
        m_toolButtonDirection = direct;
    }

    /**
     * @brief       获取view
     * @param
     */
    VisionGraphView* getView(){
        if(view == nullptr)
            return NULL;
        return view;
    }

    /**
     * @brief       修改绘制的item时候触发
     * @param       在使用鼠标移动进行绘制任意区域的时候，鼠标本身的大小作为绘制要素之一
     * @param       绘制不同的item，有不同的鼠标样式
     */
    void setPainterCursorR(qreal qR){
        view->setPainterCursorR(qR);
    }

    /**
     * @brief       设置记录当前所要绘制的item
     */
    void setItemType(ItemType type){
        view->setItemType(type);
    }


    /**
     * @brief       view的缩放比例
     */
    void zoom(float scaleFactor){
        view->zoom(scaleFactor);
    }


    /**
     * @brief       撤销区域生成
     */
    void back_region(){
        view->back_region();
    }


    /**
     * @brief       恢复区域生成
     */
    void front_region(){
        view->front_region();
    }


    /**
     * @brief       清除view的绘制数据
     */
    void clearPainter(){
        view->clearPainter();
    }

    /**
     * @brief       获取当前绘制在view的区域
     * @param       XVRegion
     */
    XVRegion* getRegion(){
        return view->getRegion();
    }

    /**
     * @brief       设置View信息框的位置（四个拐角）
     */
    void setViewInfo_Pos(Corner corner){
        view->setViewInfo_Pos(corner);
    }

    /**
     * @brief       设置View信息框的位置（任意位置）
     */
    void setViewInfo_Pos(qreal x,qreal y){
        view->setViewInfo_Pos(x,y);
    }

    /**
     * @brief       设置View信息框的大小
     */
    void setViewInfo_Size(QSize size){
        view->setViewInfo_Size(size);
    }

    void setViewInfo_Size(qreal w,qreal h){
        view->setViewInfo_Size(w,h);
    }


    /**
     * @brief       设置View信息框的文本
     */
    void setViewInfo_text(QString text){
        view->setViewInfo_text(text);
    }

    /**
     * @brief       设置View信息框的颜色（背景颜色和文本颜色）
     */
    void setViewInfo_Color(QColor backgroundColor,QColor textColor){
        view->setViewInfo_Color(backgroundColor,textColor);
    }

private:
    void initScene();
    void initTool_painter();  //竖直的工具栏
    void initTool_operation();  //水平的工具栏

    void initLayout(ToolButtonDirection toolButtonDirect);

    QPainterPath and_Item(QPainterPath path1,QPainterPath path2);  //交集  &&
    QPainterPath sub_Item(QPainterPath path1,QPainterPath path2);  //差集  ！
    QPainterPath or_Item(QPainterPath path1,QPainterPath path2);  //并集 ||
    QPainterPath nor_Item(QPainterPath path1,QPainterPath path2); //异或


private:
    VisionGraphScene *scene = nullptr;
    VisionGraphView *view = nullptr;

    QList<VisionItem*> m_lstItem;
    QList<VisionItem*> m_lstItemSelected;


    QPainterPath m_path;


    QList<QPointF> m_lstPainterPointF;  //绘制算法提供的直线的点的集合（两两配对）

    XVCreateRegionIn regionIn;


    QGraphicsPixmapItem *m_bkPixmapItem = nullptr;  //背景图片
    QGraphicsPixmapItem *m_mousePixmap = nullptr;  //调整鼠标的大小的时候，显示在区域中心的图片

    qreal m_zoom = 1;   //图形View的缩放比例

    QToolBar *tool_painter = NULL;
    QToolBar *tool_operation = NULL;
    ToolButtonDirection  m_toolButtonDirection = ToolButtonDirection::topDirection;  //tool按钮的位置
    QToolBar *tool_Widget = NULL;



private:

    //左侧工具栏 -- 绘制类（操作类）
    QAction *sys_selected_action;
    QAction *sys_drag_action;
    QAction *sys_zoom_action;

    QAction *sys_mousePainter_action;
    QAction *sys_mouseClear_action;

    QAction *sys_save_action;

    QAction *sys_rect_action;
    QAction *sys_ellipse_action;
    QAction *sys_poly_action;
    QAction *sys_poly_elli_action;
    QAction *sys_point_action;
    QAction *sys_line_action;
    QAction *sys_polyLine_action;



    //右侧工具栏 -- 功能类
    QAction *sys_open_project;  //打开工程
    QAction *sys_front_action;  //撤销
    QAction *sys_next_action;   //取消撤销
    QAction *sys_clear_action;  //清空绘图区域
    QAction *sys_remove_item;  //删除当前选中的item


    //显示的信息 -- 鼠标的移动坐标信息和操作信息
    QLabel *label_Operation;

    //记录item的类型  ====  同时也作为鼠标的状态标志 --- 鼠标事件发生的时候执行什么操作（绘制，清空，缩放，拖动等）
    ItemType m_itemType = ItemType::No;
    VisionItem* m_curVisionItem = nullptr;

    //缩放的比例显示
    QComboBox *comboBox;


    QVBoxLayout *mainLayout;   //主布局

    VisionGraphWidget *sceneWidget;

    ItemModel m_model = ItemModel::un_self;   //item的模式，用户交互绘制item？

private slots:
    //对应Action的槽函数
    void slot_selected_action();
    void slot_drag_action();
    void slot_zoom_action();

    void slot_mousePainter_action();
    void slot_mouseClear_action();

    void slot_save_action();

    void slot_rect_action();
    void slot_ellipse_action();
    void slot_poly_action();
    void slot_poly_elli_action();
    void slot_point_action();
    void slot_line_action();
    void slot_polyLine_action();

    void slot_open_project();
    void slot_front_action();
    void slot_next_action();
    void slot_clear_action();
    void slot_removeItem_action();

    void slot_addItem(ItemType type, QRectF rf);
    void slot_addPoly(QVector<QPointF> vecPointF);
    void slot_addPoint(QPointF pointF);
    void slot_addLine(QLine line);


    //接收view传过来的MouseMoveEvent事件
    void slot_mouseMove(QPointF pointF);

private slots:
    void slot_Press(VisionItem *item, bool bSelected, bool bIn, qreal x, qreal y);

    void slot_wheel(qreal delta);
    //调节view的缩放比例
    void slot_SizeChanged(QString currentSize);
    void slot_SizeChanged(qreal w,qreal h);
};


#endif // VISIONGRAPH_ITEM_H

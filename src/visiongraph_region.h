/****************************************************************************
** @brief       VisionGraph,绘制模块的widget
** @note        会生成一个widget来进行展示绘制模块  region版本
** @author      xiaodongLi
** @date        create:2018-10-24
** @example
****************************************************************************/


#ifndef VISIONGRAPH_REGION_H
#define VISIONGRAPH_REGION_H

#include <QFrame>
#include <QWidget>

#include <QAction>
#include <QToolBar>
#include <QLayout>
#include <QLabel>
#include <QComboBox>
#include <QIntValidator>
#include <QToolButton>
#include <QSpinBox>

#include "visiongraphtool.h"

class VisionGraph_Region : public QFrame
{
    Q_OBJECT
public:
    explicit VISIONGRAPHSHARED_EXPORT VisionGraph_Region(ToolButtonDirection toolButtonDirect = ToolButtonDirection::topDirection,
                                                         QWidget *parent = 0);

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
    VisionRectItem* addRect(QRectF rf,bool bEdit = true);

    QGraphicsRectItem* _addRect(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    QGraphicsPolygonItem* _addPolygon(const QPolygonF &polygon, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    QGraphicsLineItem* _addLine(const QLineF &line, const QPen &pen = QPen());
    QGraphicsEllipseItem* _addEllipse(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());


    /**
     * @brief       添加椭圆
     * @param       默认是可编辑的，未添加不可编辑的椭圆
     */
    VisionEllipseItem* addEllipse(QRectF rf);

    /**
     * @brief       添加线
     * @param       具体方法未实现
     */
    VisionLineItem* addLine(QLine line);

    /**
     * @brief       添加线
     * @param       具体方法未实现
     */
    void addLines(QList<QLine> lstLine);

    /**
     * @brief       添加多边形
     * @param       点的集合，点的集合一次连接
     */
    VisionPolygon* addPolygon(QVector<QPointF> vecPointF);

    /**
     * @brief       添加一个点
     * @param       具体方法未实现
     */
    VisionCrossPointItem* addPoint(QPointF pointF);


    /**
     * @brief       设置view的背景图片
     * @param
     */
    int setBkImg(QImage image);


    /**
     * @brief       获取当前绘制在view的区域
     * @return       XVRegion
     */
    XVRegion* getRegion(){
        return view->getRegion();
    }


    /**
     * @brief       设置toolButton的布局
     * @param
     */
    void setToolButton_Direction(ToolButtonDirection direct);

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
     * @brief       设置View信息框的显示或者隐藏
     */
    void setViewInfo_Visible(bool bVisible);

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

    /**
     * @brief       获取ToolButton
     */
    QToolButton* getToolButton(ToolButtonType type);


    /**
     * @brief       删除ToolButton
     */
    bool removeToolButton(ToolButtonType type);

    /**
     * @brief       添加ToolButton
     */
    void addToolButton(QToolButton* btn);

    /**
     * @brief       不显示toolbar的view的信息
     */
    void removeToolBarInfoWidget();

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

protected:

private:
    void initScene();
    void initTool_operation();  //水平的工具栏
    void initLayout(ToolButtonDirection toolButtonDirect = ToolButtonDirection::topDirection);


private:
    VisionGraphScene *scene = nullptr;
    VisionGraphView *view = nullptr;

    QGraphicsPixmapItem *m_bkPixmapItem = nullptr;  //背景图片
    QGraphicsPixmapItem *m_mousePixmap = nullptr;  //调整鼠标的大小的时候，显示在区域中心的图片

    qreal m_zoom = 1;   //图形View的缩放比例


    ToolButtonDirection  m_toolButtonDirection = ToolButtonDirection::topDirection;  //工具按钮的位置
    QToolBar *tool_Widget = NULL;


private:

    //左侧工具栏 -- 绘制类（操作类）
    QToolButton *sys_selected_button;
    QToolButton *sys_drag_button;
    QToolButton *sys_zoom_button;

    QToolButton *sys_mousePainter_button;
    QToolButton *sys_mouseClear_button;

    QToolButton *sys_rect_button;
    QToolButton *sys_ellipse_button;
    QToolButton *sys_poly_button;
    QToolButton *sys_poly_elli_button;


    //右侧工具栏 -- 功能类
    QToolButton *sys_open_button;
    QToolButton *sys_save_button;
    QToolButton *sys_front_button;  //撤销
    QToolButton *sys_next_button;   //取消撤销
    QToolButton *sys_clear_button;  //清空绘图区域

    QList<QToolButton*> m_lstToolBtn;
    QList<QAction*> m_lstAction;  //删除ToolButton使用的 ，必须要保证和m_lstToolBtn一致；其他的如，高度等widget，使用单独的删除接口
    QAction* m_insertAction;   //addToolButton,所需要添加的action的位置，是一个空的action（end），

    QSize m_ToolBtnSize = QSize(36,36);
    QSize m_ToolIconSize = QSize(36,36);
    Qt::ToolButtonStyle m_ToolStyle = Qt::ToolButtonIconOnly;//记录工具栏整体的ToolButtonStyle

    //显示的信息 -- 鼠标的移动坐标信息和操作信息
    QLabel *label_Operation = NULL;

    //记录item的类型  ====  同时也作为鼠标的状态标志 --- 鼠标事件发生的时候执行什么操作（绘制，清空，缩放，拖动等）
    ItemType m_itemType = ItemType::No;
    VisionItem* m_curVisionItem = nullptr;

    QLabel *label_slider = NULL;
    QSlider *pSlider = NULL;

//    Q
    QLabel *label_w;
    QSpinBox *pSpinBox_w;
    QLabel *label_h;
    QSpinBox *pSpinBox_h;
    //缩放的比例显示
    QComboBox *comboBox = NULL;
    QLabel *label_size = NULL;

    QVBoxLayout *mainLayout = NULL;   //主布局
    QHBoxLayout *m_hBoxLayout = NULL;
    QVBoxLayout *m_vBoxLayout = NULL;

    VisionGraphWidget *sceneWidget = NULL;
    QAction *infoWidget_Action = NULL;
    QWidget* infoWidget = NULL;

private slots:
    //对应Action的槽函数
    void slot_selected_action();
    void slot_drag_action();
    void slot_zoom_action();

    void slot_mousePainter_action();
    void slot_mouseClear_action();

    void slot_rect_action();
    void slot_ellipse_action();
    void slot_poly_action();
    void slot_poly_elli_action();

    void slot_open_action();
    void slot_save_action();
    void slot_front_action();
    void slot_next_action();
    void slot_clear_action();

    //绘制item（参数为QRectF，rectangle和ellipse）后，确认后执行的槽函数----调用算法，获取区域，并进行绘制在view
    void slot_addItem(ItemType type,QRectF rf);
    void slot_addPoly(QVector<QPointF> vecPointF);


    //接收view传过来的MouseMoveEvent事件
    void slot_mouseMove(QPointF pointF);
    //接收view传过来的WheelEvent事件
    void slot_wheel(qreal delta);

    //调节鼠标绘制的时候，鼠标的半径
    void slot_valueChanged(int qR);  //绘制鼠标的半径

    //调节view的缩放比例
    void slot_SizeChanged(QString currentSize);
    void slot_SizeChanged(qreal w,qreal h);

    void slot_SceneMouseMove(qreal x,qreal y);
    void slot_actionTriggered(QAction* action);

    void slot_SpinBox_ViewRegionSize(int w);
};
#endif // VISIONGRAPH_REGION_H

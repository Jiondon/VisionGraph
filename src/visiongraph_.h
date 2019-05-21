/****************************************************************************
** @brief       VisionGraph,绘制模块的widget
** @note        会生成一个widget来进行展示绘制模块---主要是优化region和item版本
** @note        不同版本合并为一个类，通过构造的参数来区分版本，方便后续拓展
** @author      xiaodongLi
** @date        create:2019-1-9
** @example
****************************************************************************/


#ifndef VISIONGRAPH__H
#define VISIONGRAPH__H

#include <QFrame>
#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QToolButton>
#include <QIntValidator>

#include <QLabel>
#include <QComboBox>
#include <QLayout>
#include <QAction>
#include <QToolBar>
#include <QSpinBox>
#include <QLineEdit>
#include "visiongraphwidget.h"
#include "visiongraphtool.h"

class VISIONGRAPHSHARED_EXPORT VisionGraph_ : public QFrame
{
    Q_OBJECT
public:
    explicit VisionGraph_(GraphType type = GraphType::graph_Info,ToolButtonDirection toolButtonDirect = ToolButtonDirection::topDirection
            ,QWidget *parent = 0);
public:
    /**
     * @brief       设置GraphType
     * @param       //此接口作废---使用此接口和设置工具栏Direction，会导致工具栏出问题（内部调用）
     * @param       此接口在构造VisionGraph后不可更改
     */
    void setGraphType(GraphType type);

    /**
     * @brief       添加rectangle  可旋转的矩形
     * @param       bEdit 表示编辑
     */
    void setSceneWidgetSize(QSize size);
    void setSceneWidgetSize(qreal w,qreal h);

    /**
     * @brief       主题颜色设置
     * @param
     */
    void setThemeColor(ThemeColor theme);

    /**
     * @brief       带下划线的表示通过程序调用非编辑模式的，不带下划线的，通过绘制操作调用api,
     * @note        带下划线的均无法通过clearPainter()函数进行清除，只能通过scene的clear进行清空，
     */
    QGraphicsRectItem* _addRect(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    QGraphicsPolygonItem* _addPolygon(const QPolygonF &polygon, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    QGraphicsLineItem* _addLine(const QLineF &line, const QPen &pen = QPen());
    QGraphicsEllipseItem* _addEllipse(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    VisionCrossPointItem* _addPoint(QPointF pointF, bool edit = false, qreal length = 5,bool color_enable = false, QColor color = QColor(255,0,0));
    VisionChainItem* _addChain(QList<QPointF> lstP, bool bClosed = false, bool bEdit = false, bool color_enable = false,QColor color = QColor(255,0,0));
    VisionArrow *_addArrow(QPointF pointF,bool bEdit = false,bool color_enable = false,QColor color = QColor(255,0,0));
    VisionCoordinateItem *_addCoordinate(QPointF p,qreal angle = 0,qreal length = 50,bool bEdit = true,
                                        bool color_enable = false,QColor color = QColor(255,0,0));
    /**
     * @brief       添加rectangle  可旋转的矩形
     * @param       bEdit 表示编辑
     */
    VisionRectItem* addRect(QRectF rf,qreal angle = 0,bool bEdit = true, bool bRotation = true,bool color_enable = false,
                            QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加一个arrow
     * @param       不可编辑的坐标系
     */
    VisionArrow *addArrow(QPointF pointF,bool bEdit = false,bool color_enable = false,
                          QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加椭圆
     * @param       默认是可编辑的，未添加不可编辑的椭圆
     */
    VisionEllipseItem* addEllipse(QRectF rf,qreal angle = 0, bool bEdit = true, bool bRotation = true,bool color_enable = false,
                                  QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加圆
     * @param       默认是可编辑的，未添加不可编辑的圆
     */
    VisionCircleItem* addCircle(QRectF rf, bool bEdit = true, bool color_enable = false,
                                QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加圆弧
     * @param       默认是可编辑的，未添加不可编辑的圆弧
     */
    VisionArcItem *addArc(QPointF sP,QPointF mP,QPointF fP, bool bEdit = true,bool color_enable = false,
                          QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    VisionArcItem *addArc(QPointF center,qreal r,qreal angle,qreal spanAngle, bool bEdit = true, bool color_enable = false,
                          QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加线
     * @param       具体方法未实现
     */
    VisionLineItem* addLine(QLine line, bool bEdit = true,bool color_enable = false,
                            QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));


    /**
     * @brief       添加线--不限数量
     * @param       具体方法未实现
     */
    VisionLine* addLines(QList<QLineF> lstLineF, bool color_enable = false,
                         QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));


    /**
     * @brief       添加多边形/close为false，为折线
     * @param       点的集合，点的集合一次连接
     */
    VisionPolygon* addPolygon(QVector<QPointF> vecPointF, bool bClose = true, bool bEdit = true,bool color_enable = false,
                              QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加一个点
     * @param
     */
    VisionCrossPointItem *addPoint(QPointF pointF, bool bEdit = false, qreal length = 5,bool color_enable = false,
                                   QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加一个点 -- 不限数量
     * @param
     */
    VisionPoint *addPointFs(QList<QPointF> lstP, bool color_enable = false,
                            QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加一个链
     * @param
     */
    VisionChainItem *addChain(QList<QPointF> lstP,bool close = false,bool edit = true,bool color_enable = false,
                              QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));


    // Fitting

    /**
     * @brief       添加线Fitting
     */
    VisionLineItemFitting* addLineFitting(QLine line, bool bEdit = true, qreal length = 0,bool color_enable = false,
                                          QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加圆弧Fitting
     * @param       默认是可编辑的，未添加不可编辑
     */
    VisionArcItemFitting *addArcFitting(QPointF sP,QPointF mP,QPointF fP, bool bEdit = true, qreal length = 0,
                                        bool color_enable = false,
                                        QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加圆Fitting
     * @param       默认是可编辑的，未添加不可编辑
     */
    VisionCircleItemFitting *addCircleFitting(QRectF rf = QRectF(0,0,0,0), bool bEdit = true, qreal length = 0,
                                              bool color_enable = false,
                                              QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));


    /**
     * @brief       添加折线Fitting
     * @param       默认是可编辑的，未添加不可编辑
     */
    VisionPolygonItemFitting *addPolygonFitting(QVector<QPointF> vecPointF, bool bClose = true,bool bEdit = true, qreal length = 0,
                                                bool color_enable = false,QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));


    /**
     * @brief       添加坐标系
     * @param       默认是不可编辑.当前不支持编辑坐标系（拖动，旋转等操作）
     */
    VisionCoordinateItem *addCoordinate(QPointF p,qreal angle = 0,qreal length = 50,bool bEdit = true,
                                        bool color_enable = false,
                                        QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加文本控件
     * @param       默认是不可编辑.当前不支持编辑（拖动，旋转等操作）
     */
    VisionTextItem *addText(VGRegion region, QString name = "?");

    /**
     * @brief       设置view的背景图片
     * @param
     */
    int setBkImg(QImage image);

    void removeBkImg();

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
//        view->clearPainter();
        slot_clear_action();
    }

    /**
     * @brief       获取当前绘制在view的区域
     * @param       XVRegion
     */
    XVRegion* getRegion(){
        return view->getRegion();
    }

    /**
     * @brief       获取当前view中的所有的item
     * @param       VisionItem*
     */
    QList<VisionItem*> getItems(){
        return m_lstItem;
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
     * @brief       自适应大小并居中，返回缩放的比例（放大或者缩小，1-正常大小）-- 算法区域
     */
    qreal adjustSize(qreal w,qreal h);

    /**
     * @brief       设置View的算法区域的Visible
     */
    void setViewRegion_Visible(bool bVisible);

    /**
     * @brief       设置View的算法区域的color
     */
    void setViewRegion_Color(const QColor &color);

    /**
     * @brief       获取背景图片
     */
    QImage getBkgImg();

    /**
     * @brief       保存当前绘图区域的绘制信息，生成图片
     * @param       path==""调用fileDialog进行设置保存
     */
    void saveBkgImg(QString path="");

    /**
     * @brief       删除具体的item
     * @param       item == nullptr 默认删除选中的
     */
    void removeItem(VisionItem* item = nullptr);

    /**
     * @brief       设置鼠标绘制的时候，鼠标的大小
     */
    void setMousePaintSize(qreal qi);

    /**
     * @brief       设置view的缩放比例
     * @param       value = 1 表示是标准大小
     */
    void setView_Zoom(qreal qZoom);

    /**
     * @brief       设置view的type
     * @param       view中显示的内容（viewType） -- 单个item，多个item等
     */
    void setViewType(ViewType type = ViewType::freeItem);

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
     * @brief       获取view中的item数据
     * @param
     */
    vector<VisionItem*> getData();

    /**
     * @brief       获取view中的选中的item数据（当有且仅有一个的时候，默认其为当前）
     * @param
     */
    VisionItem *getCurData();
//    Paint_Rect Paint_EllipseItem Paint_CirCle Paint_Poly Paint_polyLine Paint_Arc point line
//    selectedColor = QColor(255,0,0);
//    borderColor = QColor(255,0,0);
//    brushColor = QColor(255,0,0,160);
    void setRectColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setEllipseColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setCircleColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setPolyColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setPolyLineColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setArcColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setPointColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setLineColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    void setRegionColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160),
                        QColor brushColor_unEdit = QColor(255,0,0,200));

    void setListRegionColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

signals:
    void signal_itemFinished(VisionItem* item);
    void signal_Changed(VisionItem* item);

private:
    void initScene();
    void initTool_operation();  //水平的工具栏
    void initToolBar();
    void initLayout(ToolButtonDirection toolButtonDirect);

    bool checkoutItem();

private:
    VisionGraphScene *scene = nullptr;
    VisionGraphView *view = nullptr;

    QList<VisionItem*> m_lstItem;
    QList<VisionItem*> m_lstItemSelected;


    QList<QPointF> m_lstPainterPointF;  //绘制算法提供的直线的点的集合（两两配对）

//    XVCreateRegionIn regionIn;


    QGraphicsPixmapItem *m_bkPixmapItem = nullptr;  //背景图片
    QGraphicsPixmapItem *m_mousePixmap = nullptr;  //调整鼠标的大小的时候，显示在区域中心的图片

    qreal m_zoom = 1;   //图形View的缩放比例

    ToolButtonDirection  m_toolButtonDirection = ToolButtonDirection::topDirection;  //tool按钮的位置
    QToolBar *tool_Widget = NULL;


private:

    //左侧工具栏 -- 绘制类（操作类）
    QToolButton *sys_selected_button;
    QToolButton *sys_drag_button;
    QToolButton *sys_zoom_button;  //将拖动的恢复到当前窗口
    QToolButton *sys_fit_button;  //调整比例，适应当前窗口


    QToolButton *sys_mousePainter_button;
    QToolButton *sys_mouseClear_button;

    QToolButton *sys_save_button;

    QToolButton *sys_rect_button;
    QToolButton *sys_ellipse_button;
    QToolButton *sys_circle_button;
    QToolButton *sys_arc_button;
    QToolButton *sys_poly_button;
    QToolButton *sys_poly_elli_button;
    QToolButton *sys_point_button;
    QToolButton *sys_line_button;
    QToolButton *sys_polyLine_button;

    //右侧工具栏 -- 功能类
    QToolButton *sys_open_project_button;  //打开工程
    QToolButton *sys_front_button;  //撤销
    QToolButton *sys_next_button;   //取消撤销
    QToolButton *sys_clear_button;  //清空绘图区域
    QToolButton *sys_remove_item_button;  //删除当前选中的item

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

    QLabel *label_mouseSizeText = NULL;
    QLabel *label_slider = NULL;
    QSlider *pSlider = NULL;

    QSpinBox *pSpinBox = NULL;
    QLabel *label_w = NULL;
    QSpinBox *pSpinBox_w = NULL;
    QLabel *label_h = NULL;
    QSpinBox *pSpinBox_h = NULL;
    //缩放的比例显示
    QComboBox *comboBox = NULL;
    QLabel *label_size = NULL;
    QToolBar *tool_infoWidget = NULL;

    QVBoxLayout *mainLayout = NULL;   //主布局
    QHBoxLayout *m_hBoxLayout = NULL;
    QVBoxLayout *m_vBoxLayout = NULL;

    VisionGraphWidget *sceneWidget = NULL;

    QAction *infoWidget_Action;
    QWidget* infoWidget = NULL;

    GraphType m_graphType = GraphType::graphItem_unSelf;   //item的模式，用户交互绘制item？
    ViewType m_viewType = ViewType::freeItem;

    bool m_bWheel = false;   //comboBox值变化的 是否触发对应的槽函数，true，不触发，false 触发（wheel事件导致的缩放，均不触发）

private slots:
    //对应Action的槽函数
    void slot_selected_action();
    void slot_drag_action();
    void slot_zoom_action();
    void slot_fit_action();

    void slot_mousePainter_action();
    void slot_mouseClear_action();

    void slot_save_action();

    void slot_rect_action();
    void slot_ellipse_action();
    void slot_circle_action();
    void slot_arc_action();
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
    void slot_addPoly(QVector<QPointF> vecPointF, ItemType type);
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

    //调节鼠标绘制的时候，鼠标的半径
    void slot_valueChanged(int qR);  //绘制鼠标的半径

    void slot_SceneMouseMove(qreal x,qreal y);
    void slot_actionTriggered(QAction* action);

    void slot_SpinBox_ViewRegionSize(int w);

    //当GraphType变化的时候，调用该函数刷新
    void slot_GraphTypeChanged(GraphType type);

    void slotItemFinished(VisionItem* item);

private:
    void init_graph_info();
    void init_graphRegion();
    void init_graphItem_self();
    void init_graphItem_unSelf();
    void init_graphChain();
    void init_graphFitting();
    void init_graph_Item(GraphType type);


private:
    //    Paint_Rect Paint_EllipseItem Paint_CirCle Paint_Poly Paint_polyLine Paint_Arc point line

    QColor borderColor_Rect,selectedColor_Rect,brushColor_Rect;
    QColor borderColor_Ellipse,selectedColor_Ellipse,brushColor_Ellipse;
    QColor borderColor_Circle,selectedColor_Circle,brushColor_Circle;
    QColor borderColor_Poly,selectedColor_Poly,brushColor_Poly;
    QColor borderColor_PolyLine,selectedColor_PolyLine,brushColor_PolyLine;
    QColor borderColor_Arc,selectedColor_Arc,brushColor_Arc;
    QColor borderColor_Point,selectedColor_Point,brushColor_Point;
    QColor borderColor_Line,selectedColor_Line,brushColor_Line;

    QColor borderColor_Region,selectedColor_Region,brushColor_Region;

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // VISIONGRAPH__H

/****************************************************************************
** @brief       VisionGraph,绘制模块的widget
** @note        会生成一个widget来进行展示绘制模块，综合了region和item两种版本
** @author      xiaodongLi
** @date        create:2018-10-24
** @example
****************************************************************************/

#ifndef VISIONGRAPH_H
#define VISIONGRAPH_H

#include <QWidget>
#include <QWheelEvent>

#include "visiongraph_global.h"
#include "visiongraphtool.h"
#include "visiongraph_.h"

class VISIONGRAPHSHARED_EXPORT VisionGraph : public QWidget
{
    Q_OBJECT
public:
    VisionGraph(GraphType type = GraphType::graph_Info, ToolButtonDirection toolButtonDirect = ToolButtonDirection::topDirection, QWidget *parent = 0);

    ~VisionGraph();
    /**
     * @brief       添加rectangle  可旋转的矩形
     * @param       bEdit 表示编辑
     */
    void setSceneWidgetSize(QSize size);
    void setSceneWidgetSize(qreal w,qreal h);

    /**
     * @brief       设置GraphType
     * @param       此接口在构造VisionGraph后不可更改  ****
     */
    void setGraphType(GraphType type);

    /**
     * @brief       主题颜色设置
     * @param
     */
    void setThemeColor(ThemeColor theme);

    /**
     * @brief       添加rectangle  可旋转的矩形
     * @param       bEdit 表示编辑
     */
    VisionRectItem *addRect(QRectF rf,qreal angle = 0, bool bEdit = true,bool bRotation = true,
                            bool color_enable = false,QColor color = QColor(255,0,0));



    /**
     * @brief       带下划线的表示通过程序调用非编辑模式的，不带下划线的，通过绘制操作调用api,
     * @note        带下划线的均无法通过clearPainter()函数进行清除，只能通过scene的clear进行清空，
     */

    /**
     * @brief       在scene中添加rectangle  不可编辑
     * @note        带下划线的均无法通过clearPainter()函数进行清除，只能通过scene的clear进行清空，
     */
    QGraphicsRectItem* _addRect(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());

    /**
     * @brief       在scene中添加polygon  不可编辑
     * @note        带下划线的均无法通过clearPainter()函数进行清除，只能通过scene的clear进行清空，
     */
    QGraphicsPolygonItem* _addPolygon(const QPolygonF &polygon, const QPen &pen = QPen(), const QBrush &brush = QBrush());

    /**
     * @brief       在scene中添加line  不可编辑
     * @note        带下划线的均无法通过clearPainter()函数进行清除，只能通过scene的clear进行清空，
     */
    QGraphicsLineItem* _addLine(const QLineF &line, const QPen &pen = QPen());

    /**
     * @brief       在scene中添加Ellipse  不可编辑
     * @note        带下划线的均无法通过clearPainter()函数进行清除，只能通过scene的clear进行清空，
     */
    QGraphicsEllipseItem* _addEllipse(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());

    /**
     * @brief       在scene中添加CrossPoint  不可编辑
     * @note        带下划线的均无法通过clearPainter()函数进行清除，只能通过scene的clear进行清空，
     */
    VisionCrossPointItem* _addPoint(QPointF pointF, bool edit = false, qreal length = 5,
                                    bool color_enable = false,QColor color = QColor(255,0,0));

    /**
     * @brief       添加一个arrow
     * @param       不可编辑的坐标系
     * @note        带下划线的均无法通过clearPainter()函数进行清除，只能通过scene的clear进行清空，
     */
    VisionArrow *_addArrow(QPointF pointF, bool bEdit = false, bool color_enable = false,QColor color = QColor(255,0,0 ));

    /**
     * @brief       在scene中添加链
     * @note        带下划线的均无法通过clearPainter()函数进行清除，只能通过scene的clear进行清空，
     */
    VisionChainItem* _addChain(QList<QPointF> lstP, bool bClosed = false, bool bEdit = false,
                               bool color_enable = false,QColor color = QColor(255,0,0));

    /**
     * @brief       在scene中添加坐标系  不可编辑的，区别于不带下划线的部分
     * @note        带下划线的均无法通过clearPainter()函数进行清除，只能通过scene的clear进行清空，
     */
    VisionCoordinateItem *_addCoordinate(QPointF p,qreal angle = 0,qreal length = 50,bool bEdit = true,
                                        bool color_enable = false,QColor color = QColor(255,0,0));

    /**
     * @brief       添加椭圆
     * @param       默认是可编辑的，未添加不可编辑的椭圆
     */
    VisionEllipseItem* addEllipse(QRectF rf,qreal angle = 0,bool bEdit = true, bool bRotation = true,
                                  bool color_enable = false,QColor color = QColor(255,0,0));

    /**
     * @brief       添加圆
     * @param       默认是可编辑的，未添加不可编辑的圆
     */
    VisionCircleItem* addCircle(QRectF rf, bool bEdit = true,bool color_enable = false, QColor color = QColor(255,0,0));

    /**
     * @brief       添加圆弧
     * @param       默认是可编辑的，未添加不可编辑的圆弧
     */
    VisionArcItem *addArc(QPointF sP,QPointF mP,QPointF fP, bool bEdit = true,
                          bool color_enable = false, QColor color = QColor(255,0,0));
    VisionArcItem *addArc(QPointF center,qreal r,qreal angle,qreal spanAngle, bool bEdit = true,
                          bool color_enable = false,QColor color = QColor(255,0,0));

    /**
     * @brief       添加线
     * @param
     */
    VisionLineItem* addLine(QLine line, bool bEdit = true,bool color_enable = false, QColor color = QColor(255,0,0));


    /**
     * @brief       添加线
     * @param       不可编辑，可实现大数量线的绘制，只支持程序调用
     */
    VisionLine* addLines(QList<QLineF> lstLineF,bool color_enable = false, QColor color = QColor(255,0,0));


    /**
     * @brief       添加多边形
     * @param       点的集合，点的集合一次连接
     */
    VisionPolygon* addPolygon(QVector<QPointF> vecPointF, bool bClose = true, bool bEdit = false,
                              bool color_enable = false,QColor color = QColor(255,0,0));

    /**
     * @brief       添加一个点
     * @param
     */
    VisionCrossPointItem* addPoint(QPointF pointF, bool bEdit = false, qreal length = 5,
                                   bool color_enable = false,QColor color = QColor(255,0,0));

    /**
     * @brief       添加一个点 -- 不限数量
     * @param
     */
    VisionPoint *addPointFs(QList<QPointF> lstP, bool color_enable = false,QColor color = QColor(255,0,0));

    /**
     * @brief       添加一个链
     * @param
     */
    VisionChainItem *addChain(QList<QPointF> lstP, bool close = false,bool edit = true,
                              bool color_enable = false, QColor color = QColor(255,0,0));

    /**
     * @brief       获取当前绘制在view的区域  region版本
     * @param       XVRegion
     */
    XVRegion *getRegion();

    /**
     * @brief       获取当前view中的所有的item
     * @param       VisionItem*
     */
    QList<VisionItem*> getItems();


    /**
     * @brief       添加坐标系
     * @param       默认是不可编辑.当前不支持编辑坐标系（拖动，旋转等操作）
     */
    VisionCoordinateItem *addCoordinate(QPointF p,qreal angle = 0,qreal length = 50,bool bEdit = true,
                                        bool color_enable = false,QColor color = QColor(255,0,0));


    /**
     * @brief       添加文本控件
     * @param       默认是不可编辑.当前不支持编辑（拖动，旋转等操作）
     */
    VisionTextItem *addText(VGRegion region, QString name = "?");

    /**
     * @brief       添加区域
     * @param       默认是不可编辑.当前不支持编辑（拖动，旋转等操作）
     */
    VisionRegion *addRegion(VGRegion *region, QColor color = QColor(255,0,0,180));
    VisionRegion *addRegion(vector<VGRegionPair> vec_regionPair);

    /**
     * @brief       设置VisionGraph的背景，区分版本
     */
    void setBkImg(QImage image);
    void removeBkImg();


    /**
     * @brief       设置toolButton的布局
     * @param
     */
    void setToolButton_Direction(ToolButtonDirection direct);


    /**
     * @brief      设置颜色(选中)
     * @param
     */
    void setSelectedColor(QColor color);


    /**
     * @brief      设置颜色(边框)
     * @param
     */
    void setBorderColor(QColor color);


    /**
     * @brief      设置颜色(填充)
     * @param
     */
    void setBrushColor(QColor color);


    /**
     * @brief      显示VisionGraph
     * @param
     */
    void show();


    /**
     * @brief       获取view
     * @param
     */
    VisionGraphView* getView();


    /**
     * @brief       修改绘制的item时候触发
     * @param       在使用鼠标移动进行绘制任意区域的时候，鼠标本身的大小作为绘制要素之一
     * @param       绘制不同的item，有不同的鼠标样式
     */
    void setPainterCursorR(qreal qR);

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
    void setViewInfo_Color(QColor backgroundColor, QColor textColor);

    /**
     * @brief       设置工具栏的icon的路径
     */
    void setIconPath(QString iconpath);


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
     * @brief       不显示toolbar的view的信息 -- 缩放比例和视图的w，h不显示
     */
    void removeToolBarInfoWidget();

    /**
     * @brief       在工具栏添加frame布局
     * @param        todo,未实现
     */
    void addToolFrame();

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

    //补充工具栏的相关api和信息获取
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

    /**
     * @brief       获取VisionGraph的样式表
     * @param
     */
    void setGraphStyleSheet(QString strStyleSheet);

    void setRectColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setEllipseColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setCircleColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setPolyColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setPolyLineColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setArcColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setPointColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setLineColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    //region主要是brushColor有效
    void setRegionColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160),
                        QColor brushColor_unEdit = QColor(255,0,0,200));

signals:
    void signal_PaintFinishedChanged(VisionItem*);
    void signal_Changed(VisionItem* item);

protected:
    void wheelEvent(QWheelEvent *event);

private:
    VisionGraph_ *m_graphWidget = nullptr;
    GraphType m_graphType = GraphType::graphItem_unSelf;


    QColor selectedColor = QColor(255,0,0);
    QColor borderColor = QColor(0,0,0);
    QColor brushColor = QColor(255,0,0,50);
    QColor regionColor = QColor(255,0,0);  //暂时和brushColor合并

    //暂时未用，
    QColor viewMouseInfo_TextColor = QColor(255,255,255);
    QColor viewMouseInfo_BackgroundColor = QColor(255,255,255);


    QString iconPath = "./ico/graph/";

    QCursor viewCursor;
};

#endif // VISIONGRAPH_H

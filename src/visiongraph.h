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
#include "visiongraph_global.h"
#include "visiongraphtool.h"
#include "visiongraph_base.h"
#include "visiongraph_region.h"
#include "visiongraph_item.h"
#include "visiongraph_.h"



class VISIONGRAPHSHARED_EXPORT VisionGraph : public QWidget
{
    Q_OBJECT
public:
    VisionGraph(GraphType type = GraphType::graphItem_unSelf, ToolButtonDirection toolButtonDirect = ToolButtonDirection::topDirection, QWidget *parent = 0);

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
    VisionRectItem *addRect(QRectF rf, bool bEdit = true,bool bRotation = true, QColor color = QColor(255,0,0));


    /**
     * @brief       在scene中添加rectangle  不可编辑
     */
    QGraphicsRectItem* _addRect(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());

    /**
     * @brief       在scene中添加polygon  不可编辑
     */
    QGraphicsPolygonItem* _addPolygon(const QPolygonF &polygon, const QPen &pen = QPen(), const QBrush &brush = QBrush());

    /**
     * @brief       在scene中添加line  不可编辑
     */
    QGraphicsLineItem* _addLine(const QLineF &line, const QPen &pen = QPen());

    /**
     * @brief       在scene中添加Ellipse  不可编辑
     */
    QGraphicsEllipseItem* _addEllipse(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());

    /**
     * @brief       在scene中添加CrossPoint  不可编辑
     */
    VisionCrossPointItem* _addPoint(QPointF pointF,bool edit = false,QColor color = QColor(255,0,0));

    /**
     * @brief       添加一个arrow
     * @param       不可编辑的坐标系
     */
    VisionArrow *_addArrow(QPointF pointF, bool bEdit = false, QColor color = QColor(255,0,0 ));

    /**
     * @brief       在scene中添加链
     */
    VisionChainItem* _addChain(QList<QPointF> lstP, bool bClosed = false, bool bEdit = false,QColor color = QColor(255,0,0));

    /**
     * @brief       添加椭圆
     * @param       默认是可编辑的，未添加不可编辑的椭圆
     */
    VisionEllipseItem* addEllipse(QRectF rf,bool bEdit = true, bool bRotation = true, QColor color = QColor(255,0,0));

    /**
     * @brief       添加线
     * @param       具体方法未实现
     */
    VisionLineItem* addLine(QLine line, bool bEdit = true, QColor color = QColor(255,0,0));


    /**
     * @brief       添加线
     * @param       具体方法未实现
     */
    void addLines(QList<QLine> lstLine,QColor color = QColor(255,0,0));


    /**
     * @brief       添加多边形
     * @param       点的集合，点的集合一次连接
     */
    VisionPolygon* addPolygon(QVector<QPointF> vecPointF, bool bClose = true, bool bEdit = false, QColor color = QColor(255,0,0));

    /**
     * @brief       添加一个点
     * @param       具体方法未实现
     */
    VisionCrossPointItem* addPoint(QPointF pointF, bool bEdit = false, QColor color = QColor(255,0,0));

    /**
     * @brief       添加一个链
     * @param
     */
    VisionChainItem *addChain(QList<QPointF> lstP, bool close = false,bool edit = true, QColor color = QColor(255,0,0));

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
     * @brief       设置VisionGraph的背景，区分版本
     */
    void setBkImg(QImage image);


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
     * @brief      设置颜色(区域)
     * @param
     */
    void setRegionColor(QColor color);


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

signals:
    void signal_PaintFinishedChanged(VisionItem*);

protected:


private:
    VisionGraph_ *m_graphWidget = nullptr;
};

#endif // VISIONGRAPH_H

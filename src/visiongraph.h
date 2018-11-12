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

#include "visiongraph_region.h"
#include "visiongraph_item.h"


/**
 * @brief       枚举VisionGraph的几种版本，
 * @note        graphRegion --- region版本（绘制item后，item失焦后，会通过算法生成区域，此过程不可逆）,需要用户交互（绘制需要用户进行操作）
 * @note        graphItem_self --- item版本（绘制item后，在整个过程中都是可调节的）,不要用户交互，主要是代码中直接调用放开的api来进行绘制
 * @note        graphItem_unSelf --- item版本，需要用户交互（绘制需要用户进行操作）
 */
enum GraphType{
    graphRegion,
    graphItem_self,
    graphItem_unSelf
};

class VISIONGRAPHSHARED_EXPORT VisionGraph : public QWidget
{
    Q_OBJECT
public:
    VisionGraph(GraphType type = GraphType::graphRegion, ToolButtonDirection toolButtonDirect = ToolButtonDirection::topDirection, QWidget *parent = 0);

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
     * @brief       获取当前绘制在view的区域  region版本
     * @param       XVRegion
     */
    XVRegion *getRegion();

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
     * @brief       设置icon的路径
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
     * @brief       不显示toolbar的view的信息
     */
    void removeToolBarInfoWidget();

    /**
     * @brief       在工具栏添加frame布局
     * @param        todo,未实现
     */
    void addToolFrame();

protected:

private:
    GraphType m_type;

private:
    VisionGraph_Region *m_graphWidget_Region = nullptr;
    VisionGraph_Item *m_graphWidget_Item = nullptr;

};

#endif // VISIONGRAPH_H

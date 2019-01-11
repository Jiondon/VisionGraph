#ifndef VISIONGRAPH_BASE_H
#define VISIONGRAPH_BASE_H

#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QToolButton>

#include "visiongraphtool.h"


enum ItemModel{
    self,
    un_self,
    region_self
};


class VISIONGRAPHSHARED_EXPORT VisionGraph_Base : public QFrame
{
    Q_OBJECT
public:
    VisionGraph_Base(QWidget *parent = 0);

public:
    /**
     * @brief       添加rectangle  可旋转的矩形
     * @param       bEdit 表示编辑
     */
    virtual void setSceneWidgetSize(QSize size) = 0;
    virtual void setSceneWidgetSize(qreal w,qreal h) = 0;

    /**
     * @brief       添加rectangle  可旋转的矩形
     * @param       bEdit 表示编辑
     */
    virtual VisionRectItem* addRect(QRectF rf,bool bEdit = true,QColor color = QColor(255,255,255)) = 0;

    virtual QGraphicsRectItem* _addRect(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush()) = 0;
    virtual QGraphicsPolygonItem* _addPolygon(const QPolygonF &polygon, const QPen &pen = QPen(), const QBrush &brush = QBrush()) = 0;
    virtual QGraphicsLineItem* _addLine(const QLineF &line, const QPen &pen = QPen()) = 0;
    virtual QGraphicsEllipseItem* _addEllipse(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush()) = 0;
    virtual VisionCrossPointItem* _addPoint(QPointF pointF,QColor color = QColor(255,255,255)) = 0;
    virtual VisionChainItem* _addChain(QList<QPointF> lstP,QColor color = QColor(255,255,255)) = 0;

    /**
     * @brief       添加一个arrow
     * @param       不可编辑的坐标系
     */
    virtual VisionArrow *_addArrow(QPointF pointF,QColor color = QColor(255,255,255)) = 0;

    /**
     * @brief       添加椭圆
     * @param       默认是可编辑的，未添加不可编辑的椭圆
     */
    virtual VisionEllipseItem* addEllipse(QRectF rf,QColor color = QColor(255,255,255)) = 0;

    /**
     * @brief       添加线
     * @param       具体方法未实现
     */
    virtual VisionLineItem* addLine(QLine line,QColor color = QColor(255,255,255)) = 0;

    /**
     * @brief       添加线
     * @param       具体方法未实现
     */
    virtual void addLines(QList<QLine> lstLine,QColor color = QColor(255,255,255)) = 0;

    /**
     * @brief       添加多边形
     * @param       点的集合，点的集合一次连接
     */
    virtual VisionPolygon* addPolygon(QVector<QPointF> vecPointF,QColor color = QColor(255,255,255)) = 0;

    /**
     * @brief       添加一个点
     * @param       具体方法未实现
     */
    virtual VisionCrossPointItem* addPoint(QPointF pointF,QColor color = QColor(255,255,255)) = 0;


    /**
     * @brief       设置view的背景图片
     * @param
     */
    virtual int setBkImg(QImage image) = 0;


    /**
     * @brief       获取当前绘制在view的区域
     * @return       XVRegion
     */
    virtual XVRegion* getRegion() = 0;

    /**
     * @brief       获取当前view中的所有的item，在region版本中，只存在m_curVisionItem
     * @param       VisionItem*
     */
    virtual QList<VisionItem*> getItems() = 0;

    /**
     * @brief       设置toolButton的布局
     * @param
     */
    virtual void setToolButton_Direction(ToolButtonDirection direct) = 0;

    /**
     * @brief       获取view
     * @param
     */
    virtual VisionGraphView* getView() = 0;
    /**
     * @brief       修改绘制的item时候触发
     * @param       在使用鼠标移动进行绘制任意区域的时候，鼠标本身的大小作为绘制要素之一
     * @param       绘制不同的item，有不同的鼠标样式
     */
    virtual void setPainterCursorR(qreal qR) = 0;

    /**
     * @brief       设置记录当前所要绘制的item
     */
    virtual void setItemType(ItemType type) = 0;


    /**
     * @brief       view的缩放比例
     */
    virtual void zoom(float scaleFactor) = 0;


    /**
     * @brief       撤销区域生成
     */
    virtual void back_region() = 0;


    /**
     * @brief       恢复区域生成
     */
    virtual void front_region() = 0;


    /**
     * @brief       清除view的绘制数据
     */
    virtual void clearPainter() = 0;

    /**
     * @brief       设置View信息框的显示或者隐藏
     */
    virtual void setViewInfo_Visible(bool bVisible) = 0;

    /**
     * @brief       设置View信息框的位置（四个拐角）
     */
    virtual void setViewInfo_Pos(Corner corner) = 0;

    /**
     * @brief       设置View信息框的位置（任意位置）
     */
    virtual void setViewInfo_Pos(qreal x,qreal y) = 0;

    /**
     * @brief       设置View信息框的大小
     */
    virtual void setViewInfo_Size(QSize size) = 0;

    virtual void setViewInfo_Size(qreal w,qreal h) = 0;


    /**
     * @brief       设置View信息框的文本
     */
    virtual void setViewInfo_text(QString text) = 0;

    /**
     * @brief       设置View信息框的颜色（背景颜色和文本颜色）
     */
    virtual void setViewInfo_Color(QColor backgroundColor,QColor textColor) = 0;

    /**
     * @brief       获取ToolButton
     */
    virtual QToolButton* getToolButton(ToolButtonType type) = 0;


    /**
     * @brief       删除ToolButton
     */
    virtual bool removeToolButton(ToolButtonType type) = 0;

    /**
     * @brief       添加ToolButton
     */
    virtual void addToolButton(QToolButton* btn) = 0;

    /**
     * @brief       不显示toolbar的view的信息
     */
    virtual void removeToolBarInfoWidget() = 0;

    /**
     * @brief       设置View的算法区域的大小
     */
    virtual void setViewRegion_Size(qreal w,qreal h) = 0;

    /**
     * @brief       自适应大小并居中，返回缩放的比例（放大或者缩小，1-正常大小）-- 算法区域
     */
    virtual qreal adjustSize(qreal w,qreal h) = 0;

    /**
     * @brief       设置View的算法区域的Visible
     */
    virtual void setViewRegion_Visible(bool bVisible) = 0;

    /**
     * @brief       设置View的算法区域的color
     */
    virtual void setViewRegion_Color(const QColor &color) = 0;

    /**
     * @brief       获取背景图片
     */
    virtual QImage getBkgImg() = 0;

    /**
     * @brief       保存当前绘图区域的绘制信息，生成图片
     * @param       path==""调用fileDialog进行设置保存
     */
    virtual void saveBkgImg(QString path="") = 0;

    /**
     * @brief       删除具体的item
     * @param       item == nullptr 默认删除选中的
     */
    virtual void removeItem(VisionItem* item = nullptr) = 0;

    /**
     * @brief       设置鼠标绘制的时候，鼠标的大小
     */
    virtual void setMousePaintSize(qreal qi) = 0;

    /**
     * @brief       设置view的缩放比例
     * @param       value = 1 表示是标准大小
     */
    virtual void setView_Zoom(qreal qZoom) = 0;

    /**
     * @brief       设置view的type
     * @param       view中显示的内容（viewType） -- 单个item，多个item等
     */
    virtual void setViewType(ViewType type = ViewType::freeItem) = 0;

signals:
    void signal_itemFinished(VisionItem* item);

};

#endif // VISIONGRAPH_BASE_H

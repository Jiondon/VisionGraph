/****************************************************************************
** @brief       自定义path类
** @note        给定一个path，直接绘制 -- 理解为特殊的poly，目前只作为大数量的poly非编辑版本
** @author      xiaodongLi
** @date        create:2018-09-28
** @example
** @note        还未进行具体进行封装 -- todo
****************************************************************************/


#ifndef VISIONPATHITEM_H
#define VISIONPATHITEM_H

#include <QObject>
#include <QColor>
#include "../control/visionitem.h"

#include "../control/minirect.h"


//此类不建议使用正常的path，非严格意义的path，只是为了和poly进行区分，poly才是我们使用的可编辑可显示的path
//VisionPathItem只是为了大数量的poly绘制封装的，并且都是不可编辑的，只作为显示使用
class VISIONGRAPHSHARED_EXPORT VisionPathItem : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionPathItem(bool color_enable = false, QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160),
                            VisionItem *parent = 0);
    ~VisionPathItem();

    /**
     * @brief       path设置点集接口
     * @note        二维数组，多个poly。多个多边形点集
     * @param       pointFs 多边形点集，
     */
    void setPointFs(QVector<QVector<QPointF> > vec_vec_pointF);

    /**
     * @brief       判断点（x,y）是否在该item内
     * @param       bool
     */
    bool getPosInArea(qreal x, qreal y);


    /**
     * @brief       获取多边形的每个顶点
     * @param       point vec
     */
    QVector<QPointF> getPoints(){
        QVector<QPointF> vec;
        return vec;
    }

    VGPath getData(){
        VGPath vgPath;
//        vector<VGPoint2D> vec_p;
//        vec_p.clear();
//        for(int i=0;i<m_vecPointFs.count();i++){
//            VGPoint2D point2D;
//            point2D.x = m_vecPointFs.at(i).x();
//            point2D.y = m_vecPointFs.at(i).y();
//            vec_p.push_back(point2D);
//        }
//        vgPath.arrayPoint2D = vec_p;
//        vgPath.closed = m_bClose;
        return vgPath;
    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

signals:
    void signalChanged(VisionItem* item);

private:

    qreal m_x = 0;
    qreal m_y = 0;
    QVector<QVector<QPointF>> m_vec_vecPointF;
    QVector<QVector<QPointF>> m_vec_vecPointF_temp;


    QVector<QPolygonF> m_vec_polygonF;
    QPolygonF m_polygonF_temp;  //存放所有的点，同时生成有效区域

    bool m_bClose = true; //多边形是否封闭变量控制

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

public slots:
};

#endif // VISIONPATHITEM_H

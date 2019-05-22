/****************************************************************************
** @brief       自定义Region
** @note        区域控件，多条线组成一部分区域
** @author      xiaodongLi
** @date        create:2018-09-28
** @example
****************************************************************************/


#ifndef VISIONREGION_H
#define VISIONREGION_H

#include <QObject>
#include "../control/visionitem.h"
#include "../control/color.h"

#include <QPainter>

struct VGRegionPair{
    VGRegion *region;
    int value;
    QColor color;
};

class VISIONGRAPHSHARED_EXPORT VisionRegion : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionRegion(VisionItem *parent = 0);

    void setRegionData(VGRegion *region, QColor color = QColor(255,0,0,160));

    void setRegionData(vector<VGRegionPair> vec_regionPair);  //链表
    void addRegionData(VGRegion *region,QColor color);  //添加到链表

    void clearRegion();

    QVector<QPointF> getPoints(){
        QVector<QPointF> vec_p;
        return vec_p;
    }

    bool getPosInArea(qreal x, qreal y){
        return true;
    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

signals:
    void signalChanged(VisionItem* item);

private:
    QVector<QLineF> m_vecLines;
    QColor m_regionColor = QColor(255,0,0,160);

    qreal m_w = 0;
    qreal m_h = 0;

    vector<VGRegionPair> m_vecRegionPair;

private:

public slots:
};

#endif // VISIONREGION_H

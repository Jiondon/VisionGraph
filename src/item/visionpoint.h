/****************************************************************************
** @brief       基于VisionItem类封装的自定义point类
** @note        该类主要是用于绘制大数量的点的控件，只作为显示，主要是为了解决大数量点单独绘制的耗时问题
** @author      xiaodongLi
** @date        create:2019-02-20
** @example     /as VisionLine
****************************************************************************/


#ifndef VISIONPOINT_H
#define VISIONPOINT_H

#include <QObject>
#include <QPainter>
#include "../control/visionitem.h"


class VISIONGRAPHSHARED_EXPORT VisionPoint : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionPoint(QColor color = QColor(255,0,0),VisionItem *parent = 0);

    void setPointF(QPointF pointF);
    void setPointFs(QList<QPointF> lstP);

    QPointF getP(){
        return m_pointF;
    }

    /**
     * @brief       获取每个顶点
     * @param       point vec
     */
    QVector<QPointF> getPoints();


    bool getPosInArea(qreal x,qreal y);

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    enum Style{
        SINGLE,
        MULTI
    };

signals:
    void signalChanged(VisionItem* item);

private:
    QPointF m_pointF;
    QList<QPointF> m_lstPointF;
    Style m_style = SINGLE;

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

public slots:
};

#endif // VISIONPOINT_H

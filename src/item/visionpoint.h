/****************************************************************************
** @brief       基于VisionItem类封装的自定义point类
** @note
** @author      xiaodongLi
** @date        create:2018-09-28
** @example
****************************************************************************/


#ifndef VISIONPOINT_H
#define VISIONPOINT_H

#include <QObject>
#include <QPainter>
#include "../control/visionitem.h"

class VisionPoint : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionPoint(VisionItem *parent = 0);

    void setPointF(QPointF pointF);

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

signals:

private:
    QPointF m_pointF;

public slots:
};

#endif // VISIONPOINT_H

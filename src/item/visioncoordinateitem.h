#ifndef VISIONCOORDINATEITEM_H
#define VISIONCOORDINATEITEM_H

#include <QObject>
#include "../control/visionitem.h"

class VisionCoordinateItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit VisionCoordinateItem(bool bEdit = false,QColor color = QColor(255,0,0),QGraphicsItem *parent = 0);

    void setPointF(QPointF pointF)
    {
        m_pointF = pointF;
    }

    void setArrowLength(int iLength = 10)
    {
        m_iLength = iLength;
    }

    void setColor(QColor color)
    {
        m_borderColor = color;
    }

    QPointF getP(){
        return m_pointF;
    }

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

signals:
    void signalChanged(VisionItem* item);

private:
    QPointF m_pointF;
    int m_iLength = 10;

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;


};

#endif // VISIONCOORDINATEITEM_H

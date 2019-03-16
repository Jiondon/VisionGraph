#ifndef VISIONCOORDINATEITEM_H
#define VISIONCOORDINATEITEM_H

#include <QObject>
#include "../control/visionitem.h"

#include <QPainter>

class VisionCoordinateItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit VisionCoordinateItem(bool bEdit = false, bool color_enable = false, QColor color = QColor(255,0,0), QGraphicsItem *parent = 0);

    void setPointF(QPointF pointF)
    {
        this->setPos(pointF);
        m_pointF = pointF;
    }

    void setCoordinateLength(int iLength = 50)
    {
        m_iLength = iLength;
    }

    void setAngle(qreal angle){
        m_angle = angle;
//        this->setRotation(angle);
    }

    void setColor(QColor color)
    {
        m_borderColor = color;
    }

    QPointF getP(){
        return m_pointF;
    }

    VGCoordinateSystem2D getData(){
        VGCoordinateSystem2D vgCoordinate;
        vgCoordinate.optional = VG_ENABLE;
        VGPoint2D vgPoint;
        vgPoint.x = m_pointF.x();
        vgPoint.y = m_pointF.y();
        vgCoordinate.origin = vgPoint;
        vgCoordinate.angle = m_angle;
        vgCoordinate.scale = 1;  //缩放系数，默认缩放系数就是所要显示的一个单位，待定
        return vgCoordinate;
    }

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

signals:
    void signalChanged(VisionItem* item);

private:
    QPointF m_pointF;
    int m_iLength = 50;
    qreal m_angle = 0;  //旋转角度--坐标系

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;


};

#endif // VISIONCOORDINATEITEM_H

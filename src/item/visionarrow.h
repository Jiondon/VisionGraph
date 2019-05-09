#ifndef VISIONARROW_H
#define VISIONARROW_H

#include <QObject>
#include <QPainter>

#include "../control/visionitem.h"

class VISIONGRAPHSHARED_EXPORT VisionArrow : public QObject , public VisionItem
{
    Q_OBJECT
public:
    explicit VisionArrow(bool bEdit = false, bool color_enable = false,
                         QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160)
            , QObject *parent = 0);

    void setPointF(QPointF pointF);
    void setArrowLength(int iLength = 10);
    void setColor(QColor color);

    QPointF getP(){
        return m_pointF;
    }

    QVector<QPointF> getPoints();

    /**
     * @brief       判断点（x,y）是否在该item内
     * @param       bool
     */
    bool getPosInArea(qreal x,qreal y){
        return true;
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


public slots:
};

#endif // VISIONARROW_H

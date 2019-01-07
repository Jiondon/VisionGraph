#ifndef VISIONARROW_H
#define VISIONARROW_H

#include <QObject>
#include <QPainter>

#include "../control/visionitem.h"

class VISIONGRAPHSHARED_EXPORT VisionArrow : public QObject , public VisionItem
{
    Q_OBJECT
public:
    explicit VisionArrow(QObject *parent = 0);

    void setPointF(QPointF pointF);
    void setArrowLength(int iLength = 10);
    void setColor(QColor color);

    QPointF getP(){
        return m_pointF;
    }

    QVector<QPointF> getPoints();

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

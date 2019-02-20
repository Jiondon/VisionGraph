#ifndef VISIONLINE_H
#define VISIONLINE_H

#include <QObject>
#include <QPainter>
#include "../control/visionitem.h"

enum Style{
    SINGLE,
    MULTI
};

class VISIONGRAPHSHARED_EXPORT VisionLine : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionLine(VisionItem *parent = 0);

    void setLine(QLineF lineF);
    void setLines(QList<QLineF> lstLineF);


    /**
     * @brief       获取每个顶点
     * @param       point vec
     */
    QVector<QPointF> getPoints();

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;


signals:
    void signalChanged(VisionItem* item);

private:
    QLineF m_lineF;
    QList<QLineF> m_lstLineF;

    Style m_style = SINGLE;

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

public slots:
};

#endif // VISIONLINE_H

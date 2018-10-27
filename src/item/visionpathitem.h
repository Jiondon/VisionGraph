/****************************************************************************
** @brief       自定义path类
** @note        给定一个path，直接绘制
** @author      xiaodongLi
** @date        create:2018-09-28
** @example
** @note        还未进行具体进行封装 -- todo
****************************************************************************/


#ifndef VISIONPATHITEM_H
#define VISIONPATHITEM_H

#include <QObject>
#include <QColor>

class VisionPathItem : public QObject
{
    Q_OBJECT
public:
    explicit VisionPathItem(QObject *parent = 0);

    //设置绘制的半径
    void setCircleR(qreal r);

    //设置画笔颜色
    void setPenColor(QColor color);

    //设置填充的颜色
    void setBrushColor(QColor color);


signals:

private:
    QColor m_penColor = QColor(255,0,0);
    QColor m_brushColor = QColor(255,0,0);
    qreal m_circleR = 1;


public slots:
};

#endif // VISIONPATHITEM_H

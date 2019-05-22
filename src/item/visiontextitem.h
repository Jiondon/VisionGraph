/****************************************************************************
** @brief       文本控件
** @note        显示文本，专用于OCR类型的读取文本显示控件，目前仅用于读取图片上的文字，并进行显示
** @author      xiaodongLi
** @date        create:2019-04-28
** @example
****************************************************************************/

#ifndef VISIONTEXTITEM_H
#define VISIONTEXTITEM_H

#include "../control/visionitem.h"
#include "../control/color.h"

#include <QPainter>

class VISIONGRAPHSHARED_EXPORT VisionTextItem : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionTextItem(VisionItem *parent = 0);

    /**
     * @brief       设置文本区域的背景色
     */
    void setBackgroundColor(QColor bgColor)
    {
        m_bgColor = bgColor;
    }

    /**
     * @brief       设置文本的颜色
     */
    void setRegionColor(QColor color)
    {
        m_color = color;
    }

    /**
     * @brief       设置文本区域的背景色
     */
    void setBackgroundColor_text(QColor bgColor)
    {
        m_bgColor_text = bgColor;
    }

    /**
     * @brief       设置文本的颜色
     */
    void setTextColor(QColor color)
    {
        m_color_text = color;
    }


    /**
     * @brief       设置数据
     */
    void setData(VGRegion vgRegion,QString textName="?");

    void setRegion(VGRegion vgRegion,QColor color = QColor(Qt::black))
    {
        m_vgRegion = vgRegion;
        m_color = color;
    }

    VGRegion getRegion(){
        return m_vgRegion;
    }

    void setTextName(QString textName,QColor color = QColor(Qt::red))
    {
        m_strText = textName;
        m_color_text = color;
    }

    QString getTextName(){
        return m_strText;
    }

    bool getPosInArea(qreal x, qreal y){
        return true;
    }

    QVector<QPointF> getPoints(){
        QVector<QPointF> vec_point;
        return vec_point;
    }


    void setTextWidth_Height(qreal w,qreal h){
        m_textHeight = h;
        m_textWidth = w;
    }

    void setTextPiexl(qreal piexl){
        m_textPiexl = piexl;
    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    QRectF boundingRect() const;

signals:
    void signal_RightClicked(VisionItem *item);
    void signal_DoubleClicked(VisionItem *item);

    void signalChanged(VisionItem *item);
private:
    QColor m_bgColor = QColor(Qt::transparent);
    QColor m_color = QColor(Qt::black);

    QColor m_bgColor_text = QColor(Qt::transparent);
    QColor m_color_text = QColor(Qt::red);

    VGRegion m_vgRegion;  //文本的区域
    QString m_strText;  //显示的字的文本

    QVector<QLineF> m_vecLines;

    QRectF m_regionRf = QRectF(0,0,0,0);

    qreal m_textPiexl = 18;
    qreal m_textWidth = 30;  //此数值跟随字体变化
    qreal m_textHeight = 30;  //此数值需要建议跟随region变化

    bool m_bEnter = false;

public slots:
};

#endif // VISIONTEXTITEM_H

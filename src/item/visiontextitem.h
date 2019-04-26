#ifndef VISIONTEXTITEM_H
#define VISIONTEXTITEM_H

#include "../control/visionitem.h"
#include "../control/color.h"

class VisionTextItem : public VisionItem
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
    void setData(VGRegion vgRegion,QString textName);

    void setRegion(VGRegion vgRegion,QColor color = QColor(Qt::black))
    {
        m_vgRegion = vgRegion;
        m_color = color;
    }

    void setTextName(QString textName,QColor color = QColor(Qt::red))
    {
        m_strText = textName;
        m_color_text = color;
    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QRectF boundingRect() const;

signals:
    void signal_RightClicked();
    void signal_DoubleClicked();

private:
    QColor m_bgColor = QColor(Qt::transparent);
    QColor m_color = QColor(Qt::black);

    QColor m_bgColor_text = QColor(Qt::transparent);
    QColor m_color_text = QColor(Qt::red);

    VGRegion m_vgRegion;  //文本的区域
    QString m_strText;  //显示的字的文本

public slots:
};

#endif // VISIONTEXTITEM_H

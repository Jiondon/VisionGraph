#ifndef VISIONGRAPHSCENE_H
#define VISIONGRAPHSCENE_H

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
/**
 * @brief       自定义图形Scene控件
 * @note        除了捕捉鼠标位置，更多的是考虑扩展使用
 * @author      kuainq
 * @date        create:2017-11-13
 */
class VisionGraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    VisionGraphScene(QObject *parent =0);

    void setGrid_Visible(bool bVisible);  //网格背景是否显示
    void setGrid_Size(const QSize &size);
    void setGrid_Color(const QColor &color);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

//    void drawBackground(QPainter *painter, const QRectF &rect);
signals:
    /**
     * @brief       当鼠标移动时候触发该信号
     * @param       x 鼠标当前x位置
     * @param       y 鼠标当前y位置
     * @note        不可以在View中做捕捉鼠标事件，具体啥原因，自己想
     */
    void signal_MouseMove(qreal x,qreal y);

    void signal_MousePress(qreal x,qreal y);

private:
    bool m_bGrddingVisible = false;
    QSizeF m_GraddingSize = QSizeF(20,20);
    QColor m_GraddingColor = QColor(Qt::lightGray);

private:
    void updateGridding();
};

#endif // VISIONGRAPHSCENE_H

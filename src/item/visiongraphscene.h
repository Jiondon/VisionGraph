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

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    /**
     * @brief       当鼠标移动时候触发该信号
     * @param       x 鼠标当前x位置
     * @param       y 鼠标当前y位置
     * @note        不可以在View中做捕捉鼠标事件，具体啥原因，自己想
     */
    void signal_MouseMove(qreal x,qreal y);

    void signal_MousePress(qreal x,qreal y);
};

#endif // VISIONGRAPHSCENE_H

#ifndef VISIONGRAPHWIDGET_H
#define VISIONGRAPHWIDGET_H

#include <QObject>
#include <QWidget>
#include <QResizeEvent>

class VisionGraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VisionGraphWidget(QWidget *parent = 0);

    void resizeEvent(QResizeEvent *event);

signals:
    void signal_sizeChanged(qreal w,qreal h);

public slots:
};

#endif // VISIONGRAPHWIDGET_H

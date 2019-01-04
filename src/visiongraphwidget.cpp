#include "visiongraphwidget.h"
#include <QDebug>

VisionGraphWidget::VisionGraphWidget(QWidget *parent) : QWidget(parent)
{
}

void VisionGraphWidget::resizeEvent(QResizeEvent *event)
{
    emit signal_sizeChanged(event->size().width(),event->size().height());
}

#include "visionpathitem.h"

VisionPathItem::VisionPathItem(QObject *parent) : QObject(parent)
{

}

void VisionPathItem::setCircleR(qreal r)
{
    m_circleR = r;
}

void VisionPathItem::setPenColor(QColor color)
{
    m_penColor = color;
}

void VisionPathItem::setBrushColor(QColor color)
{
    m_brushColor = color;
}

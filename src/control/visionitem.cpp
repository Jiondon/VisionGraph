﻿#include "visionitem.h"
#include <QDebug>
//#include "../visiongraphview.h"

VisionItem::VisionItem(QGraphicsItem *parent):QGraphicsItem(parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

void VisionItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"visionItem mousePressEvent";
    if(!m_bEdit)
        return;

    setSelectedStatus(true);
}


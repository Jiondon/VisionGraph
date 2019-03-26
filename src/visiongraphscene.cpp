#include "visiongraphscene.h"
#include "qdebug.h"

VisionGraphScene::VisionGraphScene(QObject *parent):
    QGraphicsScene(parent)
{
    if(m_bGrddingVisible){
        updateGridding();
    }
}

void VisionGraphScene::setGrid_Visible(bool bVisible)
{
    m_bGrddingVisible = bVisible;
    if(m_bGrddingVisible){
        updateGridding();
    }else{
        //clear scene backgroud  未实现
    }
}

void VisionGraphScene::setGrid_Size(const QSize &size)
{
    m_GraddingSize  = size;
    if(m_bGrddingVisible){
        updateGridding();
    }
}

void VisionGraphScene::setGrid_Color(const QColor &color)
{
    m_GraddingColor = color;
    if(m_bGrddingVisible){
        updateGridding();
    }
}

void VisionGraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signal_MouseMove(event->scenePos().x(),event->scenePos().y());
    QGraphicsScene::mouseMoveEvent(event);
}

void VisionGraphScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signal_MousePress(event->scenePos().x(),event->scenePos().y());
    QGraphicsScene::mousePressEvent(event);

}


//void VisionGraphScene::drawBackground(QPainter *painter, const QRectF &rect)
//{
////    qDebug()<<"scene drawBackground "<<rect<<this->views().at(0)->rect()<<this->sceneRect()<<this->views().at(0)->sceneRect();

//    QRectF rf = rect;
//    if(this->views().at(0)->matrix().m11() < 1){
//        //此处会导致painter绘制rect的时候出现区域限制
//        painter->scale(1/this->views().at(0)->matrix().m11(),1/this->views().at(0)->matrix().m11());
////        rf.setWidth(rect.width()*(1/this->views().at(0)->matrix().m11()));
////        rf.setHeight(rect.height()*1/this->views().at(0)->matrix().m11());
//    }else{
//    }
//    QGraphicsScene::drawBackground(painter,rect);

////    QGraphicsScene::drawBackground(painter,rect);
//}

void VisionGraphScene::updateGridding()
{

//    QPolygonF myPolygon1;
//    myPolygon1 << QPointF(0,m_GraddingSize.height()/2) << QPointF(m_GraddingSize.width(),m_GraddingSize.height()/2);
//    QPolygonF myPolygon2;
//    myPolygon2 << QPointF(m_GraddingSize.width()/2,0) << QPointF(m_GraddingSize.width()/2,m_GraddingSize.height());
//    QPixmap pixmap(m_GraddingSize.toSize());
////    QPolygonF myPolygon1;
////    myPolygon1 << QPointF(0,10) << QPointF(20,10);
////    QPolygonF myPolygon2;
////    myPolygon2 << QPointF(10,0) << QPointF(10,20);

////    QPixmap pixmap(":/icon/drag.png");
////    QPixmap pixmap(20,20);
//    pixmap.fill(Qt::transparent);
//    QPainter painter(&pixmap);

//    QVector<qreal> dashes;//line style--虚线
//    qreal space = 5;
//    dashes << 5 << space << 5 <<space;
//    QPen pen(m_GraddingColor);
//    pen.setDashPattern(dashes);
//    pen.setWidth(0);


//    painter.setPen(pen);
//    painter.translate(0, 0);
//    painter.drawPolyline(myPolygon1);
//    painter.drawPolyline(myPolygon2);
//    this->setBackgroundBrush(pixmap);
}


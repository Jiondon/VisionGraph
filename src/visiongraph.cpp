﻿#include "visiongraph.h"
#include <QDebug>


VisionGraph::VisionGraph(GraphType type, ToolButtonDirection toolButtonDirect, QWidget *parent) : QWidget(parent)
{
    if(toolButtonDirect == ToolButtonDirection::leftDirection || toolButtonDirect == ToolButtonDirection::rightDirection){
        setMinimumSize(450,650);
    }else{
        setMinimumSize(650,450);
    }
    QVBoxLayout *mainLayout = new QVBoxLayout;
    if(type == GraphType::graphRegion){
        m_graphWidget_Region = new VisionGraph_Region(toolButtonDirect);
        mainLayout->addWidget(m_graphWidget_Region);

    }else if(type == GraphType::graphItem_self){
        m_graphWidget_Item = new VisionGraph_Item(ItemModel::self,toolButtonDirect);
        mainLayout->addWidget(m_graphWidget_Item);
        m_graphWidget_Item->setViewRegion_Visible(false);
        brushColor = Qt::transparent;

    }else if(type == GraphType::graphItem_unSelf){
        m_graphWidget_Item = new VisionGraph_Item(ItemModel::un_self,toolButtonDirect);
        mainLayout->addWidget(m_graphWidget_Item);
        m_graphWidget_Item->setViewRegion_Visible(false);
        brushColor = Qt::transparent;

    }else{
        qDebug()<<"VisionGraph is Error";
    }
    m_type = type;
//    setStyleSheet(QString::fromUtf8("border:1px solid red"));
    this->setLayout(mainLayout);
}



void VisionGraph::setSceneWidgetSize(QSize size)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setSceneWidgetSize(size);

    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setSceneWidgetSize(size);

    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setSceneWidgetSize(size);

    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setSceneWidgetSize(qreal w, qreal h)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setSceneWidgetSize(w,h);

    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setSceneWidgetSize(w,h);

    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setSceneWidgetSize(w,h);

    }else{
        qDebug()<<"VisionGraph is Error";
    }
}


VisionRectItem* VisionGraph::addRect(QRectF rf, bool bEdit, QColor color)
{
    if(m_type == GraphType::graphRegion){
        return m_graphWidget_Region->addRect(rf, bEdit);

    }else if(m_type == GraphType::graphItem_self){
        return m_graphWidget_Item->addRect(rf, bEdit);

    }else if(m_type == GraphType::graphItem_unSelf){
        return m_graphWidget_Item->addRect(rf, bEdit);

    }else{
        qDebug()<<"VisionGraph is Error";
        return NULL;
    }
}

QGraphicsRectItem *VisionGraph::_addRect(const QRectF &rect, const QPen &pen, const QBrush &brush)
{
    if(m_type == GraphType::graphRegion){
        return m_graphWidget_Region->_addRect(rect,pen,brush);

    }else if(m_type == GraphType::graphItem_self){
        return m_graphWidget_Item->_addRect(rect,pen,brush);

    }else if(m_type == GraphType::graphItem_unSelf){
        return m_graphWidget_Item->_addRect(rect,pen,brush);

    }else{
        qDebug()<<"VisionGraph is Error";
        return NULL;
    }
}

QGraphicsPolygonItem *VisionGraph::_addPolygon(const QPolygonF &polygon, const QPen &pen, const QBrush &brush)
{
    if(m_type == GraphType::graphRegion){
        return m_graphWidget_Region->_addPolygon(polygon,pen,brush);

    }else if(m_type == GraphType::graphItem_self){
        return m_graphWidget_Item->_addPolygon(polygon,pen,brush);

    }else if(m_type == GraphType::graphItem_unSelf){
        return m_graphWidget_Item->_addPolygon(polygon,pen,brush);

    }else{
        qDebug()<<"VisionGraph is Error";
        return NULL;
    }
}

QGraphicsLineItem *VisionGraph::_addLine(const QLineF &line, const QPen &pen)
{
    if(m_type == GraphType::graphRegion){
        return m_graphWidget_Region->_addLine(line,pen);

    }else if(m_type == GraphType::graphItem_self){
        return m_graphWidget_Item->_addLine(line,pen);

    }else if(m_type == GraphType::graphItem_unSelf){
        return m_graphWidget_Item->_addLine(line,pen);

    }else{
        qDebug()<<"VisionGraph is Error";
        return NULL;
    }
}

QGraphicsEllipseItem *VisionGraph::_addEllipse(const QRectF &rect, const QPen &pen, const QBrush &brush)
{
    if(m_type == GraphType::graphRegion){
        return m_graphWidget_Region->_addEllipse(rect,pen,brush);

    }else if(m_type == GraphType::graphItem_self){
        return m_graphWidget_Item->_addEllipse(rect,pen,brush);

    }else if(m_type == GraphType::graphItem_unSelf){
        return m_graphWidget_Item->_addEllipse(rect,pen,brush);

    }else{
        qDebug()<<"VisionGraph is Error";
        return NULL;
    }
}

VisionCrossPointItem *VisionGraph::_addPoint(QPointF pointF, QColor color)
{
    if(m_type == GraphType::graphRegion){
        return m_graphWidget_Region->_addPoint(pointF);

    }else if(m_type == GraphType::graphItem_self){
        return m_graphWidget_Item->_addPoint(pointF);

    }else if(m_type == GraphType::graphItem_unSelf){
        return m_graphWidget_Item->_addPoint(pointF);

    }else{
        qDebug()<<"VisionGraph is Error";
        return NULL;
    }
}

VisionArrow *VisionGraph::_addArrow(QPointF pointF, QColor color)
{
    if(m_type == GraphType::graphRegion){
        return m_graphWidget_Region->_addArrow(pointF,color);

    }else if(m_type == GraphType::graphItem_self){
        return m_graphWidget_Item->_addArrow(pointF,color);

    }else if(m_type == GraphType::graphItem_unSelf){
        return m_graphWidget_Item->_addArrow(pointF,color);

    }else{
        qDebug()<<"VisionGraph is Error";
        return NULL;
    }
}

VisionChainItem *VisionGraph::_addChain(QList<QPointF> lstP, QColor color)
{
    if(m_type == GraphType::graphRegion){
        return m_graphWidget_Region->_addChain(lstP);

    }else if(m_type == GraphType::graphItem_self){
        return m_graphWidget_Item->_addChain(lstP);

    }else if(m_type == GraphType::graphItem_unSelf){
        return m_graphWidget_Item->_addChain(lstP);

    }else{
        qDebug()<<"VisionGraph is Error";
        return NULL;
    }
}

VisionEllipseItem* VisionGraph::addEllipse(QRectF rf, bool bEdit, QColor color)
{
    if(m_type == GraphType::graphRegion){
        return m_graphWidget_Region->addEllipse(rf);

    }else if(m_type == GraphType::graphItem_self){
        return m_graphWidget_Item->addEllipse(rf);

    }else if(m_type == GraphType::graphItem_unSelf){
        return m_graphWidget_Item->addEllipse(rf);

    }else{
        qDebug()<<"VisionGraph is Error";
        return NULL;
    }
}

VisionLineItem *VisionGraph::addLine(QLine line, QColor color)
{
    if(m_type == GraphType::graphRegion){
        return m_graphWidget_Region->addLine(line);
    }else if(m_type == GraphType::graphItem_self){
        return m_graphWidget_Item->addLine(line);

    }else if(m_type == GraphType::graphItem_unSelf){
        return m_graphWidget_Item->addLine(line);

    }else{
        qDebug()<<"VisionGraph is Error";
        return NULL;
    }
}

void VisionGraph::addLines(QList<QLine> lstLine, QColor color)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->addLines(lstLine);

    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->addLines(lstLine);

    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->addLines(lstLine);

    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

VisionPolygon *VisionGraph::addPolygon(QVector<QPointF> vecPointF, QColor color)
{
    if(m_type == GraphType::graphRegion){
        return m_graphWidget_Region->addPolygon(vecPointF);

    }else if(m_type == GraphType::graphItem_self){
        return m_graphWidget_Item->addPolygon(vecPointF);

    }else if(m_type == GraphType::graphItem_unSelf){
        return m_graphWidget_Item->addPolygon(vecPointF);

    }else{
        qDebug()<<"VisionGraph is Error";
        return NULL;
    }
}

VisionCrossPointItem *VisionGraph::addPoint(QPointF pointF, QColor color)
{
    if(m_type == GraphType::graphRegion){
        return m_graphWidget_Region->addPoint(pointF);

    }else if(m_type == GraphType::graphItem_self){
        return m_graphWidget_Item->addPoint(pointF);

    }else if(m_type == GraphType::graphItem_unSelf){
        return m_graphWidget_Item->addPoint(pointF);

    }else{
        qDebug()<<"VisionGraph is Error";
        return NULL;
    }
}

XVRegion* VisionGraph::getRegion()
{
//    XVRegion xvRegin;
    if(m_graphWidget_Region == nullptr)
        return NULL;
    return m_graphWidget_Region->getRegion();
}

void VisionGraph::setBkImg(QImage image)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setBkImg(image);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setBkImg(image);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setBkImg(image);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setToolButton_Direction(ToolButtonDirection direct)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setToolButton_Direction(direct);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setToolButton_Direction(direct);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setToolButton_Direction(direct);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setSelectedColor(QColor color)
{
    selectedColor = color;
}

void VisionGraph::setBorderColor(QColor color)
{
    borderColor = color;
}

void VisionGraph::setBrushColor(QColor color)
{
    brushColor = color;
}

void VisionGraph::setRegionColor(QColor color)
{
    regionColor = color;
}


void VisionGraph::show()
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->show();
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->show();
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->show();
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

VisionGraphView *VisionGraph::getView()
{
    VisionGraphView* view = NULL;
    if(m_type == GraphType::graphRegion){
        view = m_graphWidget_Region->getView();
    }else if(m_type == GraphType::graphItem_self){
        view = m_graphWidget_Item->getView();
    }else if(m_type == GraphType::graphItem_unSelf){
        view = m_graphWidget_Item->getView();
    }
    return view;
}

void VisionGraph::setPainterCursorR(qreal qR){
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setPainterCursorR(qR);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setPainterCursorR(qR);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setPainterCursorR(qR);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setItemType(ItemType type){
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setItemType(type);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setItemType(type);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setItemType(type);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::zoom(float scaleFactor){
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->zoom(scaleFactor);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->zoom(scaleFactor);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->zoom(scaleFactor);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::back_region(){
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->back_region();
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->back_region();
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->back_region();
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::front_region(){
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->front_region();
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->front_region();
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->front_region();
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::clearPainter(){
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->clearPainter();
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->clearPainter();
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->clearPainter();
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setViewInfo_Visible(bool bVisible)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setViewInfo_Visible(bVisible);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setViewInfo_Visible(bVisible);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setViewInfo_Visible(bVisible);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setViewInfo_Pos(Corner corner){
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setViewInfo_Pos(corner);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setViewInfo_Pos(corner);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setViewInfo_Pos(corner);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setViewInfo_Pos(qreal x, qreal y){
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setViewInfo_Pos(x,y);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setViewInfo_Pos(x,y);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setViewInfo_Pos(x,y);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setViewInfo_Size(QSize size){
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setViewInfo_Size(size);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setViewInfo_Size(size);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setViewInfo_Size(size);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setViewInfo_Size(qreal w, qreal h){
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setViewInfo_Size(w,h);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setViewInfo_Size(w,h);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setViewInfo_Size(w,h);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setViewInfo_text(QString text){
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setViewInfo_text(text);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setViewInfo_text(text);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setViewInfo_text(text);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setViewInfo_Color(QColor backgroundColor,QColor textColor){
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setViewInfo_Color(backgroundColor,textColor);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setViewInfo_Color(backgroundColor,textColor);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setViewInfo_Color(backgroundColor,textColor);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setIconPath(QString iconpath)
{
    iconPath = iconpath;
}

QToolButton *VisionGraph::getToolButton(ToolButtonType type)
{
    if(m_type == GraphType::graphRegion){
        return m_graphWidget_Region->getToolButton(type);
    }else if(m_type == GraphType::graphItem_self){
        return m_graphWidget_Item->getToolButton(type);
    }else if(m_type == GraphType::graphItem_unSelf){
        return m_graphWidget_Item->getToolButton(type);
    }else{
        qDebug()<<"VisionGraph is Error";
        return NULL;
    }
}

bool VisionGraph::removeToolButton(ToolButtonType type)
{
    if(m_type == GraphType::graphRegion){
        return m_graphWidget_Region->removeToolButton(type);
    }else if(m_type == GraphType::graphItem_self){
        return m_graphWidget_Item->removeToolButton(type);
    }else if(m_type == GraphType::graphItem_unSelf){
        return m_graphWidget_Item->removeToolButton(type);
    }else{
        qDebug()<<"VisionGraph is Error";
        return NULL;
    }
}

void VisionGraph::addToolButton(QToolButton *btn)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->addToolButton(btn);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->addToolButton(btn);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->addToolButton(btn);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::removeToolBarInfoWidget()
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->removeToolBarInfoWidget();
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->removeToolBarInfoWidget();
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->removeToolBarInfoWidget();
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::addToolFrame()
{

}

void VisionGraph::setViewRegion_Size(qreal w, qreal h)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setViewRegion_Size(w,h);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setViewRegion_Size(w,h);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setViewRegion_Size(w,h);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setViewRegion_Visible(bool bVisible)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setViewRegion_Visible(bVisible);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setViewRegion_Visible(bVisible);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setViewRegion_Visible(bVisible);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setViewRegion_Color(const QColor &color)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setViewRegion_Color(color);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setViewRegion_Color(color);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setViewRegion_Color(color);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}


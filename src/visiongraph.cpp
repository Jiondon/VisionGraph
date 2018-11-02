#include "visiongraph.h"
#include <QDebug>


VisionGraph::VisionGraph(GraphType type, QWidget *parent) : QWidget(parent)
{
    setFixedSize(1200,800);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    if(type == GraphType::graphRegion){
        m_graphWidget_Region = new VisionGraph_Region(this);
        mainLayout->addWidget(m_graphWidget_Region);

    }else if(type == GraphType::graphItem_self){
        m_graphWidget_Item = new VisionGraph_Item(ItemModel::self,this);
        mainLayout->addWidget(m_graphWidget_Item);

    }else if(type == GraphType::graphItem_unSelf){
        m_graphWidget_Item = new VisionGraph_Item(ItemModel::un_self,this);
        mainLayout->addWidget(m_graphWidget_Item);

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


void VisionGraph::addRect(QRectF rf, bool bEdit)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->addRect(rf, bEdit);

    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->addRect(rf, bEdit);

    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->addRect(rf, bEdit);

    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::addEllipse(QRectF rf)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->addEllipse(rf);

    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->addEllipse(rf);

    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->addEllipse(rf);

    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::addLine(QLine line)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->addLine(line);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->addLine(line);

    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->addLine(line);

    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::addLines(QList<QLine> lstLine)
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

void VisionGraph::addPolygon(QVector<QPointF> vecPointF)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->addPolygon(vecPointF);

    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->addPolygon(vecPointF);

    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->addPolygon(vecPointF);

    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::addPoint(QPointF pointF)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->addPoint(pointF);

    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->addPoint( pointF);

    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->addPoint(pointF);

    }else{
        qDebug()<<"VisionGraph is Error";
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

void VisionGraph::setToolButton_Painter(ToolButtonDirection direct)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setToolButton_Painter(direct);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setToolButton_Painter(direct);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setToolButton_Painter(direct);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setToolButton_Operation(ToolButtonDirection direct)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setToolButton_Operation(direct);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setToolButton_Operation(direct);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setToolButton_Operation(direct);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::initLayout()
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->initLayout();
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->initLayout();
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->initLayout();
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


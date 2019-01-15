#include "visiongraph.h"
#include <QDebug>


VisionGraph::VisionGraph(GraphType type, ToolButtonDirection toolButtonDirect, QWidget *parent) : QWidget(parent)
{
    if(toolButtonDirect == ToolButtonDirection::leftDirection || toolButtonDirect == ToolButtonDirection::rightDirection){
        setMinimumSize(450,650);
    }else{
        setMinimumSize(650,450);
    }
    g_graphType = type;

    QVBoxLayout *mainLayout = new QVBoxLayout;

    m_graphWidget_Base = new VisionGraph_(g_graphType,toolButtonDirect);

    if(type == GraphType::graphRegion){
//        m_graphWidget_Base = new VisionGraph_Region(toolButtonDirect);
    }else if(type == GraphType::graphItem_self){
//        m_graphWidget_Base = new VisionGraph_Item(GraphType::self,toolButtonDirect);
        brushColor = Qt::transparent;
    }else if(type == GraphType::graphItem_unSelf){
//        m_graphWidget_Base = new VisionGraph_Item(ItemModel::un_self,toolButtonDirect);
        brushColor = Qt::transparent;
    }else if(type == GraphType::graphRegion){
        brushColor = Qt::transparent;
    }else{
        qDebug()<<"VisionGraph is Error";
    }
    mainLayout->addWidget(m_graphWidget_Base);
    m_graphWidget_Base->layout()->setMargin(0);
    connect(m_graphWidget_Base,SIGNAL(signal_itemFinished(VisionItem*)),this,SIGNAL(signal_PaintFinishedChanged(VisionItem*)));

    this->setLayout(mainLayout);
}



void VisionGraph::setSceneWidgetSize(QSize size)
{
    m_graphWidget_Base->setSceneWidgetSize(size);
}

void VisionGraph::setSceneWidgetSize(qreal w, qreal h)
{
    m_graphWidget_Base->setSceneWidgetSize(w,h);
}


VisionRectItem* VisionGraph::addRect(QRectF rf, bool bEdit,bool bRotation, QColor color)
{
    return m_graphWidget_Base->addRect(rf,bEdit,bRotation);
}

QGraphicsRectItem *VisionGraph::_addRect(const QRectF &rect, const QPen &pen, const QBrush &brush)
{
    return m_graphWidget_Base->_addRect(rect,pen,brush);
}

QGraphicsPolygonItem *VisionGraph::_addPolygon(const QPolygonF &polygon, const QPen &pen, const QBrush &brush)
{
    return m_graphWidget_Base->_addPolygon(polygon,pen,brush);
}

QGraphicsLineItem *VisionGraph::_addLine(const QLineF &line, const QPen &pen)
{
    return m_graphWidget_Base->_addLine(line,pen);
}

QGraphicsEllipseItem *VisionGraph::_addEllipse(const QRectF &rect, const QPen &pen, const QBrush &brush)
{
    return m_graphWidget_Base->_addEllipse(rect,pen,brush);
}

VisionCrossPointItem *VisionGraph::_addPoint(QPointF pointF, QColor color)
{
    return m_graphWidget_Base->_addPoint(pointF);
}

VisionArrow *VisionGraph::_addArrow(QPointF pointF,bool bEdit, QColor color)
{
    return m_graphWidget_Base->_addArrow(pointF,bEdit,color);
}

VisionChainItem *VisionGraph::_addChain(QList<QPointF> lstP, QColor color)
{
    return m_graphWidget_Base->_addChain(lstP);
}

VisionEllipseItem* VisionGraph::addEllipse(QRectF rf, bool bEdit, bool bRotation, QColor color)
{
    return m_graphWidget_Base->addEllipse(rf,bEdit,bRotation);
}

VisionLineItem *VisionGraph::addLine(QLine line,bool bEdit, QColor color)
{
    return m_graphWidget_Base->addLine(line,bEdit,color);
}

void VisionGraph::addLines(QList<QLine> lstLine, QColor color)
{
    m_graphWidget_Base->addLines(lstLine);
}

VisionPolygon *VisionGraph::addPolygon(QVector<QPointF> vecPointF,bool bClose, bool bEdit, QColor color)
{
    return m_graphWidget_Base->addPolygon(vecPointF,bClose,bEdit,color);
}

VisionCrossPointItem *VisionGraph::addPoint(QPointF pointF,bool bEdit, QColor color)
{
    return m_graphWidget_Base->addPoint(pointF,bEdit);
}

VisionChainItem *VisionGraph::addChain(QList<QPointF> lstP, bool close,bool edit, QColor color)
{
    return m_graphWidget_Base->addChain(lstP,close,edit,color);
}

XVRegion* VisionGraph::getRegion()
{
//    XVRegion xvRegin;
    if(m_graphWidget_Base == nullptr)
        return NULL;
    return m_graphWidget_Base->getRegion();
}

QList<VisionItem *> VisionGraph::getItems()
{
    QList<VisionItem *> lstItem;
    lstItem.clear();

        lstItem = m_graphWidget_Base->getItems();

    return lstItem;
}

void VisionGraph::setBkImg(QImage image)
{
    m_graphWidget_Base->setBkImg(image);
}

void VisionGraph::setToolButton_Direction(ToolButtonDirection direct)
{
    m_graphWidget_Base->setToolButton_Direction(direct);
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
    m_graphWidget_Base->show();
}

VisionGraphView *VisionGraph::getView()
{
    VisionGraphView* view = NULL;
    view = m_graphWidget_Base->getView();
    return view;
}

void VisionGraph::setPainterCursorR(qreal qR)
{
    m_graphWidget_Base->setPainterCursorR(qR);
}

void VisionGraph::setItemType(ItemType type)
{
    m_graphWidget_Base->setItemType(type);
}

void VisionGraph::zoom(float scaleFactor)
{
    m_graphWidget_Base->zoom(scaleFactor);
}

void VisionGraph::back_region()
{
    m_graphWidget_Base->back_region();
}

void VisionGraph::front_region()
{
    m_graphWidget_Base->front_region();
}

void VisionGraph::clearPainter()
{
    m_graphWidget_Base->clearPainter();
}

void VisionGraph::setViewInfo_Visible(bool bVisible)
{
    m_graphWidget_Base->setViewInfo_Visible(bVisible);
}

void VisionGraph::setViewInfo_Pos(Corner corner)
{
    m_graphWidget_Base->setViewInfo_Pos(corner);
}

void VisionGraph::setViewInfo_Pos(qreal x, qreal y)
{
    m_graphWidget_Base->setViewInfo_Pos(x,y);
}

void VisionGraph::setViewInfo_Size(QSize size)
{
    m_graphWidget_Base->setViewInfo_Size(size);
}

void VisionGraph::setViewInfo_Size(qreal w, qreal h)
{
    m_graphWidget_Base->setViewInfo_Size(w,h);
}

void VisionGraph::setViewInfo_text(QString text)
{
    m_graphWidget_Base->setViewInfo_text(text);
}

void VisionGraph::setViewInfo_Color(QColor backgroundColor,QColor textColor)
{
    m_graphWidget_Base->setViewInfo_Color(backgroundColor,textColor);
}

void VisionGraph::setIconPath(QString iconpath)
{
    iconPath = iconpath;
}

QToolButton *VisionGraph::getToolButton(ToolButtonType type)
{
    return m_graphWidget_Base->getToolButton(type);
}

bool VisionGraph::removeToolButton(ToolButtonType type)
{
    return m_graphWidget_Base->removeToolButton(type);
}

void VisionGraph::addToolButton(QToolButton *btn)
{
    m_graphWidget_Base->addToolButton(btn);
}

void VisionGraph::removeToolBarInfoWidget()
{
    m_graphWidget_Base->removeToolBarInfoWidget();
}

void VisionGraph::addToolFrame()
{

}

void VisionGraph::setViewRegion_Size(qreal w, qreal h)
{
    m_graphWidget_Base->setViewRegion_Size(w,h);
}

void VisionGraph::setViewRegion_Visible(bool bVisible)
{
    m_graphWidget_Base->setViewRegion_Visible(bVisible);
}

void VisionGraph::setViewRegion_Color(const QColor &color)
{
    m_graphWidget_Base->setViewRegion_Color(color);
}

QImage VisionGraph::getBkgImg()
{
    QImage image;
    image = m_graphWidget_Base->getBkgImg();
    return image;
}

void VisionGraph::saveBkgImg(QString path)
{
    m_graphWidget_Base->saveBkgImg(path);
}

void VisionGraph::removeItem(VisionItem *item)
{
    m_graphWidget_Base->removeItem(item);
}

void VisionGraph::setMousePaintSize(qreal qi)
{
    m_graphWidget_Base->setMousePaintSize(qi);
}

void VisionGraph::setView_Zoom(qreal qZoom)
{
    m_graphWidget_Base->setView_Zoom(qZoom);
}

void VisionGraph::setViewType(ViewType type)
{
    m_graphWidget_Base->setViewType(type);
}

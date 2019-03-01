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

    m_graphWidget = new VisionGraph_(g_graphType,toolButtonDirect);

    if(type == GraphType::graphRegion){
//        m_graphWidget = new VisionGraph_Region(toolButtonDirect);
    }else{
        brushColor = Qt::transparent;
    }
//    qDebug()<<"brush color : "<<brushColor;
    mainLayout->addWidget(m_graphWidget);
    m_graphWidget->layout()->setMargin(0);
    connect(m_graphWidget,SIGNAL(signal_itemFinished(VisionItem*)),this,SIGNAL(signal_PaintFinishedChanged(VisionItem*)));

    this->setLayout(mainLayout);
}



void VisionGraph::setSceneWidgetSize(QSize size)
{
    m_graphWidget->setSceneWidgetSize(size);
}

void VisionGraph::setSceneWidgetSize(qreal w, qreal h)
{
    m_graphWidget->setSceneWidgetSize(w,h);
}

void VisionGraph::setThemeColor(ThemeColor theme)
{
    m_graphWidget->setThemeColor(theme);
}


VisionRectItem* VisionGraph::addRect(QRectF rf, bool bEdit,bool bRotation, QColor color)
{
    return m_graphWidget->addRect(rf,bEdit,bRotation,color);
}

QGraphicsRectItem *VisionGraph::_addRect(const QRectF &rect, const QPen &pen, const QBrush &brush)
{
    return m_graphWidget->_addRect(rect,pen,brush);
}

QGraphicsPolygonItem *VisionGraph::_addPolygon(const QPolygonF &polygon, const QPen &pen, const QBrush &brush)
{
    return m_graphWidget->_addPolygon(polygon,pen,brush);
}

QGraphicsLineItem *VisionGraph::_addLine(const QLineF &line, const QPen &pen)
{
    return m_graphWidget->_addLine(line,pen);
}

QGraphicsEllipseItem *VisionGraph::_addEllipse(const QRectF &rect, const QPen &pen, const QBrush &brush)
{
    return m_graphWidget->_addEllipse(rect,pen,brush);
}

VisionCrossPointItem *VisionGraph::_addPoint(QPointF pointF, bool edit, QColor color)
{
    return m_graphWidget->_addPoint(pointF,edit,color);
}

VisionArrow *VisionGraph::_addArrow(QPointF pointF,bool bEdit, QColor color)
{
    return m_graphWidget->_addArrow(pointF,bEdit,color);
}

VisionChainItem *VisionGraph::_addChain(QList<QPointF> lstP, bool bClosed, bool bEdit, QColor color)
{
    return m_graphWidget->_addChain(lstP,bClosed,bEdit,color);
}

VisionEllipseItem* VisionGraph::addEllipse(QRectF rf, bool bEdit, bool bRotation, QColor color)
{
    return m_graphWidget->addEllipse(rf,bEdit,bRotation,color);
}

VisionArcItem *VisionGraph::addArc(QPointF sP, QPointF mP, QPointF fP, bool bEdit, QColor color)
{
    return m_graphWidget->addArc(sP,mP,fP,bEdit,color);
}

VisionLineItem *VisionGraph::addLine(QLine line,bool bEdit, QColor color)
{
    return m_graphWidget->addLine(line,bEdit,color);
}

VisionLine *VisionGraph::addLines(QList<QLineF> lstLineF, QColor color)
{
    return m_graphWidget->addLines(lstLineF,color);
}

VisionPolygon *VisionGraph::addPolygon(QVector<QPointF> vecPointF,bool bClose, bool bEdit, QColor color)
{
    return m_graphWidget->addPolygon(vecPointF,bClose,bEdit,color);
}

VisionCrossPointItem *VisionGraph::addPoint(QPointF pointF,bool bEdit, QColor color)
{
    return m_graphWidget->addPoint(pointF,bEdit,color);
}

VisionPoint *VisionGraph::addPointFs(QList<QPointF> lstP, QColor color)
{
    return m_graphWidget->addPointFs(lstP,color);
}

VisionChainItem *VisionGraph::addChain(QList<QPointF> lstP, bool close,bool edit, QColor color)
{
    return m_graphWidget->addChain(lstP,close,edit,color);
}

XVRegion* VisionGraph::getRegion()
{
//    XVRegion xvRegin;
    if(m_graphWidget == nullptr)
        return NULL;
    return m_graphWidget->getRegion();
}

QList<VisionItem *> VisionGraph::getItems()
{
    QList<VisionItem *> lstItem;
    lstItem.clear();

        lstItem = m_graphWidget->getItems();

        return lstItem;
}

VisionCoordinateItem *VisionGraph::addCoordinate(QPointF p, qreal angle, qreal length, bool bEdit, QColor color)
{
    return m_graphWidget->addCoordinate(p,angle,length,bEdit,color);
}

void VisionGraph::setBkImg(QImage image)
{
    m_graphWidget->setBkImg(image);
}

void VisionGraph::setToolButton_Direction(ToolButtonDirection direct)
{
    m_graphWidget->setToolButton_Direction(direct);
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
//    regionColor = color;
}


void VisionGraph::show()
{
    m_graphWidget->show();
}

VisionGraphView *VisionGraph::getView()
{
    VisionGraphView* view = NULL;
    view = m_graphWidget->getView();
    return view;
}

void VisionGraph::setPainterCursorR(qreal qR)
{
    m_graphWidget->setPainterCursorR(qR);
}

void VisionGraph::setItemType(ItemType type)
{
    m_graphWidget->setItemType(type);
}

void VisionGraph::zoom(float scaleFactor)
{
    m_graphWidget->zoom(scaleFactor);
}

void VisionGraph::back_region()
{
    m_graphWidget->back_region();
}

void VisionGraph::front_region()
{
    m_graphWidget->front_region();
}

void VisionGraph::clearPainter()
{
    m_graphWidget->clearPainter();
}

void VisionGraph::setViewInfo_Visible(bool bVisible)
{
    m_graphWidget->setViewInfo_Visible(bVisible);
}

void VisionGraph::setViewInfo_Pos(Corner corner)
{
    m_graphWidget->setViewInfo_Pos(corner);
}

void VisionGraph::setViewInfo_Pos(qreal x, qreal y)
{
    m_graphWidget->setViewInfo_Pos(x,y);
}

void VisionGraph::setViewInfo_Size(QSize size)
{
    m_graphWidget->setViewInfo_Size(size);
}

void VisionGraph::setViewInfo_Size(qreal w, qreal h)
{
    m_graphWidget->setViewInfo_Size(w,h);
}

void VisionGraph::setViewInfo_text(QString text)
{
    m_graphWidget->setViewInfo_text(text);
}

void VisionGraph::setViewInfo_Color(QColor backgroundColor,QColor textColor)
{
    m_graphWidget->setViewInfo_Color(backgroundColor,textColor);
}

void VisionGraph::setIconPath(QString iconpath)
{
    iconPath = iconpath;
}

QToolButton *VisionGraph::getToolButton(ToolButtonType type)
{
    return m_graphWidget->getToolButton(type);
}

bool VisionGraph::removeToolButton(ToolButtonType type)
{
    return m_graphWidget->removeToolButton(type);
}

void VisionGraph::addToolButton(QToolButton *btn)
{
    m_graphWidget->addToolButton(btn);
}

void VisionGraph::removeToolBarInfoWidget()
{
    m_graphWidget->removeToolBarInfoWidget();
}

void VisionGraph::addToolFrame()
{

}

void VisionGraph::setViewRegion_Size(qreal w, qreal h)
{
    m_graphWidget->setViewRegion_Size(w,h);
}

void VisionGraph::setViewRegion_Visible(bool bVisible)
{
    m_graphWidget->setViewRegion_Visible(bVisible);
}

void VisionGraph::setViewRegion_Color(const QColor &color)
{
    m_graphWidget->setViewRegion_Color(color);
}

QImage VisionGraph::getBkgImg()
{
    QImage image;
    image = m_graphWidget->getBkgImg();
    return image;
}

void VisionGraph::saveBkgImg(QString path)
{
    m_graphWidget->saveBkgImg(path);
}

void VisionGraph::removeItem(VisionItem *item)
{
    m_graphWidget->removeItem(item);
}

void VisionGraph::setMousePaintSize(qreal qi)
{
    m_graphWidget->setMousePaintSize(qi);
}

void VisionGraph::setView_Zoom(qreal qZoom)
{
    m_graphWidget->setView_Zoom(qZoom);
}

void VisionGraph::setViewType(ViewType type)
{
    m_graphWidget->setViewType(type);
}

QColor VisionGraph::getPixel(qreal x, qreal y)
{
    return m_graphWidget->getPixel(x,y);
}

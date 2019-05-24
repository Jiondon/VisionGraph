#include "visiontextitem.h"
#include <QDebug>

VisionTextItem::VisionTextItem(VisionItem *parent) : VisionItem(parent)
{
//    if(color_enable){
//        m_borderColor = borderColor;
//    }else{
//        m_borderColor = borderColor;
//    }
//    m_brushColor = brushColor;
//    m_selectedColor = selectedColor;

//    penColor = QColor(0,0,0);//black
//    penWidth = 1;
//    m_bRotation = rotation;
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable,false);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    setFlag(QGraphicsItem::ItemDoesntPropagateOpacityToChildren,true);
    setFlag(QGraphicsItem::ItemClipsChildrenToShape);

//    m_type = ItemType::Paint_Rect;

//    m_bEdit = edit;
//    if(m_bEdit){
//        setSelectedStatus(true);
//    }else{
//        setSelectedStatus(false);
//    }
}

void VisionTextItem::setData(VGRegion vgRegion, QString textName)
{
    m_vgRegion = vgRegion;
    m_strText = textName;

    if(m_vgRegion.arrayPointRun.size() <= 0)
        return;

    QLineF lineF;
    m_vecLines.clear();
    VGPointRun pointRun_init = m_vgRegion.arrayPointRun.at(0);
    qreal minX=pointRun_init.x,minY=pointRun_init.y,
            maxX=pointRun_init.x+pointRun_init.length,maxY=pointRun_init.y;
    for(int i=0;i<m_vgRegion.arrayPointRun.size();i++){
        VGPointRun pointRun = m_vgRegion.arrayPointRun.at(i);
        lineF.setPoints((QPointF(pointRun.x,pointRun.y)),
                        (QPointF(pointRun.x+pointRun.length,pointRun.y)));
        m_vecLines.append(lineF);


        //最大值
        if(pointRun.x+pointRun.length > maxX)
            maxX = pointRun.x+pointRun.length;

        if(pointRun.y > maxY)
            maxY = pointRun.y;

        if(pointRun.x < minX)
            minX = pointRun.x;

        if(pointRun.y < minY)
            minY = pointRun.y;
    }
    qDebug()<<"minX:: "<<minX<<"  minY :: "<<minY<<"  maxX:: "<<maxX<<"  maxY::"<<maxY;
    m_regionRf = QRectF(minX,minY,maxX-minX,maxY-minY);

//    this->setPos(minX-100,minY-100);
}

void VisionTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen = QPen(QColor(255,0,0),g_penWidth*(1/g_scale));
    painter->setPen(pen);


    //绘制文字区域
    QVector<QLineF> vecLines;
    for(int i=0;i<m_vecLines.size();i++){
        QLineF lineF = QLineF((m_vecLines.at(i).p1()),(m_vecLines.at(i).p2()));
        vecLines.append(lineF);
    }
    painter->drawLines(vecLines);

    QFont font;
    font.setPixelSize(m_textPiexl);
    painter->setFont(font);
    painter->drawText(QPointF(m_regionRf.x(),m_regionRf.y()),m_strText);

    if(m_bEnter){
        painter->setPen(QPen(QColor(0,0,0),g_penWidth*(1/g_scale)));
    }else{
        painter->setPen(QPen(QColor(255,0,0),g_penWidth*(1/g_scale)));
    }
    painter->drawRect(m_regionRf);

//    painter->setPen(QColor(0,0,255));
//    painter->drawRect(boundingRect());
}

void VisionTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit signal_DoubleClicked(this);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void VisionTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        qDebug()<<"right clicked";
        emit signal_RightClicked(this);
    }
    QGraphicsItem::mousePressEvent(event);
}

void VisionTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

void VisionTextItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_bEnter = true;
    QGraphicsItem::hoverEnterEvent(event);
}

void VisionTextItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_bEnter = false;
    QGraphicsItem::hoverLeaveEvent(event);
}

QRectF VisionTextItem::boundingRect() const
{
    return QRectF(m_regionRf.x(),m_regionRf.y()-m_textHeight,m_regionRf.width(),m_regionRf.height()+m_textHeight);
}

//void VisionTextItem::mouseMoveEvent(QGraphicsSceneHoverEvent *event)
//{
//    return;
//}

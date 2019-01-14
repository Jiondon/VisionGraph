#include "visionpolygon.h"
#include <QDebug>
#include "../control/color.h"

VisionPolygon::VisionPolygon(bool close, VisionItem *parent) : VisionItem(parent)
{
    m_borderColor = borderColor;
    m_brushColor = brushColor;
    m_selectedColor = m_selectedColor;

    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    m_type = ItemType::Paint_Poly;
    m_bEdit = true;
    m_bClose = close;
    setSelected(true);
}

VisionPolygon::~VisionPolygon()
{

}

void VisionPolygon::setPointFs(QVector<QPointF> pointFs, bool bFinished)
{
    m_vecPointFs = pointFs;
    m_polygonF.clear();
    m_polygonF.append(m_vecPointFs);

    //获取item的pos位置，boundingRect的topLeft

    QPointF orignPointF = m_polygonF.boundingRect().topLeft();
    m_x = orignPointF.x();
    m_y = orignPointF.y();

    for(int i=0;i<pointFs.count();i++){
        m_vecPointFs_temp.append(pointFs.at(i) - orignPointF);
    }
    m_polygonF_temp.append(m_vecPointFs_temp);

    this->setPos(m_x,m_y);

    if(bFinished){
        initMiniRect();
    }
}


bool VisionPolygon::getPosInArea(qreal x, qreal y)
{
    if(m_polygonF_temp.containsPoint(QPointF(x,y),Qt::OddEvenFill)){
        return true;
    }else{
        return false;
    }
}


void VisionPolygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    if(option->state & QStyle::State_Selected){

        painter->setPen(QPen(QBrush(m_selectedColor),0));

        for(int i=0;i<m_lstRect.count();i++){
            m_lstRect[i]->setVisible(true);
        }

        if(!m_bEdit){
            emit selectedChanged(true,this,ItemType::Paint_Poly,m_vecPointFs);
        }
        m_bEdit = true;
        setEdit(m_bEdit);

    }else{

        painter->setPen(QPen(QBrush(borderColor),0));

        for(int i=0;i<m_lstRect.count();i++){
            m_lstRect[i]->setVisible(false);
        }
        if(m_bEdit){
            emit selectedChanged(false,this,ItemType::Paint_Poly,m_vecPointFs);
        }

        m_bEdit = false;
        setEdit(m_bEdit);
    }

    if(m_bClose){
        painter->setBrush(m_brushColor);
        painter->drawPolygon(m_polygonF_temp);
    }else{
        painter->drawPolyline(m_polygonF_temp);
    }


    if(m_bEdit){
        QPainterPath path;
        path.addPolygon(m_polygonF);
        emit signal_painterInfo(ItemType::Paint_Poly,path);
    }

}

QRectF VisionPolygon::boundingRect() const
{
    QRectF rf = QRectF(m_polygonF_temp.boundingRect().x()-5,m_polygonF_temp.boundingRect().y()-5,
                       m_polygonF_temp.boundingRect().width()+10,m_polygonF_temp.boundingRect().height()+10);
    return rf;
}


void VisionPolygon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    m_lastPointF = event->scenePos();

    //鼠标属于非正常状态--拖动小矩形框，当鼠标在编辑框状态，不处理按下事件，此时只需要处理moveEvent事件即可
    if(m_iIndex != -1)
        return;

    if(m_polygonF_temp.containsPoint(event->pos(),Qt::OddEvenFill)){
//        qDebug()<<" mouse press Event : true";
        setSelected(true);
    }else{
        setSelected(false);
//        qDebug()<<" mouse press Event false";
    }
    this->scene()->update();
}

void VisionPolygon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_iIndex != -1)
        return;

    if(!m_polygonF_temp.containsPoint(event->pos(),Qt::OddEvenFill)){
        emit signal_clicked(this,true,true,event->scenePos().x(),event->scenePos().y());
        return;
    }
    emit signal_clicked(this,true,false,event->scenePos().x(),event->scenePos().y());
    QGraphicsItem::mouseReleaseEvent(event);

}

void VisionPolygon::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if(!m_bEdit)
        return;

    //在执行QGraphicsItem的时候。会自动的进行pos的重新设置
    QGraphicsItem::mouseMoveEvent(event);

    QPointF disPointF = event->scenePos() - m_lastPointF;
    m_lastPointF = event->scenePos();

    if(m_vecPointFs.count() > m_iIndex && m_iIndex != -1){
        m_vecPointFs.replace(m_iIndex,event->scenePos());

        m_vecPointFs_temp.replace(m_iIndex,event->scenePos()-QPointF(m_x,m_y));
    }else{
        //拖动的时候。m_vecPointFs是不变化的，变化的事this->pos()
        for(int i=0;i<m_vecPointFs.count();i++){
            m_vecPointFs.replace(i,m_vecPointFs.at(i)+disPointF);
        }
        m_x = m_x + disPointF.x();m_y = m_y + disPointF.y();
    }
    m_polygonF.clear();
    m_polygonF.append(m_vecPointFs);
    m_polygonF_temp.clear();
    m_polygonF_temp.append(m_vecPointFs_temp);

    updateMiniRect();
    this->setPos(m_x,m_y);
    emit signalChanged(this);
    this->scene()->update();
}


void VisionPolygon::initMiniRect()
{
    m_lstRect.clear();

    for(int i=0;i<m_vecPointFs_temp.count();i++){
        MiniRect* miniRect = new MiniRect(m_vecPointFs_temp.at(i).x()-5,m_vecPointFs_temp.at(i).y()-5,10,10,QColor(255,0,0),this);
        miniRect->setIndex(i);
        connect(miniRect,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));
        m_lstRect.append(miniRect);
    }

}

void VisionPolygon::updateMiniRect()
{

    for(int i=0;i<m_vecPointFs_temp.count();i++){
        m_lstRect[i]->setPos(m_vecPointFs_temp.at(i).x()-5,m_vecPointFs_temp.at(i).y()-5);
    }
}

void VisionPolygon::slotIndex(int index)
{
    m_iIndex = index;
    QGraphicsView *view = this->scene()->views().at(0);

    if(m_iIndex == -1){
        view->setCursor(viewCursor);
    }else{
        QCursor cursor = QCursor(QPixmap(iconPath+"cursor-sizeall.png"));
        view->setCursor(cursor);
    }
}

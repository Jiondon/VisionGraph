#include "visionpolygon.h"
#include <QDebug>
#include "../control/color.h"

VisionPolygon::VisionPolygon(VisionItem *parent) : VisionItem(parent)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    m_type = ItemType::Poly;
    m_bEdit = true;
    setSelected(true);
}

void VisionPolygon::setPointFs(QVector<QPointF> pointFs, bool bFinished)
{
    m_vecPointFs = pointFs;
    m_polygonF.clear();
    m_polygonF.append(m_vecPointFs);

    if(bFinished){
        initMiniRect();
    }
}


bool VisionPolygon::getPosInArea(qreal x, qreal y)
{
    if(m_polygonF.containsPoint(QPointF(x,y),Qt::OddEvenFill)){
        return true;
    }else{
        return false;
    }
}


void VisionPolygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setPen(QPen(QBrush(borderColor),0));
//    painter->setBrush(QColor(255,0,0,50));
    painter->drawPolygon(m_vecPointFs);

    QPainterPath path;
    path.addPolygon(m_polygonF);
    emit signal_painterInfo(ItemType::Poly,path);

    if(option->state & QStyle::State_Selected){
        for(int i=0;i<m_lstRect.count();i++){
            m_lstRect[i]->setVisible(true);
        }

        if(!m_bEdit){
            emit selectedChanged(true,this,ItemType::Poly,m_vecPointFs);
        }
        m_bEdit = true;
        setEdit(m_bEdit);

    }else{
        for(int i=0;i<m_lstRect.count();i++){
            m_lstRect[i]->setVisible(false);
        }
        if(m_bEdit){
            emit selectedChanged(false,this,ItemType::Poly,m_vecPointFs);
        }

        m_bEdit = false;
        setEdit(m_bEdit);
    }

}

QRectF VisionPolygon::boundingRect() const
{
    QRectF rf = QRectF(m_polygonF.boundingRect().x()-5,m_polygonF.boundingRect().y()-5,
                       m_polygonF.boundingRect().width()+10,m_polygonF.boundingRect().height()+10);
    return rf;
}


void VisionPolygon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

    if(!m_bEdit)
        return;

    if(m_polygonF.containsPoint(event->pos(),Qt::OddEvenFill)){
        qDebug()<<"true";
        setSelected(true);
    }else{
        setSelected(false);
        qDebug()<<"false";
    }
    m_lastPointF = event->scenePos();
    this->scene()->update();
}

void VisionPolygon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;
    if(!m_polygonF.containsPoint(QPointF(event->scenePos().x(),event->scenePos().y()),Qt::OddEvenFill)){
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
//    QGraphicsItem::mouseMoveEvent(event);


    QPointF disPointF = event->scenePos() - m_lastPointF;
    m_lastPointF = event->scenePos();

    if(m_vecPointFs.count() > m_iIndex && m_iIndex != -1){
        m_vecPointFs[m_iIndex] = event->scenePos();
        m_polygonF.clear();
        m_polygonF.append(m_vecPointFs);
        updateMiniRect();
    }else{
        //拖动的时候。m_vecPointFs是不变化的，变化的事this->pos()

        for(int i=0;i<m_vecPointFs.count();i++){
            m_vecPointFs[i] = m_vecPointFs[i]+disPointF;
        }
        m_polygonF.clear();
        m_polygonF.append(m_vecPointFs);
        updateMiniRect();
    }
    this->scene()->update();
}


void VisionPolygon::initMiniRect()
{
    m_lstRect.clear();

    for(int i=0;i<m_vecPointFs.count();i++){
        MiniRect* miniRect = new MiniRect(m_vecPointFs[i].x()-this->pos().x()-5,m_vecPointFs[i].y()-this->pos().y()-5,10,10,QColor(255,0,0),this);
        miniRect->setIndex(i);
        connect(miniRect,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));
        m_lstRect.append(miniRect);
    }

}

void VisionPolygon::updateMiniRect()
{
    for(int i=0;i<m_vecPointFs.count();i++){
        m_lstRect[i]->setPos(m_vecPointFs[i].x()-this->pos().x()-5,m_vecPointFs[i].y()-this->pos().y()-5);
    }
}

void VisionPolygon::slotIndex(int index)
{
    m_iIndex = index;
    QGraphicsView *view = this->scene()->views().at(0);

    if(m_iIndex == -1){
        view->setCursor(Qt::ArrowCursor);
    }else{
        QCursor cursor = QCursor(QPixmap(":/icon/cursor-sizeall.png"));
        view->setCursor(cursor);
    }
}

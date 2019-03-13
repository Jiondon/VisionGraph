#include "visionring.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QDebug>
#include "../control/color.h"

VisionRing::VisionRing(qreal centerX, qreal centerY, qreal r1, qreal r2, bool bEdit, qreal penWidth,
                       bool color_enable, QColor penColor, VisionItem *parent) : VisionItem(parent)
{
    if(color_enable){
        m_borderColor = penColor;
    }else{
        m_borderColor = borderColor;
    }
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;

    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);

    m_rf1 = QRectF(centerX-r1,centerY-r1,2*r1,2*r1);
    m_rf2 = QRectF(centerX-r2,centerY-r2,2*r2,2*r2);
    m_r1 = r1;m_r2 = r2;

    m_centerX = centerX;
    m_centerY = centerY;

    m_penColor = penColor;
    m_penWidth = penWidth;

    m_bEdit = bEdit;
    if(m_bEdit){
        setSelectedStatus(true);
    }else{
        setSelectedStatus(false);
    }

    setItemPos();
    initMiniRect();
}

VisionRing::VisionRing(QRectF rf1, QRectF rf2, bool bEdit, qreal penWidth, QColor penColor, QGraphicsItem *parent)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);

    m_rf1 = rf1;m_rf2 = rf2;
    m_r1 = rf1.width()/2;m_r2 = rf2.width()/2;
    m_centerX = m_rf1.x()-m_r1;
    m_centerY = m_rf1.y()-m_r1;
    m_penColor = penColor;
    m_penWidth = penWidth;

    setItemPos();
    initMiniRect();
}

void VisionRing::setDirection(int iDirection)
{
    m_iDirection = iDirection;
}

QPainterPath VisionRing::getPainterPath()
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

QVector<QPointF> VisionRing::getPoints()
{
    QVector<QPointF> vec_p;
    vec_p.append(m_rf1.topLeft());
    vec_p.append(m_rf1.topRight());
    vec_p.append(m_rf1.bottomRight());
    vec_p.append(m_rf1.bottomLeft());
    vec_p.append(m_rf2.topLeft());
    vec_p.append(m_rf2.topRight());
    vec_p.append(m_rf2.bottomRight());
    vec_p.append(m_rf2.bottomLeft());
    return vec_p;
}

void VisionRing::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

//    qDebug()<<m_width<<m_height<<m_r1<<m_r2;
    painter->setPen(QPen(m_borderColor,0));
    painter->drawEllipse(QPointF(m_width/2,m_height/2),m_r1,m_r1);
    painter->drawEllipse(QPointF(m_width/2,m_height/2),m_r2,m_r2);
    painter->drawRect(0,0,m_width,m_height);

    if(option->state & QStyle::State_Selected){
//        qDebug()<<"show miniRect";
        if(m_bSelected1){
            //显示圆1的编辑边框
            for(int i=0;i<4;i++){
                m_lstRect[i]->show(); //top
            }
        }else{
            for(int i=0;i<4;i++){
                m_lstRect[i]->hide(); //top
            }
        }

        if(m_bSelected2){
            //显示圆2的编辑边框
            for(int i=0;i<4;i++){
                m_lstRect[i+4]->show(); //top
            }
        }else{
            for(int i=0;i<4;i++){
                m_lstRect[i+4]->hide(); //top
            }
        }
    }else{
//        qDebug()<<"hide miniRect";
        for(int i=0;i<8;i++){
            m_lstRect[i]->hide(); //top
        }
    }

    //绘制方向
    //2 --> 1 正向   1 --> 2 反向

    painter->setPen(QPen(QBrush(QColor(255,0,0)),0));
    if(m_iDirection == 0){
        //正向
        painter->drawLine(QPointF(m_width/2+m_r2,m_height/2),QPointF(m_width/2+m_r1,m_height/2));
        if(m_r1 > m_r2){
             //-->
            painter->drawLine(QPointF(m_width/2+m_r1-10,m_height/2-5),QPointF(m_width/2+m_r1,m_height/2));
            painter->drawLine(QPointF(m_width/2+m_r1-10,m_height/2+5),QPointF(m_width/2+m_r1,m_height/2));
        }else{
            // <--
            painter->drawLine(QPointF(m_width/2+m_r1+10,m_height/2-5),QPointF(m_width/2+m_r1,m_height/2));
            painter->drawLine(QPointF(m_width/2+m_r1+10,m_height/2+5),QPointF(m_width/2+m_r1,m_height/2));
        }
    }else if(m_iDirection == -1){
        //反向
        painter->drawLine(QPointF(m_width/2+m_r1,m_height/2),QPointF(m_width/2+m_r2,m_height/2));
        if(m_r1 > m_r2){
             //<-
            painter->drawLine(QPointF(m_width/2+m_r2+10,m_height/2-5),QPointF(m_width/2+m_r2,m_height/2));
            painter->drawLine(QPointF(m_width/2+m_r2+10,m_height/2+5),QPointF(m_width/2+m_r2,m_height/2));
        }else{
            // -->
            painter->drawLine(QPointF(m_width/2+m_r2-10,m_height/2-5),QPointF(m_width/2+m_r2,m_height/2));
            painter->drawLine(QPointF(m_width/2+m_r2-10,m_height/2+5),QPointF(m_width/2+m_r2,m_height/2));
        }
    }
    /*

    //选中内圆部分区域，则内圆为编辑模式     选中外圆部分区域，则外圆为编辑模式
    //全部加上对应rect的x和this的x差值--理由是绘制的时候，是相对this的左上角作为原点进行绘制的，小的圆形，坐标是该rect的x和this之间的差值
    qreal iTemp = 5;
    painter->drawRect(m_width/2-iTemp,m_height/2-m_rf1.height()/2-iTemp,2*iTemp,2*iTemp); //top
    painter->drawRect(m_width/2+m_rf1.width()/2-iTemp,m_height/2-iTemp,2*iTemp,2*iTemp); //right
    painter->drawRect(m_width/2-iTemp,m_height/2+m_rf1.height()/2-iTemp,2*iTemp,2*iTemp);  //bottom
    painter->drawRect(m_width/2-m_rf1.width()/2-iTemp,m_height/2-iTemp,2*iTemp,2*iTemp); //left

    //显示圆2的编辑边框
    painter->setPen(QPen(QColor(255,0,0),0));
    painter->setBrush(QBrush(QColor(255,0,0)));
    qreal iTemp = 5;
    painter->drawRect(m_width/2-iTemp,m_height/2-m_rf2.height()/2-iTemp,2*iTemp,2*iTemp); //top
    painter->drawRect(m_width/2+m_rf2.width()/2-iTemp,m_height/2-iTemp,2*iTemp,2*iTemp); //right
    painter->drawRect(m_width/2-iTemp,m_height/2+m_rf2.height()/2-iTemp,2*iTemp,2*iTemp);  //bottom
    painter->drawRect(m_width/2-m_rf2.width()/2-iTemp,m_height/2-iTemp,2*iTemp,2*iTemp); //left
    */
}

QRectF VisionRing::boundingRect() const
{
    return QRectF(-5,-5,m_width+10,m_height+10);
}

void VisionRing::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    if(!m_bEdit)
        return;

    qreal qx = event->scenePos().x()-m_centerX;
    qreal qy = event->scenePos().y()-m_centerY;
    qreal qr = sqrt(qx*qx+qy*qy);

    m_curPointF = event->scenePos();
    QPointF disPointF = m_curPointF - m_lastPointF;
    m_lastPointF = m_curPointF;

    if(m_bSelected1 && m_bSelected2){
        //1，2均被选中
        qDebug()<<"drag area";
        m_centerX = m_centerX+disPointF.x();
        m_centerY = m_centerY+disPointF.y();
    }else if(m_bSelected1 && m_iIndex == 1){
        //在只有1被选中的情况，进行拉伸
        qDebug()<<"drag select1";
        m_r1 = qr;


    }else if(m_bSelected2 && m_iIndex == 2){
        qDebug()<<"drag selected2";
        m_r2 = qr;
    }
    this->setItemPos();
    this->scene()->update();
}

void VisionRing::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    if(!m_bEdit)
        return;

    qreal qx = event->scenePos().x()-m_centerX;
    qreal qy = event->scenePos().y()-m_centerY;
    qreal qr = sqrt(qx*qx+qy*qy);

//    if()
    if(qr > m_r1+5 && qr > m_r2+5){
        m_bSelected1 = false;
        m_bSelected2 = false;
        setSelectedStatus(false);
        this->scene()->update();
        return;
    }

    setEnabled(true);
    m_lastPointF = event->scenePos();

    //排除在非正常模式下的干扰
//    if(m_direcCursor != normal_rect)
//        return;

    if(qr < (m_r1+5) && qr > (m_r1-5)){
        //m_rf1 被选中
        qDebug()<<"rect 1 selected";
        m_bSelected1 = true;
        m_bSelected2 = false;
    }else if(qr < (m_r2+5) && qr > (m_r2-5)){
        //m_rf2 被选中
        qDebug()<<"rect 2 selected";
        m_bSelected1 = false;
        m_bSelected2 = true;
    }else{
        qDebug()<<"selceted other area";
        m_bSelected1 = true;
        m_bSelected2 = true;
        //变成可拖动的状态
    }
    this->scene()->update();
}

void VisionRing::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void VisionRing::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverMoveEvent(event);
}

void VisionRing::setItemPos()
{
    if(m_centerX-m_r1 > m_centerX-m_r2){
        this->setPos(m_centerX-m_r2,m_centerY-m_r2);
        m_x = m_centerX-m_r2;m_y = m_centerY-m_r2;
        m_width = 2*m_r2;m_height = 2*m_r2;
    }else{
        this->setPos(m_centerX-m_r1,m_centerY-m_r1);
        m_x = m_centerX-m_r1;m_y = m_centerY-m_r1;
        m_width = 2*m_r1;m_height = 2*m_r1;
    }
    m_rf1.setRect(m_centerX-m_r1,m_centerY-m_r1,2*m_r1,2*m_r1);
    m_rf2.setRect(m_centerX-m_r2,m_centerY-m_r2,2*m_r2,2*m_r2);
    updateMiniRect();
}

void VisionRing::initMiniRect()
{
    //list rectF
    m_lstRect.clear();
    qreal iTemp = 5;
    MiniRect* rect11 = new MiniRect(m_width/2-iTemp,m_height/2-m_rf1.height()/2-iTemp,2*iTemp,2*iTemp,QColor(255,0,0),this); //top
    rect11->setIndex(0);
    connect(rect11,SIGNAL(signalIndex(int)),this,SLOT(slotIndex_MiniRect(int)));

    MiniRect* rect12 = new MiniRect(m_width/2+m_rf1.width()/2-iTemp,m_height/2-iTemp,2*iTemp,2*iTemp,QColor(255,0,0),this); //right
    rect12->setIndex(1);
    connect(rect12,SIGNAL(signalIndex(int)),this,SLOT(slotIndex_MiniRect(int)));

    MiniRect* rect13 = new MiniRect(m_width/2-iTemp,m_height/2+m_rf1.height()/2-iTemp,2*iTemp,2*iTemp,QColor(255,0,0),this);  //bottom
    rect13->setIndex(2);
    connect(rect13,SIGNAL(signalIndex(int)),this,SLOT(slotIndex_MiniRect(int)));

    MiniRect* rect14 = new MiniRect(m_width/2-m_rf1.width()/2-iTemp,m_height/2-iTemp,2*iTemp,2*iTemp,QColor(255,0,0),this); //left
    rect14->setIndex(3);
    connect(rect14,SIGNAL(signalIndex(int)),this,SLOT(slotIndex_MiniRect(int)));

    //显示圆2的编辑边框

    MiniRect* rect21 = new MiniRect(m_width/2-iTemp,m_height/2-m_rf2.height()/2-iTemp,2*iTemp,2*iTemp,QColor(255,0,0),this); //top
    rect21->setIndex(4);
    connect(rect21,SIGNAL(signalIndex(int)),this,SLOT(slotIndex_MiniRect(int)));

    MiniRect* rect22 = new MiniRect(m_width/2+m_rf2.width()/2-iTemp,m_height/2-iTemp,2*iTemp,2*iTemp,QColor(255,0,0),this); //right
    rect22->setIndex(5);
    connect(rect22,SIGNAL(signalIndex(int)),this,SLOT(slotIndex_MiniRect(int)));

    MiniRect* rect23 = new MiniRect(m_width/2-iTemp,m_height/2+m_rf2.height()/2-iTemp,2*iTemp,2*iTemp,QColor(255,0,0),this);  //bottom
    rect23->setIndex(6);
    connect(rect23,SIGNAL(signalIndex(int)),this,SLOT(slotIndex_MiniRect(int)));

    MiniRect* rect24 = new MiniRect(m_width/2-m_rf2.width()/2-iTemp,m_height/2-iTemp,2*iTemp,2*iTemp,QColor(255,0,0),this); //left
    rect24->setIndex(7);
    connect(rect24,SIGNAL(signalIndex(int)),this,SLOT(slotIndex_MiniRect(int)));

    m_lstRect.append(rect11);
    m_lstRect.append(rect12);
    m_lstRect.append(rect13);
    m_lstRect.append(rect14);

    m_lstRect.append(rect21);
    m_lstRect.append(rect22);
    m_lstRect.append(rect23);
    m_lstRect.append(rect24);
}

void VisionRing::updateMiniRect()
{
    qreal iTemp = 5;
    for(int i=0;i<m_lstRect.count();i++){
        if(i == 0){
            m_lstRect[0]->setPos(m_width/2-iTemp,m_height/2-m_r1-iTemp);

        }else if(i == 1){
            m_lstRect[1]->setPos(m_width/2+m_r1-iTemp,m_height/2-iTemp);

        }else if(i == 2){
            m_lstRect[2]->setPos(m_width/2-iTemp,m_height/2+m_r1-iTemp);

        }else if(i == 3){
            m_lstRect[3]->setPos(m_width/2-m_r1-iTemp,m_height/2-iTemp);

        }else if(i == 4){
            m_lstRect[4]->setPos(m_width/2-iTemp,m_height/2-m_r2-iTemp);

        }else if(i == 5){
            m_lstRect[5]->setPos(m_width/2+m_r2-iTemp,m_height/2-iTemp);

        }else if(i == 6){
            m_lstRect[6]->setPos(m_width/2-iTemp,m_height/2+m_r2-iTemp);

        }else if(i == 7){
            m_lstRect[7]->setPos(m_width/2-m_r2-iTemp,m_height/2-iTemp);
        }
    }
}

void VisionRing::slotIndex_MiniRect(int index)
{

    if(m_lstRect.count() < 8)
        return;

    if(m_bSelected1 && index == 0){
        m_iIndex = 1;
        m_direcCursor = top_rect;
        m_lstRect[0]->setCursor(Qt::SizeVerCursor);
    }else if(m_bSelected1 && index == 1){
        m_iIndex = 1;
        m_direcCursor = right_rect;
        m_lstRect[1]->setCursor(Qt::SizeHorCursor);
    }else if(m_bSelected1 && index == 2){
        m_iIndex = 1;
        m_direcCursor = bottom_rect;
        m_lstRect[2]->setCursor(Qt::SizeVerCursor);
    }else if(m_bSelected1 && index == 3){
        m_iIndex = 1;
        m_direcCursor = left_rect;
        m_lstRect[3]->setCursor(Qt::SizeHorCursor);
    }else if(m_bSelected2 && index == 4){
        m_iIndex = 2;
        m_direcCursor = top_rect;
        m_lstRect[4]->setCursor(Qt::SizeVerCursor);
    }else if(m_bSelected2 && index == 5){
        m_iIndex = 2;
        m_direcCursor = right_rect;
        m_lstRect[5]->setCursor(Qt::SizeHorCursor);
    }else if(m_bSelected2 && index == 6){
        m_iIndex = 2;
        m_direcCursor = bottom_rect;
        m_lstRect[6]->setCursor(Qt::SizeVerCursor);
    }else if(m_bSelected2 && index == 7){
        m_iIndex = 2;
        m_direcCursor = left_rect;
        m_lstRect[7]->setCursor(Qt::SizeHorCursor);
    }else{
        m_direcCursor = normal_rect;
        for(int i=0;i<m_lstRect.count();i++){
            m_lstRect[i]->setCursor(Qt::ArrowCursor);
        }
    }
}

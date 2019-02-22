#include "visionlineitemfitting.h"

#include <QDebug>
#include <QPainterPath>

#include "../control/color.h"

VisionLineItemFitting::VisionLineItemFitting(bool bEdit, QPointF p1, QPointF p2, qreal length,
                                             qreal penWidth, QColor penColor, VisionItem *parent) : VisionItem(parent)
{
    this->setAcceptHoverEvents(true);
    m_borderColor = borderColor;
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;

    m_brushColor = QColor(255,0,0,125);
    m_pointF1 = p1;m_pointF2 = p2;
    m_penColor = penColor;
    m_penWidth = penWidth;
    m_bEdit = bEdit;
    m_type = ItemType::Paint_LineFitting;

    m_length = length;

    if(m_bEdit){
        setSelectedStatus(true);
    }else{
        setSelectedStatus(true);
    }

    m_bFitting = true;

    m_polygonF.clear();

    m_miniRect1 = new MiniRect(m_pointF1.x()-5,m_pointF1.y()-5,10,10,QColor(255,0,0),this);
    m_miniRect1->setIndex(1);
    connect(m_miniRect1,SIGNAL(signalIndex(int)),this,SLOT(slotMiniRectIndex(int)));
    m_miniRect1->hide();
    m_miniRect2 = new MiniRect(m_pointF2.x()-5,m_pointF2.y()-5,10,10,QColor(255,0,0),this);
    m_miniRect2->setIndex(2);
    connect(m_miniRect2,SIGNAL(signalIndex(int)),this,SLOT(slotMiniRectIndex(int)));
    m_miniRect2->hide();

    m_polygonF.clear();
    m_polygonF.append({m_pointF1,m_pointF2});
    updateRect(m_polygonF);

}

void VisionLineItemFitting::setLine(QPointF p1, QPointF p2)
{
    m_pointF1 = p1;
    m_pointF2 = p2;
    m_miniRect1->setRect(m_pointF1.x()-5,m_pointF1.y()-5,10,10);
    m_miniRect2->setRect(m_pointF2.x()-5,m_pointF2.y()-5,10,10);

    m_polygonF.clear();
    m_polygonF.append({m_pointF1,m_pointF2});
    updateRect(m_polygonF);
}

void VisionLineItemFitting::setPenWidth(qreal penWidth)
{
    m_penWidth = penWidth;
}

void VisionLineItemFitting::setPenColor(QColor color)
{
    m_penColor = color;
}

bool VisionLineItemFitting::getPosInArea(qreal x, qreal y)
{
    if(m_polygonF.containsPoint(QPointF(x,y),Qt::OddEvenFill)){
        return true;
    }else{
        return false;
    }
}

QVector<QPointF> VisionLineItemFitting::getPoints(){
    QVector<QPointF> vec_p;
    vec_p.append(m_pointF1);
    vec_p.append(m_pointF2);
    return vec_p;
}

QRectF VisionLineItemFitting::boundingRect() const
{
    return QRectF(m_x-10,m_y-10,m_width+20,m_height+20);
}

void VisionLineItemFitting::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    if(option->state & QStyle::State_Selected){
        painter->setPen(QPen(QBrush(m_selectedColor),0));

    }else{
        painter->setPen(QPen(QBrush(m_borderColor),0));

    }

    painter->drawLine(m_pointF1,m_pointF2);
    painter->setBrush(m_brushColor);
    painter->drawPolygon(m_polygonF);

    if(!m_bEdit)
        return;

    //绘制编辑框
    if(option->state & QStyle::State_Selected){
        m_miniRect1->show();
        m_miniRect2->show();
        m_bSelected = true;
        setSelectedStatus(m_bSelected);
    }else{
        m_miniRect1->hide();
        m_miniRect2->hide();
        m_bSelected = false;
        setSelectedStatus(m_bSelected);
    }
}

void VisionLineItemFitting::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_bFitting = false;
    setSelectedStatus(true);
}

void VisionLineItemFitting::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    if(!m_bSelected)
        return;

//    QGraphicsItem::mouseMoveEvent(event);
    QPointF disPointF = event->scenePos()-m_lastPointF;
    m_lastPointF = event->scenePos();
    if(m_iIndex == 1){
        m_pointF1 = event->scenePos();
    }else if(m_iIndex == 2){
        m_pointF2 = event->scenePos();
    }else if(m_iIndex == 3){
        //边框拖动只改变m_length
        qreal A = m_pointF2.y() - m_pointF1.y();
        qreal B = m_pointF1.x() - m_pointF2.x();
        qreal C = m_pointF2.x()*m_pointF1.y() - m_pointF1.x()*m_pointF2.y();
        qreal l = fabs(A*event->scenePos().x() + B*event->scenePos().y() + C)/sqrt(A*A+B*B);
        m_length = l;
    }else{
        //移动整体
        m_pointF1 = m_pointF1 + disPointF;
        m_pointF2 = m_pointF2 + disPointF;
    }

    m_miniRect1->setPos(m_pointF1.x()-5,m_pointF1.y()-5);
    m_miniRect2->setPos(m_pointF2.x()-5,m_pointF2.y()-5);

    updatePolygon();

    emit signalChanged(this);
    this->scene()->update();
}

void VisionLineItemFitting::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    if(!m_polygonF.containsPoint(event->scenePos(),Qt::OddEvenFill)){
        emit signal_clicked(this,true,false,event->scenePos().x(),event->scenePos().y());
        return;
    }
    emit signal_clicked(this,true,true,event->scenePos().x(),event->scenePos().y());
    QGraphicsItem::mouseReleaseEvent(event);
}

void VisionLineItemFitting::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(m_bFitting){
        //记录length，并且刷新绘制的区域   length 为鼠标的位置到线的距离
        qreal A = m_pointF2.y() - m_pointF1.y();
        qreal B = m_pointF1.x() - m_pointF2.x();
        qreal C = m_pointF2.x()*m_pointF1.y() - m_pointF1.x()*m_pointF2.y();
        m_lastPointF = event->scenePos();
        qreal l = fabs(A*event->scenePos().x() + B*event->scenePos().y() + C)/sqrt(A*A+B*B);
        m_length = l;
        //更新数据
        //获得垂直线数据
        //Bx-Ay+C1=0;
        qreal C1 = -event->scenePos().x()*B+event->scenePos().y()*A;
        //Ax+By+C=0  Bx-Ay+C1=0   x=-(A*C+B*C1)/(A*A+B*B)  y=-(B*C-A*C1)/(A*A+B*B)
        QPointF crossPoint = QPointF(-(A*C+B*C1)/(A*A+B*B),-(B*C-A*C1)/(A*A+B*B));
        QPointF disPointF = event->scenePos() - crossPoint;
        m_polygonF.clear();
        m_polygonF.append({m_pointF1 - disPointF,m_pointF2 - disPointF,m_pointF2 + disPointF, m_pointF1 +disPointF});
//        qDebug()<<m_polygonF<<m_polygonF.boundingRect();
        updateRect(m_polygonF);
        this->scene()->update();
    }else{
        //获取边框的状态；
        qreal A = m_pointF2.y() - m_pointF1.y();
        qreal B = m_pointF1.x() - m_pointF2.x();
        qreal C = m_pointF2.x()*m_pointF1.y() - m_pointF1.x()*m_pointF2.y();
        m_lastPointF = event->scenePos();
        qreal l = fabs(A*event->scenePos().x() + B*event->scenePos().y() + C)/sqrt(A*A+B*B);
        if(l<m_length+3 && l > m_length-3){
            m_iIndex = 3;
            this->scene()->views().at(0)->setCursor(Qt::SizeVerCursor);
        }else{
            //恢复正常
            m_iIndex = -1;
            this->scene()->views().at(0)->setCursor(viewCursor);
        }
    }
}

void VisionLineItemFitting::updateRect(QPolygonF polygonF)
{
    m_x = polygonF.boundingRect().x();
    m_y = polygonF.boundingRect().y();
    m_width = polygonF.boundingRect().width();
    m_height = polygonF.boundingRect().height();
}

void VisionLineItemFitting::updatePolygon()
{
    qreal A = m_pointF2.y() - m_pointF1.y();
    qreal B = m_pointF1.x() - m_pointF2.x();
    qreal C = m_pointF2.x()*m_pointF1.y() - m_pointF1.x()*m_pointF2.y();


    //直线的cos值  cosφ=A1A2+B1B2/[√(A1^2+B1^2)√(A2^2+B2^2)]  // A2=0 B2=1;  cosφ=B1/√(A1^2+B1^2)
    m_polygonF.clear();
    QPointF disPointF;
    //P1和P2起点不一致，对应的AB的值是不一致的，存在方向性，cosφ的值是根据向量计算出来的，实际的ABC是动态的，也要考虑到方向
    if(m_pointF1.x() < m_pointF2.x()){
        disPointF = QPoint((-A/sqrt(A*A+B*B))*m_length,m_length*sin(acos(-A/sqrt(A*A+B*B))));
    }else{
        disPointF = QPoint((A/sqrt(A*A+B*B))*m_length,m_length*sin(acos(A/sqrt(A*A+B*B))));
    }
    m_polygonF.append({m_pointF1 - disPointF,m_pointF2 - disPointF,m_pointF2 + disPointF, m_pointF1 + disPointF});
    updateRect(m_polygonF);
    this->scene()->update();
}

void VisionLineItemFitting::slotMiniRectIndex(int index)
{
    if(index == 1){
        //移动点1
        m_iIndex = 1;
        this->scene()->views().at(0)->setCursor(Qt::SizeAllCursor);
    }else if(index == 2){
        //移动点2
        m_iIndex = 2;
        this->scene()->views().at(0)->setCursor(Qt::SizeAllCursor);
    }else{
        //恢复正常
        m_iIndex = -1;
        this->scene()->views().at(0)->setCursor(viewCursor);
    }
}

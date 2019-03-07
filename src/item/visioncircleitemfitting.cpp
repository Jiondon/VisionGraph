#include "visioncircleitemfitting.h"
#include "../control/color.h"
#include <QDebug>

VisionCircleItemFitting::VisionCircleItemFitting(bool edit, qreal length,QColor color, VisionItem *parent) : VisionItem(parent)
{
    m_borderColor = borderColor;
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;

    penColor = QColor(0,0,0);//black
    penWidth = 1;
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    m_type = ItemType::Paint_CirCle;

    m_bFitting = true;
    m_length = length;

    m_bEdit = edit;
    if(m_bEdit){
        setSelectedStatus(true);
    }else{
        setSelectedStatus(false);
    }
}

void VisionCircleItemFitting::setCircle(qreal x, qreal y, qreal width, qreal height)
{
    m_width = width;
    m_height = height;
    m_x = x;
    m_y = y;

    this->setPos(m_x,m_y);

    m_lstPointF = rfToPoint(QRectF(m_x,m_y,m_width,m_height));

    initItem();
}

void VisionCircleItemFitting::setCircle(QPointF center, qreal r)
{
    m_width = 2*r;
    m_height = 2*r;
    m_x = center.x() - r;
    m_y = center.y() - r;

    this->setPos(m_x,m_y);

    m_lstPointF = rfToPoint(QRectF(m_x,m_y,m_width,m_height));

    initItem();
}

void VisionCircleItemFitting::setCircle(QRectF rf)
{
    m_width = rf.width();
    m_height = rf.height();
    m_x = rf.x();
    m_y = rf.y();

    this->setPos(m_x,m_y);

    m_lstPointF = rfToPoint(QRectF(m_x,m_y,m_width,m_height));

    initItem();
}


bool VisionCircleItemFitting::getPosInArea(qreal x, qreal y)
{
    if(boundingRect().contains(x-m_x,y-m_y)){
        return true;
    }else{
        return false;
    }
}

QVector<QPointF> VisionCircleItemFitting::getPoints()
{
    QVector<QPointF> vec_p;
    vec_p.append(QPointF(m_x,m_y));
    vec_p.append(QPointF(m_x+m_width,m_y));
    vec_p.append(QPointF(m_x,m_y+m_height));
    vec_p.append(QPointF(m_x+m_width,m_y+m_height));
    return vec_p;
}

void VisionCircleItemFitting::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);


    //保证在非编辑模式下，不会执行该语句---构造函数中做了setSelected(false)处理
    if(option->state & QStyle::State_Selected){

        painter->setPen(QPen(QBrush(m_selectedColor),0));

        //编辑模式下的小矩形框
        if(m_bEdit){
            for(int i=0;i<m_lstRect.count();i++){
                m_lstRect[i]->setVisible(true);
            }
        }

        //用处不大，主要考虑对应关系
        emit selectedChanged(true,this,ItemType::Paint_CirCle,QRectF(m_x,m_y,m_width,m_height),QPointF(m_x,m_y),0);

        m_bSelected = true;
        setSelectedStatus(m_bSelected);
    }else{

        painter->setPen(QPen(QBrush(m_borderColor),0));

        for(int i=0;i<m_lstRect.count();i++){
            m_lstRect[i]->setVisible(false);
        }

        //通知view将该item转换为区域 ---
        //由选中状态变为非选中状态，由于，构造函数默认为选中状态，故当item为未选中状态，则必定是由选中状态变为未选中状态，直接传输信号通知
        //前提是item是可编辑的
        if(m_bEdit){
            emit selectedChanged(false,this,ItemType::Paint_EllipseItem,QRectF(m_x,m_y,m_width,m_height),QPointF(m_x,m_y),0);
        }

        m_bSelected = false;
        setSelectedStatus(m_bSelected);

        if(directCursor != arrowsUp){
            this->scene()->views().at(0)->setCursor(viewCursor);
            directCursor = normal_rect;
        }
    }

    painter->setBrush(Qt::transparent);
    painter->drawEllipse(QRectF(0,0,m_width,m_height));

    QPen pen = QPen(QBrush(m_borderColor),0);
    pen.setStyle(Qt::DotLine);
    painter->setPen(pen);
    if(m_bSelected){
        painter->drawRect(QRectF(0,0,m_width,m_height));
    }

    painter->setBrush(m_brushColor);
    pen.setStyle(Qt::SolidLine);
    painter->drawPath(m_path);
}

QRectF VisionCircleItemFitting::boundingRect() const
{
    QRectF rf = QRectF(-5-m_length,-5-m_length,m_width+10+2*m_length,m_width+10+2*m_length);
    return rf;
}

void VisionCircleItemFitting::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_bFitting = false;

    if(!m_bEdit)
        return;

    //鼠标左键
    QGraphicsItem::mousePressEvent(event);

    if(m_iIndex != -1)
        return;


    setSelectedStatus(true);
    m_bSelected = true;

    lastPoint = event->scenePos();
    this->scene()->update();
}

void VisionCircleItemFitting::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    lastPointF = QPointF(0,0);
    if(!m_bEdit)
        return;

    if(m_iIndex != -1)
        return;

    emit signal_clicked(this,true,true,event->scenePos().x(),event->scenePos().y());
    QGraphicsItem::mouseReleaseEvent(event);

}

void VisionCircleItemFitting::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    //计算两次move的鼠标的差值，
    //计算两次move的鼠标的差值，
    QPointF curPoint = event->scenePos();
    QPointF disPoint = curPoint - lastPoint;
    QPointF disPointF;
    if(lastPointF != QPointF(0,0)){
        disPointF = curPoint - lastPointF;
    }else{
        disPointF = QPointF(0,0);
    }
    lastPoint = curPoint;
    lastPointF = curPoint;
    QGraphicsItem::mouseMoveEvent(event);

    if(directCursor == normal_rect){
        m_x = m_x + disPoint.x();m_y = m_y + disPoint.y();
        m_lstPointF = rfToPoint(QRectF(m_x,m_y,m_width,m_height));
    }else{
        if(m_iIndex == 10){
            float x = event->scenePos().x() - (m_x+m_width/2);
            float y = event->scenePos().y() - (m_y+m_width/2);
            m_length = fabs(m_width/2 - sqrt(x*x+y*y));

            if(m_width/2 <= 5){
                m_length = 0;
            }else if(m_length >= m_width/2 - 5){
                m_length = m_width/2 - 5;
            }
            QPainterPath path1,path2;
            path1.addEllipse(QRectF(m_length,m_length,m_width-2*m_length,m_height-2*m_length));
            path2.addEllipse(QRectF(-m_length,-m_length,m_width+2*m_length,m_height+2*m_length));
            m_path = path2 - path1;
        }else{
            QRectF rf = detailMove(m_iIndex,curPoint);
            m_x = rf.x();
            m_y = rf.y();
            m_width = rf.width();
            m_height = rf.height();

            if(m_width/2 <= 5){
                m_length = 0;
            }else if(m_length >= m_width/2 - 5){
                m_length = m_width/2 - 5;
            }
            QPainterPath path1,path2;
            path1.addEllipse(QRectF(m_length,m_length,m_width-2*m_length,m_height-2*m_length));
            path2.addEllipse(QRectF(-m_length,-m_length,m_width+2*m_length,m_height+2*m_length));
            m_path = path2 - path1;
        }

    }
    this->setPos(m_x,m_y);
    updateItem();

    emit signalChanged(this);
    this->scene()->update();
}

void VisionCircleItemFitting::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(m_bFitting){
        //记录length，并且刷新绘制的区域   length 为鼠标的位置到圆弧的距离
        float x = event->scenePos().x() - (m_x+m_width/2);
        float y = event->scenePos().y() - (m_y+m_width/2);
        m_length = fabs(m_width/2 - sqrt(x*x+y*y));

        if(m_width/2 <= 5){
            m_length = 0;
        }else if(m_length >= m_width/2 - 5){
            m_length = m_width/2 - 5;
        }

        QPainterPath path1,path2;
        path1.addEllipse(QRectF(m_length,m_length,m_width-2*m_length,m_height-2*m_length));
        path2.addEllipse(QRectF(-m_length,-m_length,m_width+2*m_length,m_height+2*m_length));
        m_path = path2 - path1;
        this->scene()->update();
    }else{

        if(!getPosInArea(event->scenePos().x(),event->scenePos().y())){
            return;
        }

        //获取边框的状态；
        float x = event->scenePos().x() - (m_x+m_width/2);
        float y = event->scenePos().y() - (m_y+m_width/2);
        qreal l = fabs(m_width/2 - sqrt(x*x+y*y));

        //同时要保证点在圆弧上， angle< <angle_spanAngle;

        if(l<m_length+3 && l > m_length-3){
            m_iIndex = 10;
            directCursor = arrowsUp;
            this->scene()->views().at(0)->setCursor(Qt::SizeVerCursor);
        }else{
            //恢复正常
            m_iIndex = -1;
            directCursor = normal_rect;
            this->scene()->views().at(0)->setCursor(viewCursor);
        }
    }
}

void VisionCircleItemFitting::initItem()
{
    m_lstRect.clear();

    MiniRect* miniRect1 = new MiniRect(-5,-5,10,10,QColor(255,0,0),this);
    miniRect1->setIndex(0);
    QObject::connect(miniRect1,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    MiniRect* miniRect2 = new MiniRect(-5+m_width/2,-5,10,10,QColor(255,0,0),this);
    miniRect2->setIndex(1);
    QObject::connect(miniRect2,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    MiniRect* miniRect3 = new MiniRect(-5+m_width,-5,10,10,QColor(255,0,0),this);
    miniRect3->setIndex(2);
    QObject::connect(miniRect3,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    MiniRect* miniRect4 = new MiniRect(-5+m_width,-5+m_height/2,10,10,QColor(255,0,0),this);
    miniRect4->setIndex(3);
    QObject::connect(miniRect4,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    MiniRect* miniRect5 = new MiniRect(-5+m_width,-5+m_height,10,10,QColor(255,0,0),this);
    miniRect5->setIndex(4);
    QObject::connect(miniRect5,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    MiniRect* miniRect6 = new MiniRect(-5+m_width/2,-5+m_height,10,10,QColor(255,0,0),this);
    miniRect6->setIndex(5);
    QObject::connect(miniRect6,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    MiniRect* miniRect7 = new MiniRect(-5,-5+m_height,10,10,QColor(255,0,0),this);
    miniRect7->setIndex(6);
    QObject::connect(miniRect7,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    MiniRect* miniRect8 = new MiniRect(-5,-5+m_height/2,10,10,QColor(255,0,0),this);
    miniRect8->setIndex(7);
    QObject::connect(miniRect8,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    miniRect1->hide();miniRect2->hide();miniRect3->hide();miniRect4->hide();
    miniRect5->hide();miniRect6->hide();miniRect7->hide();miniRect8->hide();

    m_lstRect.append(miniRect1);
    m_lstRect.append(miniRect2);
    m_lstRect.append(miniRect3);
    m_lstRect.append(miniRect4);
    m_lstRect.append(miniRect5);
    m_lstRect.append(miniRect6);
    m_lstRect.append(miniRect7);
    m_lstRect.append(miniRect8);
}

void VisionCircleItemFitting::updateItem()
{
    qreal x;qreal y;
    for(int i=0;i<m_lstRect.count();i++){
        if(i == 0){
            x = 0;
            y = 0;
        }else if(i == 1){
            x = m_width/2;
            y = 0;
        }else if(i == 2){
            x = m_width;
            y = 0;
        }else if(i == 3){
            x = m_width;
            y = m_height/2;
        }else if(i == 4){
            x = m_width;
            y = m_height;
        }else if(i == 5){
            x = m_width/2;
            y = m_height;
        }else if(i == 6){
            x = 0;
            y = m_height;
        }else if(i == 7){
            x = 0;
            y = m_height/2;
        }
        m_lstRect[i]->setPos(x-5,y-5);
    }
    QPainterPath path1,path2;
    path1.addEllipse(QRectF(m_length,m_length,m_width-2*m_length,m_height-2*m_length));
    path2.addEllipse(QRectF(-m_length,-m_length,m_width+2*m_length,m_height+2*m_length));
    m_path = path2 - path1;
}

QList<QPointF> VisionCircleItemFitting::rfToPoint(QRectF rf)
{
    QList<QPointF> lstPointF;
    lstPointF.push_back(rf.topLeft());
    lstPointF.push_back((rf.topLeft()+QPointF(rf.width()/2,0)));
    lstPointF.push_back(rf.topRight());
    lstPointF.push_back((rf.topRight()+QPointF(0,rf.height()/2)));
    lstPointF.push_back(rf.bottomRight());
    lstPointF.push_back((rf.bottomRight()+QPointF(-rf.width()/2,0)));
    lstPointF.push_back(rf.bottomLeft());
    lstPointF.push_back((rf.bottomLeft()+QPointF(0,-rf.height()/2)));
    return lstPointF;
}

QRectF VisionCircleItemFitting::pointsToRf(QList<QPointF> lstPointF)
{
    if(lstPointF.count() < 5)
        return QRectF(0,0,0,0);
    return QRectF(lstPointF.at(0),lstPointF.at(4));
}

QRectF VisionCircleItemFitting::detailMove(int index, QPointF p)
{
    qreal w;
    QPointF p0,p1,p2,p3,p4,p5,p6,p7;
    if(index == 0){
        //top-left
        w = fabs(m_lstPointF.at(4).x() - p.x());

        p4 = m_lstPointF.at(4);
        p0 = QPointF(m_lstPointF.at(4) - QPointF(w,w));
        p1 = QPointF(m_lstPointF.at(4) - QPointF(w/2,w));
        p2 = QPointF(m_lstPointF.at(4) - QPointF(0,w));
        p3 = QPointF(m_lstPointF.at(4) - QPointF(0,w/2));
        p5 = QPointF(m_lstPointF.at(4) - QPointF(w/2,0));
        p6 = QPointF(m_lstPointF.at(4) - QPointF(w,0));
        p7 = QPointF(m_lstPointF.at(4) - QPointF(w,w/2));


    }else if(index == 1){
        //top
        w = fabs(m_lstPointF.at(5).y() - p.y());

        p5 = m_lstPointF.at(5);
        p0 = QPointF(m_lstPointF.at(5) + QPointF(-w/2,-w));
        p1 = QPointF(m_lstPointF.at(5) + QPointF(0,-w));
        p2 = QPointF(m_lstPointF.at(5) + QPointF(w/2,-w));
        p3 = QPointF(m_lstPointF.at(5) + QPointF(w/2,-w/2));
        p4 = QPointF(m_lstPointF.at(5) + QPointF(w/2,0));
        p6 = QPointF(m_lstPointF.at(5) + QPointF(-w/2,0));
        p7 = QPointF(m_lstPointF.at(5) + QPointF(-w/2,-w/2));

    }else if(index == 2){
        //top-right
        w = fabs(m_lstPointF.at(6).x() - p.x());

        p6 = m_lstPointF.at(6);
        p0 = QPointF(m_lstPointF.at(6) + QPointF(0,-w));
        p1 = QPointF(m_lstPointF.at(6) + QPointF(w/2,-w));
        p2 = QPointF(m_lstPointF.at(6) + QPointF(w,-w));
        p3 = QPointF(m_lstPointF.at(6) + QPointF(w,-w/2));
        p4 = QPointF(m_lstPointF.at(6) + QPointF(w,0));
        p5 = QPointF(m_lstPointF.at(6) + QPointF(w/2,0));
        p7 = QPointF(m_lstPointF.at(6) + QPointF(0,-w/2));

    }else if(index == 3){
        //right
        w = fabs(m_lstPointF.at(7).x() - p.x());

        p7 = m_lstPointF.at(7);
        p0 = QPointF(m_lstPointF.at(7) + QPointF(0,-w/2));
        p1 = QPointF(m_lstPointF.at(7) + QPointF(w/2,-w/2));
        p2 = QPointF(m_lstPointF.at(7) + QPointF(w,-w/2));
        p3 = QPointF(m_lstPointF.at(7) + QPointF(w,0));
        p4 = QPointF(m_lstPointF.at(7) + QPointF(w,w/2));
        p5 = QPointF(m_lstPointF.at(7) + QPointF(w/2,w/2));
        p6 = QPointF(m_lstPointF.at(7) + QPointF(0,w/2));

    }else if(index == 4){
        //bottom-right

        w = fabs(m_lstPointF.at(0).x() - p.x());

        p0 = m_lstPointF.at(0);
        p1 = QPointF(m_lstPointF.at(0) + QPointF(w/2,0));
        p2 = QPointF(m_lstPointF.at(0) + QPointF(w,0));
        p3 = QPointF(m_lstPointF.at(0) + QPointF(w,w/2));
        p4 = QPointF(m_lstPointF.at(0) + QPointF(w,w));
        p5 = QPointF(m_lstPointF.at(0) + QPointF(w/2,w));
        p6 = QPointF(m_lstPointF.at(0) + QPointF(0,w));
        p7 = QPointF(m_lstPointF.at(0) + QPointF(0,w/2));

    }else if(index == 5){
        //bottom
        w = fabs(m_lstPointF.at(1).y() - p.y());

        p1 = m_lstPointF.at(1);
        p0 = QPointF(m_lstPointF.at(1) + QPointF(-w/2,0));
        p2 = QPointF(m_lstPointF.at(1) + QPointF(w/2,0));
        p3 = QPointF(m_lstPointF.at(1) + QPointF(w/2,w/2));
        p4 = QPointF(m_lstPointF.at(1) + QPointF(w/2,w));
        p5 = QPointF(m_lstPointF.at(1) + QPointF(0,w));
        p6 = QPointF(m_lstPointF.at(1) + QPointF(-w/2,w));
        p7 = QPointF(m_lstPointF.at(1) + QPointF(-w/2,w/2));

    }else if(index == 6){
        //bottom-left
        w = fabs(m_lstPointF.at(2).x() - p.x());

        p2 = m_lstPointF.at(2);
        p0 = QPointF(m_lstPointF.at(2) + QPointF(-w,0));
        p1 = QPointF(m_lstPointF.at(2) + QPointF(-w/2,0));
        p3 = QPointF(m_lstPointF.at(2) + QPointF(0,w/2));
        p4 = QPointF(m_lstPointF.at(2) + QPointF(0,w));
        p5 = QPointF(m_lstPointF.at(2) + QPointF(-w/2,w));
        p6 = QPointF(m_lstPointF.at(2) + QPointF(-w,w));
        p7 = QPointF(m_lstPointF.at(2) + QPointF(-w,w/2));

    }else if(index == 7){
        //left
        w = fabs(m_lstPointF.at(3).x() - p.x());

        p3 = m_lstPointF.at(3);
        p0 = QPointF(m_lstPointF.at(3) + QPointF(-w,-w/2));
        p1 = QPointF(m_lstPointF.at(3) + QPointF(-w/2,-w/2));
        p2 = QPointF(m_lstPointF.at(3) + QPointF(0,-w/2));
        p4 = QPointF(m_lstPointF.at(3) + QPointF(0,w/2));
        p5 = QPointF(m_lstPointF.at(3) + QPointF(-w/2,w/2));
        p6 = QPointF(m_lstPointF.at(3) + QPointF(-w,w/2));
        p7 = QPointF(m_lstPointF.at(3) + QPointF(-w,0));
    }
    m_lstPointF.clear();
    m_lstPointF.push_back(p0);
    m_lstPointF.push_back(p1);
    m_lstPointF.push_back(p2);
    m_lstPointF.push_back(p3);
    m_lstPointF.push_back(p4);
    m_lstPointF.push_back(p5);
    m_lstPointF.push_back(p6);
    m_lstPointF.push_back(p7);
    return pointsToRf(m_lstPointF);
}

void VisionCircleItemFitting::slotIndex(int index)
{
    //可以将对于的miniRect的鼠标样式修改下
//    qDebug()<<"click miniRect : "<<index;

    QCursor cursor;
    m_iIndex = index;
    if(index == 7){
        //left
        directCursor = left_rect;
        cursor = QCursor(QPixmap(iconPath+"cursor-sizeh.png"));
        this->scene()->views().at(0)->setCursor(cursor);

    }else if(index == 1){
        //top
        directCursor = top_rect;
        cursor = QCursor(QPixmap(iconPath+"cursor-sizev.png"));
        this->scene()->views().at(0)->setCursor(cursor);

    }else if(index == 3){
        //right
        directCursor = right_rect;
        cursor = QCursor(QPixmap(iconPath+"cursor-sizeh.png"));
        this->scene()->views().at(0)->setCursor(cursor);

    }else if(index == 5){
        //bottom
        directCursor = bottom_rect;
        cursor = QCursor(QPixmap(iconPath+"cursor-sizev.png"));
        this->scene()->views().at(0)->setCursor(cursor);

    }else if(index == 0){
        //left top
        directCursor = left_Top_rect;
        cursor = QCursor(QPixmap(iconPath+"cursor-sizef.png"));
        this->scene()->views().at(0)->setCursor(cursor);

    }else if(index == 2){
        //top right
        directCursor = right_top_rect;
        cursor = QCursor(QPixmap(iconPath+"cursor-sizeb.png"));
        this->scene()->views().at(0)->setCursor(cursor);

    }else if(index == 4){
        //right bottom
        directCursor = right_bottom_rect;
        cursor = QCursor(QPixmap(iconPath+"cursor-sizef.png"));
        this->scene()->views().at(0)->setCursor(cursor);

    }else if(index == 6){
        //bottom left
        directCursor = left_bottom_rect;
        cursor = QCursor(QPixmap(iconPath+"cursor-sizeb.png"));
        this->scene()->views().at(0)->setCursor(cursor);

    }else{
        m_iIndex = -1;
        directCursor = normal_rect;
        this->scene()->views().at(0)->setCursor(viewCursor);
    }
}


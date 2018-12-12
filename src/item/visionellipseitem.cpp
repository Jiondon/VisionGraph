#include "visionellipseitem.h"
#include <QDebug>
#include <QCursor>
#include <QtMath>
#include <QMatrix>
#include <QPixmap>

#include "../control/color.h"

#define pi 3.1415926

VisionEllipseItem::VisionEllipseItem(bool rotation, VisionItem *parent):VisionItem(parent)
{
    m_borderColor = borderColor;
    m_brushColor = brushColor;
    m_selectedColor = m_selectedColor;

    penColor = QColor(0,0,0);//black
    penWidth = 1;
    m_bRotation = rotation;
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    m_type = ItemType::EllipseItem;

    setSelected(true);
    setEdit(true);
    m_bEdit = true;
}

void VisionEllipseItem::setRect(qreal x, qreal y, qreal width, qreal height)
{
    m_width = width;
    m_height = height;
    m_x = x;
    m_y = y;

    m_pointF1 = QPointF(x,y);
    m_pointF2 = QPointF(x+width,y);
    m_pointF3 = QPointF(x+width,y+height);
    m_pointF4 = QPointF(x,y+height);

    this->setPos(m_x,m_y);

    initItem();

    if(m_bRotation){
        arrowsItem = new VisionArrows_Rotate(m_width/2,m_height/2,30,10,QColor(255,0,0),this);
        QObject::connect(arrowsItem,SIGNAL(signalHoverEnter()),this,SLOT(slotArrowsItem()));
        QObject::connect(arrowsItem,SIGNAL(signalHoverLeave()),this,SLOT(slotArrowsItem_leave()));
    }
}

void VisionEllipseItem::setRect(QRectF rf)
{
    m_width = rf.width();
    m_height = rf.height();
    m_x = rf.x();
    m_y = rf.y();

    m_pointF1 = QPointF(rf.x(),rf.y());
    m_pointF2 = QPointF(rf.x()+rf.width(),rf.y());
    m_pointF3 = QPointF(rf.x()+rf.width(),rf.y()+rf.height());
    m_pointF4 = QPointF(rf.x(),rf.y()+rf.height());

    this->setPos(m_x,m_y);

    initItem();

    if(m_bRotation){
        arrowsItem = new VisionArrows_Rotate(m_width/2,m_height/2,30,10,QColor(255,0,0),this);
        connect(arrowsItem,SIGNAL(signalHoverEnter()),this,SLOT(slotArrowsItem()));
        connect(arrowsItem,SIGNAL(signalHoverLeave()),this,SLOT(slotArrowsItem_leave()));
    }

}

QPainterPath VisionEllipseItem::getPainterPath()
{
    QPainterPath path;
    path.addEllipse(m_x,m_y,m_width,m_height);
    m_path = path;
    return m_path;
}

bool VisionEllipseItem::getPosInArea(qreal x, qreal y)
{
    //过滤掉在boundingRect但是不在绘制的有效区域的点击
    //根据椭圆定义，椭圆上任意一点，到横轴上的两个焦点距离之和等于2a
    qreal qc = sqrt(fabs((m_width/2)*(m_width/2) - (m_height/2)*(m_height/2)));
    //两个焦点需要平移到item的中心点
    qreal dx1 = x-m_x-(qc*cos(m_angle*pi/180)+m_width/2);
    qreal dy1 = y-m_y-(qc*sin(m_angle*pi/180)+m_height/2);
    qreal dx2 = x-m_x-(qc*cos(m_angle*pi/180+pi)+m_width/2);
    qreal dy2 = y-m_y-(qc*sin(m_angle*pi/180+pi)+m_height/2);
    //焦点1 (qc*cos(m_angle*pi/180),qc*cos(m_angle*pi/180))焦点2关于原点对称，因为该item的原点设置为中心点 焦点2(qc*cos(m_angle*pi/180+pi),qc*cos(m_angle*pi/180+pi))
//    qreal dx2 = x-qc*cos
    qreal l = sqrt(dx1*dx1+dy1*dy1)+sqrt(dx2*dx2+dy2*dy2);
    qDebug()<<m_x<<m_y<<m_width<<m_height<<"("<<l<<")";
    if(l <= m_height || l <= m_width){
        return true;
    }else{
        return false;
    }

}

void VisionEllipseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    if(option->state & QStyle::State_Selected){

        painter->setPen(QPen(QBrush(m_selectedColor),0));

        //编辑模式下的小矩形框
        for(int i=0;i<m_lstRect.count();i++){
            if(i%2 == 0){
                m_lstRect[i]->setVisible(false);
            }else{
                m_lstRect[i]->setVisible(true);
            }
        }

        if(!m_bEdit){
            emit selectedChanged(true,this,EllipseItem,QRectF(m_x,m_y,m_width,m_height),m_pointF1,m_angle);
        }

        m_bEdit = true;
        setEdit(m_bEdit);
    }else{

        painter->setPen(QPen(QBrush(m_borderColor),0));

        for(int i=0;i<m_lstRect.count();i++){
            m_lstRect[i]->setVisible(false);
        }

        if(m_bEdit){
            emit selectedChanged(false,this,EllipseItem,QRectF(m_x,m_y,m_width,m_height),m_pointF1,m_angle);
        }

        m_bEdit = false;
        setEdit(m_bEdit);

        if(directCursor != arrowsUp){
            this->scene()->views().at(0)->setCursor(viewCursor);
            directCursor = normal_rect;
        }
    }



    painter->setBrush(m_brushColor);

    painter->translate(m_width/2,m_height/2);
    painter->rotate(m_angle);
    painter->drawEllipse(QRectF(-m_width/2,-m_height/2,m_width,m_height));
    //item pos ()

    QVector<QPointF> points;
    points.append(m_pointF1);
    points.append(m_pointF2);
    points.append(m_pointF3);
    points.append(m_pointF4);

//    QPolygonF poly(points);
//    QRectF rf1(-m_width/2,-m_height/2,m_width,m_height);
//    rf1.moveTopLeft(m_pointF1);
//    rf1.moveTopRight(m_pointF2);
//    rf1.moveBottomRight(m_pointF3);
//    rf1.moveBottomLeft(m_pointF4);

//    painter->setPen(QPen(QBrush(QColor(0,0,0)),0));
//    painter->rotate(0);
//    painter->drawEllipse(rf1);

//    QPainterPath path;
//    path.addEllipse(rf1);

//    path.addEllipse(QPointF((m_pointF1.x()+m_pointF3.x())/2,(m_pointF1.y()+m_pointF3.y())/2),m_width/2,m_height/2);
//    emit signal_painterInfo(EllipseItem,path);

}

QRectF VisionEllipseItem::boundingRect() const
{
    //为方便旋转后的区域变化问题，临时的将有效区域设置为圆（直径为矩形的对角线）
    qreal r = sqrt((m_width)*(m_width)+(m_height)*(m_height));
//    QRectF rf = QRectF(-5-10+(m_width/2-r/2)-m_width/2,-5-10+(m_height/2-r/2)-m_height/2,r+20,r+20);
    QRectF rf = QRectF(-5-10,-5-10,r+20,r+20);
    return rf;
}

void VisionEllipseItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "aaa";

    //鼠标左键
    QGraphicsItem::mousePressEvent(event);

    if(m_iIndex != -1)
        return;

    //过滤掉在boundingRect但是不在绘制的有效区域的点击
    //根据椭圆定义，椭圆上任意一点，到横轴上的两个焦点距离之和等于2a
    qreal qc = sqrt(fabs((m_width/2)*(m_width/2) - (m_height/2)*(m_height/2)));
    //两个焦点需要平移到item的中心点
    qreal dx1 = event->pos().x()-(qc*cos(m_angle*pi/180)+m_width/2);
    qreal dy1 = event->pos().y()-(qc*sin(m_angle*pi/180)+m_height/2);
    qreal dx2 = event->pos().x()-(qc*cos(m_angle*pi/180+pi)+m_width/2);
    qreal dy2 = event->pos().y()-(qc*sin(m_angle*pi/180+pi)+m_height/2);
    //焦点1 (qc*cos(m_angle*pi/180),qc*cos(m_angle*pi/180))焦点2关于原点对称，因为该item的原点设置为中心点 焦点2(qc*cos(m_angle*pi/180+pi),qc*cos(m_angle*pi/180+pi))
//    qreal dx2 = event->pos().x()-qc*cos
    qreal l = sqrt(dx1*dx1+dy1*dy1)+sqrt(dx2*dx2+dy2*dy2);
    if(l <= m_height || l <= m_width){
    }else{
        setSelected(false);
        this->scene()->update();
        return;
    }


    if (event->button() == Qt::LeftButton) {
        if (event->modifiers() == Qt::ShiftModifier) {
//            qDebug() << "visionItem left clicked with SHIFT key.";
            // 选中 item
        } else if (event->modifiers() == Qt::AltModifier) {

        } else {
            setSelected(true);
            qDebug() << "Custom item left clicked.";
            QGraphicsItem::mousePressEvent(event);
            event->accept();
        }
    } else if (event->button() == Qt::RightButton) {
        event->ignore();
    }

    lastPoint = event->scenePos();
    this->setPos(m_x,m_y);
    this->scene()->update();
}

void VisionEllipseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_iIndex != -1)
        return;

    qreal qc = sqrt(fabs((m_width/2)*(m_width/2) - (m_height/2)*(m_height/2)));
    //两个焦点需要平移到item的中心点
    qreal dx1 = event->pos().x()-(qc*cos(m_angle*pi/180)+m_width/2);
    qreal dy1 = event->pos().y()-(qc*sin(m_angle*pi/180)+m_height/2);
    qreal dx2 = event->pos().x()-(qc*cos(m_angle*pi/180+pi)+m_width/2);
    qreal dy2 = event->pos().y()-(qc*sin(m_angle*pi/180+pi)+m_height/2);
    //焦点1 (qc*cos(m_angle*pi/180),qc*cos(m_angle*pi/180))焦点2关于原点对称，因为该item的原点设置为中心点 焦点2(qc*cos(m_angle*pi/180+pi),qc*cos(m_angle*pi/180+pi))
//    qreal dx2 = event->pos().x()-qc*cos
    qreal l = sqrt(dx1*dx1+dy1*dy1)+sqrt(dx2*dx2+dy2*dy2);
    if(l <= m_height || l <= m_width){
    }else{
        emit signal_clicked(this,true,false,event->scenePos().x(),event->scenePos().y());
        return;
    }
    emit signal_clicked(this,true,true,event->scenePos().x(),event->scenePos().y());
    QGraphicsItem::mouseReleaseEvent(event);

}

void VisionEllipseItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(directCursor != arrowsUp){
        if(!m_bEdit){
            return;
        }
        //计算两次move的鼠标的差值，
        //计算两次move的鼠标的差值，
        QPointF curPoint = event->scenePos();
        QPointF disPoint = curPoint - lastPoint;
        lastPoint = curPoint;
        QGraphicsItem::mouseMoveEvent(event);


        if(directCursor == normal_rect){
            m_pointF1 = m_pointF1+disPoint;
            m_pointF2 = m_pointF2+disPoint;
            m_pointF3 = m_pointF3+disPoint;
            m_pointF4 = m_pointF4+disPoint;
            m_x = m_x + disPoint.x();m_y = m_y + disPoint.y();
        }else{

            //当存在旋转的时候，计算三条线的交点，
            //获取到线的斜率
//            A = Y2 - Y1
//            B = X1 - X2
//            C = X2*Y1 - X1*Y2
            qreal a1 = (m_pointF2.y()-m_pointF1.y());
            qreal b1 = (m_pointF1.x()-m_pointF2.x());
            qreal c1 = m_pointF2.x()*m_pointF1.y() - m_pointF1.x()*m_pointF2.y();
            //线的直线方程 (m_lstRect[0]-m_lstRect[2])*x - (m_lstRect[0]-m_lstRect[2])*y - (m_lstRect[0]-m_lstRect[2])*m_lstRect[0] +(m_lstRect[0]-m_lstRect[2])*m_lstRect[0]

            qreal a2 = (m_pointF4.y()-m_pointF3.y());
            qreal b2 = (m_pointF3.x()-m_pointF4.x());
            qreal c2 = m_pointF4.x()*m_pointF3.y() - m_pointF3.x()*m_pointF4.y();


            qreal a3 = (m_pointF3.y()-m_pointF2.y());
            qreal b3 = (m_pointF2.x()-m_pointF3.x());
            qreal c3 = m_pointF3.x()*m_pointF2.y() - m_pointF2.x()*m_pointF3.y();

            qreal a4 = (m_pointF4.y()-m_pointF1.y());
            qreal b4 = (m_pointF1.x()-m_pointF4.x());
            qreal c4 = m_pointF4.x()*m_pointF1.y() - m_pointF1.x()*m_pointF4.y();

//            qDebug()<<"a1 b1: "<<a1<<b1<<" a2 b2 :"<<a2<<b2<<" a3 b3 :"<<a3<<b3<<" a4 b4 : "<<a4<<b4;
            //过鼠标所在的点的两条直线
            qreal A1 = a1; qreal B1 = b1;
            qreal C1 = - (A1)*curPoint.x() - (B1)*curPoint.y(); //和l1 l2 平行的
            //A1x+B1y+C1 = 0; la
            qreal A2 = a3; qreal B2 = b3;
            qreal C2 = - A2*curPoint.x() - B2*curPoint.y();  //和l3 l4 平行的
            //A2x+B2y+C2 = 0;  lb

            //l1:a1x+b1y+c1=0; 0-2
            //l2:a2x+b2y+c2=0; 4-6
            //l3:a3x+b3y+c3=0; 2-4
            //l4:a4x+b4y+c4=0; 6-0

            //A1x+B1x+C1=0;A2x+B2y+C2=0
            //if(A1*B2-A2*B1 != 0) 有唯一解  x=(B1*C2-B2*C1)/(A1*B2-A2*B1）  y=-(A1*C2-A2*C1)/(A1*B2-A2*B1）
            //不考虑重合和平行的情况
            //la-l3  x=(B1*c3-b3*C1)/(A1*b3-a3*B1)  y=-(A1*c3-a3*C1)/(A1*b3-a3*B1)
            //la-l4  x=(B1*c4-b4*C1)/(A1*b4-a4*B1)  y=-(A1*c4-a4*C1)/(A1*b4-a4*B1)

            //lb-l1  x=(B2*c1-b1*C2)/(A2*b1-a1*B2)  y=-(A2*c1-a1*C2)/(A2*b1-a1*B2)
            //lb-l2  x=(B2*c2-b2*C2)/(A2*b2-a2*B2)  y=-(A2*c2-a2*C2)/(A2*b2-a2*B2)

            if(directCursor == top_rect){
                //top point
                //修改点1和点2的坐标,l4 l3
                //点1坐标  la-l4
                m_pointF1 = QPointF((B1*c4-b4*C1)/(A1*b4-a4*B1),-(A1*c4-a4*C1)/(A1*b4-a4*B1));
                //点2坐标  la-l3
                m_pointF2 = QPointF((B1*c3-b3*C1)/(A1*b3-a3*B1),-(A1*c3-a3*C1)/(A1*b3-a3*B1));

            }else if(directCursor == right_rect){
                //right point
                //修改点2和点3的坐标 l1 l2
                //点2坐标  lb-l1
                m_pointF2 = QPointF((B2*c1-b1*C2)/(A2*b1-a1*B2),-(A2*c1-a1*C2)/(A2*b1-a1*B2));
                //点3坐标  lb-l2
                m_pointF3 = QPointF((B2*c2-b2*C2)/(A2*b2-a2*B2),-(A2*c2-a2*C2)/(A2*b2-a2*B2));

            }else if(directCursor == bottom_rect){
                //bottom point
                //修改点3和点4的坐标 l3 l4
                //点4坐标  la-l4
                m_pointF4 = QPointF((B1*c4-b4*C1)/(A1*b4-a4*B1),-(A1*c4-a4*C1)/(A1*b4-a4*B1));
                //点3坐标  la-l3
                m_pointF3 = QPointF((B1*c3-b3*C1)/(A1*b3-a3*B1),-(A1*c3-a3*C1)/(A1*b3-a3*B1));

            }else if(directCursor == left_rect){
                //left point
                //修改点4和点1的坐标 l1 l2
                //点1坐标  lb-l1
                m_pointF1 = QPointF((B2*c1-b1*C2)/(A2*b1-a1*B2),-(A2*c1-a1*C2)/(A2*b1-a1*B2));
                //点4坐标  lb-l2
                m_pointF4 = QPointF((B2*c2-b2*C2)/(A2*b2-a2*B2),-(A2*c2-a2*C2)/(A2*b2-a2*B2));

            }else if(directCursor == left_Top_rect){
                //left top
                //修改4，1，2的坐标

                //点1坐标 鼠标的坐标
                m_pointF1 = curPoint;
                //点4坐标  lb-l2
                m_pointF4 = QPointF((B2*c2-b2*C2)/(A2*b2-a2*B2),-(A2*c2-a2*C2)/(A2*b2-a2*B2));
                //点2坐标  la-l3
                m_pointF2 = QPointF((B1*c3-b3*C1)/(A1*b3-a3*B1),-(A1*c3-a3*C1)/(A1*b3-a3*B1));

            } else if(directCursor == left_bottom_rect){
                //left bottom
                //修改4，1，3的坐标

                //点4坐标 鼠标的坐标
                m_pointF4 = curPoint;
                //点1坐标  lb-l1
                m_pointF1 = QPointF((B2*c1-b1*C2)/(A2*b1-a1*B2),-(A2*c1-a1*C2)/(A2*b1-a1*B2));
                //点3坐标  la-l3
                m_pointF3 = QPointF((B1*c3-b3*C1)/(A1*b3-a3*B1),-(A1*c3-a3*C1)/(A1*b3-a3*B1));

            } else if(directCursor == right_top_rect){
                //right top
                //修改1,2,3的坐标

                //点2坐标 鼠标的坐标
                m_pointF2 = curPoint;
                //点1坐标  la-l4
                m_pointF1 = QPointF((B1*c4-b4*C1)/(A1*b4-a4*B1),-(A1*c4-a4*C1)/(A1*b4-a4*B1));
                //点3坐标  lb-l2
                m_pointF3 = QPointF((B2*c2-b2*C2)/(A2*b2-a2*B2),-(A2*c2-a2*C2)/(A2*b2-a2*B2));

            }else if(directCursor == right_bottom_rect){
                //right bottom
                //修改2,3,4的坐标

                //点3坐标 鼠标的坐标
                m_pointF3 = curPoint;
                //点2坐标  lb-l1
                m_pointF2 = QPointF((B2*c1-b1*C2)/(A2*b1-a1*B2),-(A2*c1-a1*C2)/(A2*b1-a1*B2));
                //点4坐标  la-l4
                m_pointF4 = QPointF((B1*c4-b4*C1)/(A1*b4-a4*B1),-(A1*c4-a4*C1)/(A1*b4-a4*B1));
            }
            else{
                qDebug()<<"error directCursor";
            }


            if(m_width < 1)
                m_width = 1;
            if(m_height < 1)
                m_height = 1;

        }
        updateBoundingRect();
        this->setPos(m_x,m_y);
        updateItem();
    }else{
//        qDebug()<<"arrow up";

        //角度计算有瑕疵，角度的变化不能完全跟随鼠标，可能是应为采用的pos坐标
        /*
        qreal x = event->pos().x();
        qreal y = event->pos().y();
        qreal z = sqrt(x*x+y*y);
        */

        qreal x = event->scenePos().x()-(m_x+m_width/2);
        qreal y = event->scenePos().y()-(m_y+m_height/2);
        qreal z = sqrt(x*x+y*y);

//        qDebug()<<event->scenePos();
        if(y >= 0){
            //第一和第二象限
            qreal alph = acos(x/z);
            m_angle = (alph*180)/3.14159;
        }else{
            //第三和第四象限
            qreal alph = acos(x/z);
            m_angle = 360 - (alph*180)/3.14159;
        }

        this->setPos(m_x,m_y);
        updateItem();
        updatePointF();
    }
    emit signalChanged(this);
    this->scene()->update();
}

void VisionEllipseItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverMoveEvent(event);
}

void VisionEllipseItem::initItem()
{
    m_lstRect.clear();

    MiniRect* miniRect1 = new MiniRect(-5,-5,10,10,QColor(255,0,0),this);
    miniRect1->setIndex(0);
    QObject::connect(miniRect1,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    MiniRect* miniRect2 = new MiniRect(-5+m_width/2,-5,10,10,QColor(255,0,0),this);
    miniRect2->setIndex(1);
    miniRect2->setParent(this);
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


    m_lstRect.append(miniRect1);
    m_lstRect.append(miniRect2);
    m_lstRect.append(miniRect3);
    m_lstRect.append(miniRect4);
    m_lstRect.append(miniRect5);
    m_lstRect.append(miniRect6);
    m_lstRect.append(miniRect7);
    m_lstRect.append(miniRect8);

}

void VisionEllipseItem::updateItem()
{
//    qDebug()<<m_x<<m_y<<m_width<<m_height;
    qreal x;
    qreal y;
    QRectF rf = boundingRect();
    //由于当w和h变化的时候，对于的对角线的角度就会变好，
    qreal angle = atan(m_height/m_width);
    qreal r = sqrt((m_width/2)*(m_width/2)+(m_height/2)*(m_height/2));

    if(arrowsItem != NULL){
        qreal w1 = arrowsItem->boundingRect().width();
        qreal h1 = arrowsItem->boundingRect().height();
        qreal x1 = (m_width/2+w1/2)*cos(m_angle*pi/180)+m_width/2;
        qreal y1 = (m_width/2+w1/2)*sin(m_angle*pi/180)+m_height/2;
        //update arrowItem
        arrowsItem->setPos(m_width/2,m_height/2);
        arrowsItem->setRotation(m_angle);
    }


    //update miniRect
    for(int i=0;i<m_lstRect.count();i++){

        if(i == 0){
            x = r*cos(angle+pi+m_angle*pi/180)+m_width/2;
            y = r*sin(angle+pi+m_angle*pi/180)+m_height/2;

        }else if(i == 1){
            x = (m_height/2)*cos(pi*3/2+m_angle*pi/180)+m_width/2;
            y = (m_height/2)*sin(pi*3/2+m_angle*pi/180)+m_height/2;

        }else if(i == 2){
            x = r*cos(2*pi-angle+m_angle*pi/180)+m_width/2;
            y = r*sin(2*pi-angle+m_angle*pi/180)+m_height/2;

        }else if(i == 3){
            x = (m_width/2)*cos(m_angle*pi/180)+m_width/2;
            y = (m_width/2)*sin(m_angle*pi/180)+m_height/2;

        }else if(i == 4){
            x = r*cos(angle+m_angle*pi/180)+m_width/2;
            y = r*sin(angle+m_angle*pi/180)+m_height/2;

        }else if(i == 5){
            x = (m_height/2)*cos(pi/2+m_angle*pi/180)+m_width/2;
            y = (m_height/2)*sin(pi/2+m_angle*pi/180)+m_height/2;

        }else if(i == 6){
            x = r*cos(pi-angle+m_angle*pi/180)+m_width/2;
            y = r*sin(pi-angle+m_angle*pi/180)+m_height/2;

        }else if(i == 7){
            x = (m_width/2)*cos(pi+m_angle*pi/180)+m_width/2;
            y = (m_width/2)*sin(pi+m_angle*pi/180)+m_height/2;

        }
        m_lstRect[i]->setPos(x-5,y-5);
        m_lstRect[i]->setRotation(m_angle);
    }


}

void VisionEllipseItem::updatePointF()
{
    //m_lstRect中的四个顶点是基于this的坐标，换算需要和m_x,m_y进行换算
    m_pointF1 = QPointF(m_lstRect[0]->pos().x()+5+m_x,m_lstRect[0]->pos().y()+5+m_y);
    m_pointF2 = QPointF(m_lstRect[2]->pos().x()+5+m_x,m_lstRect[2]->pos().y()+5+m_y);
    m_pointF3 = QPointF(m_lstRect[4]->pos().x()+5+m_x,m_lstRect[4]->pos().y()+5+m_y);
    m_pointF4 = QPointF(m_lstRect[6]->pos().x()+5+m_x,m_lstRect[6]->pos().y()+5+m_y);
}

void VisionEllipseItem::updateBoundingRect()
{
    //已经在旋转后进行了换算
    //获取中心点，两条对角线的交点，
    QPointF centerPointF = QPointF((m_pointF1.x()+m_pointF3.x())/2,(m_pointF1.y()+m_pointF3.y())/2);
    qreal w = sqrt((m_pointF1.x()-m_pointF2.x())*(m_pointF1.x()-m_pointF2.x())+(m_pointF1.y()-m_pointF2.y())*(m_pointF1.y()-m_pointF2.y()));
    qreal h = sqrt((m_pointF1.x()-m_pointF4.x())*(m_pointF1.x()-m_pointF4.x())+(m_pointF1.y()-m_pointF4.y())*(m_pointF1.y()-m_pointF4.y()));
    m_x = centerPointF.x()-w/2;
    m_y = centerPointF.y()-h/2;
    m_width = w;
    m_height = h;

    //在此处将QRectF rf = QRectF(m_x,m_y,m_width,m_height)绘制出来，会发现，和旋转后的反旋转是一直的，我对旋转的角度是有记录的，所以在此时，直接绘制rf在旋转角度，会得到
    //直接绘制四个点连线的矩形是一样的---（用途，绘制矩形的内切圆的时候需要在旋转的情况下，转换成未旋转的数据，绘制出来后，在进行对应角度的进行旋转）
}

void VisionEllipseItem::slotIndex(int index)
{
    //可以将对于的miniRect的鼠标样式修改下
//    qDebug()<<"click miniRect : "<<index;
    m_bCircle = false;
    QMatrix leftmatrix;
    leftmatrix.rotate(m_angle);
    QCursor cursor;

    m_iIndex = index;

    if(index == 7){
        //left
        directCursor = left_rect;
        cursor = QCursor(QPixmap(iconPath+"cursor-sizeh.png").transformed(leftmatrix,Qt::SmoothTransformation));
        this->scene()->views().at(0)->setCursor(cursor);

    }else if(index == 1){
        //top
        directCursor = top_rect;
        cursor = QCursor(QPixmap(iconPath+"cursor-sizev.png").transformed(leftmatrix,Qt::SmoothTransformation));
        this->scene()->views().at(0)->setCursor(cursor);

    }else if(index == 3){
        //right
        directCursor = right_rect;
        cursor = QCursor(QPixmap(iconPath+"cursor-sizeh.png").transformed(leftmatrix,Qt::SmoothTransformation));
        this->scene()->views().at(0)->setCursor(cursor);

    }else if(index == 5){
        //bottom
        directCursor = bottom_rect;
        cursor = QCursor(QPixmap(iconPath+"cursor-sizev.png").transformed(leftmatrix,Qt::SmoothTransformation));
        this->scene()->views().at(0)->setCursor(cursor);

    }else{
        m_iIndex = -1;
        directCursor = normal_rect;
        this->scene()->views().at(0)->setCursor(viewCursor);
    }
}

void VisionEllipseItem::slotArrowsItem()
{
    directCursor = arrowsUp;
    m_bCircle = true;
}

void VisionEllipseItem::slotArrowsItem_leave()
{
    directCursor = normal_rect;
    m_bCircle = false;
}

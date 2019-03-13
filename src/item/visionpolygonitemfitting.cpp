#include "visionpolygonitemfitting.h"
#include <QDebug>
#include "../control/color.h"

#define Pi 3.1415926


VisionPolygonItemFitting::VisionPolygonItemFitting(bool close, bool edit, qreal length, bool color_enable,QColor color, VisionItem *parent) : VisionItem(parent)
{
    if(color_enable){
        m_borderColor = color;
    }else{
        m_borderColor = borderColor;
    }
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;

    m_bFitting = true;
    m_length = length;

    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    m_type = ItemType::Paint_Poly;
    m_bEdit = edit;
    if(m_bEdit){
        setSelectedStatus(true);
    }else{
        setSelectedStatus(false);
    }
    m_bClose = close;
}

VisionPolygonItemFitting::~VisionPolygonItemFitting()
{

}

void VisionPolygonItemFitting::setPointFs(QVector<QPointF> pointFs, bool bFinished)
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


bool VisionPolygonItemFitting::getPosInArea(qreal x, qreal y)
{
    if(m_polygonF_temp.containsPoint(this->mapFromScene(QPointF(x,y)),Qt::OddEvenFill)){
        return true;
    }else{
        return false;
    }
}


void VisionPolygonItemFitting::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    if(option->state & QStyle::State_Selected){

        painter->setPen(QPen(QBrush(m_selectedColor),0));

        if(m_bEdit){
            for(int i=0;i<m_lstRect.count();i++){
                m_lstRect[i]->show();
            }
        }

        emit selectedChanged(true,this,ItemType::Paint_Poly,m_vecPointFs);

        m_bSelected = true;
        setSelectedStatus(m_bSelected);

    }else{
        painter->setPen(QPen(QBrush(m_borderColor),0));

        for(int i=0;i<m_lstRect.count();i++){
            m_lstRect[i]->hide();
        }

        //通知view将该item转换为区域 ---
        //由选中状态变为非选中状态，由于，构造函数默认为选中状态，故当item为未选中状态，则必定是由选中状态变为未选中状态，直接传输信号通知
        //前提是item是可编辑的
        if(m_bEdit){
            emit selectedChanged(false,this,ItemType::Paint_Poly,m_vecPointFs);
        }
        m_bSelected = false;
        setSelectedStatus(m_bSelected);
    }

    if(m_bClose){
//        painter->setBrush(m_brushColor);
        painter->drawPolygon(m_polygonF_temp);
    }else{
        painter->drawPolyline(m_polygonF_temp);
    }

    painter->setBrush(m_brushColor);

    for(int i=0;i<m_lstPoly.count();i++){
        painter->drawPolygon(m_lstPoly[i]);
    }

    painter->setPen(QPen(QBrush(Qt::green),0));
    painter->drawPolygon(m_poly);
//    painter->drawPolygon(QPolygonF(m_lstPointF));

    painter->setPen(QPen(QBrush(Qt::blue),0));
//    painter->drawPolygon(QPolygonF(m_lstPointF1));

    if(m_bSelected){
        QPainterPath path;
        path.addPolygon(m_polygonF);
        emit signal_painterInfo(ItemType::Paint_Poly,path);
    }

}

QRectF VisionPolygonItemFitting::boundingRect() const
{
    QRectF rf;
    if(m_lstPointF1.count() <= 0){
        rf = QRectF(m_polygonF_temp.boundingRect().x()-5,m_polygonF_temp.boundingRect().y()-5,
                          m_polygonF_temp.boundingRect().width()+10,m_polygonF_temp.boundingRect().height()+10);
    }else{
        rf = QPolygonF(m_lstPointF).boundingRect();
    }
    return rf;
}


void VisionPolygonItemFitting::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_bFitting = false;

    if(!m_bEdit)
        return;

    QGraphicsItem::mousePressEvent(event);

    m_lastPointF = event->scenePos();

    //鼠标属于非正常状态--拖动小矩形框，当鼠标在编辑框状态，不处理按下事件，此时只需要处理moveEvent事件即可
    if(m_iIndex != -1)
        return;

    if(m_polygonF_temp.containsPoint(event->pos(),Qt::OddEvenFill)){
//        qDebug()<<" mouse press Event : true";
        setSelectedStatus(true);
    }else{
        setSelectedStatus(false);
//        qDebug()<<" mouse press Event false";
    }
    this->scene()->update();
}

void VisionPolygonItemFitting::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    if(m_iIndex != -1)
        return;

    if(!m_polygonF_temp.containsPoint(event->pos(),Qt::OddEvenFill)){
        emit signal_clicked(this,true,false,event->scenePos().x(),event->scenePos().y());
        return;
    }
    emit signal_clicked(this,true,true,event->scenePos().x(),event->scenePos().y());
    QGraphicsItem::mouseReleaseEvent(event);

}

void VisionPolygonItemFitting::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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

    updateData();
    emit signalChanged(this);
    this->scene()->update();
}

void VisionPolygonItemFitting::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(m_bFitting){
        m_length = getMinDistance(m_vecPointFs,m_bClose,event->scenePos());
        qDebug()<<m_length;

        m_poly.clear();
        m_lstPoly.clear();
        m_poly = getPolygonLineFitting(m_vecPointFs_temp,m_bClose,m_length);
        this->scene()->update();
    }
}

void VisionPolygonItemFitting::initMiniRect()
{
    m_lstRect.clear();
    for(int i=0;i<m_vecPointFs_temp.count();i++){
        MiniRect* miniRect = new MiniRect(m_vecPointFs_temp.at(i).x()-5,m_vecPointFs_temp.at(i).y()-5,10,10,QColor(255,0,0),this);
        miniRect->setIndex(i);
        connect(miniRect,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));
        miniRect->hide();
        m_lstRect.append(miniRect);
    }
}

void VisionPolygonItemFitting::updateMiniRect()
{
    for(int i=0;i<m_vecPointFs_temp.count();i++){
        m_lstRect[i]->setPos(m_vecPointFs_temp.at(i).x()-5,m_vecPointFs_temp.at(i).y()-5);
    }
}




qreal VisionPolygonItemFitting::getMinDistance(QVector<QPointF> vec_p, bool close, QPointF p)
{
    qreal l = 1000;
    for(int i=0;i<vec_p.count()-1;i++){
        qreal l1 = getDistance(vec_p[i],vec_p[i+1],p);
        if(l1 < l){
            l = l1;
        }
    }
    if(close){
        qreal l1 = getDistance(vec_p.last(),vec_p.first(),p);
        if(l1 < l){
            l = l1;
        }
    }
    return l;
}

qreal VisionPolygonItemFitting::getDistance(QPointF p1, QPointF p2, QPointF p)
{
    qreal A = p2.y() - p1.y();
    qreal B = p1.x() - p2.x();
    qreal C = p2.x()*p1.y() - p1.x()*p2.y();
    qreal l = fabs(A*p.x() + B*p.y() + C)/sqrt(A*A+B*B);
    return l;
}

QPolygonF VisionPolygonItemFitting::getPolygonLineFitting(QVector<QPointF> vec_p, bool close, qreal length)
{

    m_lstPointF.clear();
    m_lstPointF1.clear();
    m_lstLineStruct.clear();
//    QList<QPointF> lstP1;
//    QList<QPointF> lstP2;

    QVector<QPointF> vecP;
    vecP.clear();
    QPolygonF poly;
    poly.clear();

    if(vec_p.count() <= 1)
        return poly;

    if(!close){
        //非封闭的图形
        //获取首尾两个点的半圆
        //n个点--  n-1直线 -- n-2圆弧
        for(int i=0;i<vec_p.count()-1;i++){
            m_lstPoly.append(getLineCircle(vec_p.at(i),vec_p.at(i+1),length));
        }
        //获取到所有的点
        //处理获取到的点的集合
        //如果就一个，则直接结束
        if(m_lstLineStruct.count() <= 0){
            return poly;
        }else if(m_lstLineStruct.count() == 1){

        }else{
            for(int i=0;i<m_lstLineStruct.count()-1;i++){
                m_lstLineStruct[i] = detailLine(m_lstLineStruct[i],m_lstLineStruct[i+1]);
            }
        }

    }else{
        //封闭的图形
        //n个点--  n直线 -- n圆弧
        for(int i=0;i<vec_p.count()-1;i++){
            m_lstPoly.append(getLineCircle(vec_p.at(i),vec_p.at(i+1),length));
        }
        m_lstPoly.append(getLineCircle(vec_p.at(vec_p.count()-1),vec_p.first(),length));
    }

    poly.append(vecP);
    return poly;
}

QPolygonF VisionPolygonItemFitting::getLineCircle(QPointF p1, QPointF p2, qreal length)
{
    //获取  过点P1和点P2两条和P1P2线垂直的两条直线，分别和与线P1P2平行并且垂直距离为length的交点
    qreal A = p2.y() - p1.y();
    qreal B = p1.x() - p2.x();
    qreal C = p2.x()*p1.y() - p1.x()*p2.y();

    //直线l，获取以两点为圆心，将l平移length后，和两点为圆心的圆相切的点的坐标
    //l1: Ax+By+C11=0  (C11:+- √(length*length *(A*A+B*B)) -(Ax1+By1);  lo:Bx-Ay+C1=0;(C1:Ay1-Bx1)--x1,y1点p1的坐标。  l1和lo的交点即为切点
    //l1和l0可以得到两个交点   Ax+By+C=0  Bx-Ay+C1=0   x=-(A*C+B*C1)/(A*A+B*B)  y=-(B*C-A*C1)/(A*A+B*B)
    qreal C11 = -sqrt(length*length *(A*A+B*B)) -(A*p1.x()+B*p1.y());
    qreal C12 = sqrt(length*length *(A*A+B*B)) -(A*p1.x()+B*p1.y());
    qreal C1 = A*p1.y()-B*p1.x();
    QPointF tempP1 = QPointF(-(A*C11+B*C1)/(A*A+B*B),-(B*C11-A*C1)/(A*A+B*B));
    QPointF tempP2 = QPointF(-(A*C12+B*C1)/(A*A+B*B),-(B*C12-A*C1)/(A*A+B*B));

    qreal C21 = -sqrt(length*length *(A*A+B*B)) -(A*p2.x()+B*p2.y());
    qreal C22 = sqrt(length*length *(A*A+B*B)) -(A*p2.x()+B*p2.y());
    qreal C2 = A*p2.y()-B*p2.x();
    QPointF tempP3 = QPointF(-(A*C21+B*C2)/(A*A+B*B),-(B*C21-A*C2)/(A*A+B*B));
    QPointF tempP4 = QPointF(-(A*C22+B*C2)/(A*A+B*B),-(B*C22-A*C2)/(A*A+B*B));
    qDebug()<<QPolygonF({tempP1,tempP2,tempP4,tempP3});

    //定位p1,p2和p3,p4分别的对应的点
    //2-3和1-4两条线相交的话，则 1,3;2,4;  -- 此处已经确认分组是没问题的，
    //谁在前，谁在后
    m_lstPointF.append({tempP1,tempP3});
    m_lstPointF1.append({tempP2,tempP4});
    Line_Struct lineStruct;
    lineStruct.line1 = QLineF(tempP1,tempP3);
    lineStruct.line2 = QLineF(tempP2,tempP4);

    QLineF line = QLineF(p1,p2);
    lineStruct.line = line;
    m_lstLineStruct.append(lineStruct);


    return QPolygonF({tempP1,tempP2,tempP4,tempP3});
}

Line_Struct VisionPolygonItemFitting::detailLine(Line_Struct lineStruct1, Line_Struct lineStruct2)
{
    //lineStruct1相对lineStruct2；
    //获取line的x，y范围
    QLineF line = lineStruct2.line;
    qreal minX,maxX,minY,maxY;
    if(line.p1().x() < line.p2().x()){
        minX = line.p1().x();
        maxX = line.p2().x();
    }
    if(line.p1().y() < line.p2().y()){
        minY = line.p1().y();
        maxY = line.p2().y();
    }

    //line1和line的交点
    QPointF p1 = getLineCrossP(lineStruct1.line1.p1(),lineStruct1.line1.p2(),lineStruct2.line.p1(),lineStruct2.line.p2());
    //line2和line的交点
    QPointF p2 = getLineCrossP(lineStruct1.line2.p1(),lineStruct1.line2.p2(),lineStruct2.line.p1(),lineStruct2.line.p2());

    Line_Struct lineStu1;
    if((p1.x() <= maxX && p1.x() >= minX) && (p1.y() <= maxY && p1.y() >= minY)){
        //lineStruct1的line1与lineStruct2的line相交在线上
        lineStu1.line1 = lineStruct1.line2;
        lineStu1.line2 = lineStruct1.line1;
    }else if((p2.x() <= maxX && p2.x() >= minX) && (p2.y() <= maxY && p2.y() >= minY)){
        //lineStruct1的line2与lineStruct2的line相交在线上
        lineStu1.line1 = lineStruct1.line1;
        lineStu1.line2 = lineStruct1.line2;
    }else{
        lineStu1.line1 = lineStruct1.line1;
        lineStu1.line2 = lineStruct1.line2;
    }

    //lineStruct2相对lineStruct1；
    //line1和line的交点
//    QPointF p_1 = getLineCrossP(lineStruct2.line1.p1(),lineStruct2.line1.p2(),lineStruct1.line.p1(),lineStruct1.line.p2());
//    //line2和line的交点
//    QPointF p_2 = getLineCrossP(lineStruct2.line2.p1(),lineStruct2.line2.p2(),lineStruct1.line.p1(),lineStruct1.line.p2());

//    Line_Struct lineStu2;
//    if((p_1.x() <= maxX && p_1.x() >= minX) && (p_1.y() <= maxY && p_1.y() >= minY)){
//        //lineStruct1的line1与lineStruct2的line相交在线上
//        lineStu2.line1 = lineStruct2.line2;
//        lineStu2.line2 = lineStruct2.line1;
//    }else if((p_2.x() <= maxX && p_2.x() >= minX) && (p_2.y() <= maxY && p_2.y() >= minY)){
//        //lineStruct1的line2与lineStruct2的line相交在线上
//        lineStu2.line1 = lineStruct2.line1;
//        lineStu2.line2 = lineStruct2.line2;
//    }else{
//        lineStu2.line1 = lineStruct2.line1;
//        lineStu2.line2 = lineStruct2.line2;
//    }

    return lineStu1;
}

QPolygonF VisionPolygonItemFitting::drawArc(QPointF sP, QPointF fP, QPointF center, qreal r)
{
    //三点确定一个圆,硬解，可得到表达式（三点一线的时候，则无法形成圆）
    double x1 = sP.x(), x2 = fP.x();
    double y1 = sP.y(), y2 = fP.y();


    double x0 = center.x();
    double y0 = center.y();

    //计算每个点和圆心所形成的的角度
    double angle1 = acos((x1-x0)/(hypot((x1-x0),(y1-y0))));
    double angle2 = acos((x2-x0)/(hypot((x2-x0),(y2-y0))));
    if(y1-y0 < 0){
        angle1 = 2*Pi - angle1;
    }else{
        angle1 = angle1;
    }

    if(y2-y0 < 0){
        angle2 = 2*Pi - angle2;
    }else{
        angle2 = angle2;
    }

    //上面计算的角度是基于QGraphicsView中的坐标，需要进行转换为数学坐标中的角度
    angle1 = 360-angle1*180/Pi;
    angle2 = 360-angle2*180/Pi;

    qDebug()<<angle1<<angle2;

    qreal angle;
    qreal spanAngle;

    QPainterPath path;
    if(angle1 < angle2){
        //1是起点，2是终点
        angle = angle1;
        spanAngle = angle2 - angle1;
    }else{
        //2是起点，1是终点
        angle = angle2;
        spanAngle = angle1 - angle2;
    }
    path.arcTo(center.x()-r,center.y()-r,2*r,2*r,angle,spanAngle);

    return path.toFillPolygon();
}

QPointF VisionPolygonItemFitting::getLineCrossP(QPointF p1, QPointF p2, QPointF p3, QPointF p4)
{
    qreal A1 = p2.y() - p1.y();
    qreal B1 = p1.x() - p2.x();
    qreal C1 = p2.x()*p1.y() - p1.x()*p2.y();

    qreal A2 = p4.y() - p3.y();
    qreal B2 = p3.x() - p4.x();
    qreal C2 = p4.x()*p3.y() - p3.x()*p4.y();

    //如果平行的话，没有交点，直接返回p4
    if(A1*B2-A2*B1 == 0)
        return p4;

    return QPointF((B1*C2-B2*C1)/(A1*B2-A2*B1),((A1*C2-A2*C1)/(A2*B1-A1*B2)));
}

void VisionPolygonItemFitting::updateData()
{
    m_poly.clear();
    m_lstPoly.clear();
    m_poly = getPolygonLineFitting(m_vecPointFs_temp,m_bClose,m_length);
//    this->scene()->update();
}



void VisionPolygonItemFitting::slotIndex(int index)
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

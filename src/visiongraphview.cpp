﻿#include "visiongraphview.h"
#include <QScrollBar>
#include "qdebug.h"
#include "visiongraphscene.h"
#include "./control/color.h"

#include "XVCreateRegion.h"
#include "XVCombineRegions.h"

#define Pi 3.1415926

VisionGraphView::VisionGraphView(QWidget *parent):
    QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff);
    this->setMouseTracking(true);//捕捉鼠标移动信息
    m_pMouseInfo_Label = new QLabel(this);
    m_pMouseInfo_Label->resize(120,50);
    m_pMouseInfo_Label->setStyleSheet("background-color:gray;color:black;");
    m_pMouseInfo_Label->hide();

    m_pLabelInfo = new QLabel(this);
    m_pLabelInfo->move(2,2);
    m_pLabelInfo->resize(150,70);
    m_pLabelInfo->setAlignment(Qt::AlignCenter);
    m_pLabelInfo->setStyleSheet("background-color:#ADD8E699;color:green;");
//    m_pLabelInfo->setText("View Infomation show");
    m_pLabelInfo->hide();

    setItemType(ItemType::No);

    connect(this,SIGNAL(signal_wheelEevent(QWheelEvent*)),this,SLOT(slot_wheelEvent(QWheelEvent*)));

    m_lib_XVRegionAnalysis.setFileName("XVRegionAnalysis");
    if(!m_lib_XVRegionAnalysis.load())
    {
        qDebug() << "load library failed";
        qDebug() << m_lib_XVRegionAnalysis.errorString();
    }

}

void VisionGraphView::setGraphType(GraphType type)
{
    m_graphType = type;
}

void VisionGraphView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint viewPos = event->pos();//获取视口坐标
    QPointF scenePos = this->mapToScene(viewPos);//将视口坐标转换为场景坐标

    emit signal_Move(viewPos);
    m_movePointF = viewPos;

    //show mouse info
    if(!m_pLabelInfo->isHidden()){
        QString text_pos="";
        QString text_rgb="";
        QString text_gray="";
        text_pos = (QStringLiteral("坐标:(")+QString::number(scenePos.x())+","+QString::number(scenePos.y())+")\n");
        //todo 采用截图的方式，获取坐标点的图片，然后获取rgb值（可优化?）
        QPixmap pixmap = this->grab(QRect(QPoint(viewPos),QSize(-1,-1)));
        if (!pixmap.isNull())
        {
            QImage image = pixmap.toImage();//将像素图转换为QImage
            if (!image.isNull()) //如果image不为空
            {
                if (image.valid(0, 0)) //坐标位置有效
                {
                    QColor color = image.pixel(0, 0);
                    text_rgb = QString("RGB: %1, %2, %3").arg(color.red()).arg(color.green()).arg(color.blue());
                    int grayValue = (color.red()*30+color.green()*59+color.blue()*11)/100;
                    text_gray = QString("Gray: %1,%2,%3").arg(grayValue).arg(grayValue).arg(grayValue);
                }
            }
        }
        m_pLabelInfo->setText(text_pos+"\n"+text_rgb+"\n"+text_gray);
    }

    //拖动
    if(m_bPress_Drag && m_itemType == ItemType::Drag){
        QPointF disPointF = scenePos - (this->mapToScene(m_lastPointF.toPoint()));
        m_lastPointF = viewPos;
//        qDebug()<<disPointF;
        this->scene()->setSceneRect(this->scene()->sceneRect().x()-disPointF.x(),this->scene()->sceneRect().y()-disPointF.y(),
                                    this->scene()->sceneRect().width(),this->scene()->sceneRect().height());
//        qDebug()<<this->scene()->sceneRect();
//        this->scene()->update();
        return;
    }

    //2.修改在点击选择选项的时候，item在选中情况下无法move    m_itemType != ItemType::No的原因
    if(m_bPainter && m_bPress && m_itemType != ItemType::No){
        detailMoveEvent(event);  //事件处理函数
    }else{
        if(m_itemType != ItemType::Drag){
            //鼠标在没有按下的情况下，鼠标拖动事件也屏蔽掉item部分
            QGraphicsView::mouseMoveEvent(event);
        }
    }

    m_lastPointF = viewPos;

}

void VisionGraphView::mousePressEvent(QMouseEvent *event)
{
    QPoint viewPos = event->pos();//获取视口坐标
    QPointF scenePos = this->mapToScene(viewPos);//将视口坐标转换为场景坐标

    //当前只存在两种模式
    //第一次按下开始，第二次按下结束
    //第一次按下开始，直到双击或者右击结束或者一定数量的单击结束
    //
    m_pressPointF = viewPos;
    m_pressPointF_scene = scenePos;

    if(m_itemType == ItemType::Drag){
        m_bPress_Drag = true;
        return;
    }

    QGraphicsView::mousePressEvent(event);

    if(m_itemType == ItemType::No || m_itemType == ItemType::Zoom){
        //非绘制模式的时候，直接return
        return;
    }

    if(m_bPainter){
        //View是绘制item模式下
        detailPressEvent(event);
    }
    this->scene()->update();
}

void VisionGraphView::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint viewPos = event->pos();//获取视口坐标
    QPointF scenePos = this->mapToScene(viewPos);//将视口坐标转换为场景坐标
    m_releasePointF = viewPos;

    if(m_itemType == ItemType::Drag){
        m_bPress_Drag = false;
        return;
    }

    QGraphicsView::mouseReleaseEvent(event);

    if(m_bPainter){
        if(m_itemType == ItemType::Paint_Point || m_itemType == ItemType::Paint_NoPoint){
            //对于鼠标绘制，鼠标释放为一次记录
            push_region(m_region);
        }else if(m_itemType == ItemType::Paint_Region){
            //鼠标释放后，将鼠标绘制的任意区域转换成算法提供的区域
            XVRegion region = createPolygon(this->mapToScene(m_path).toFillPolygon());
            m_region = slot_CombineRegion(m_region,region,XVCombineRegionsType::Union);
            push_region(m_region);
            analysis_region(m_region);

            m_bPress = false;  //绘制结束
            setItemType(ItemType::No);

            QPainterPath path;
            m_path = path;
            m_vecPoint_Region.clear();
            this->scene()->update();

        }
    }
    m_lstPoint.clear();
}

void VisionGraphView::wheelEvent(QWheelEvent *event)
{
    emit signal_wheelEevent(event);
}

void VisionGraphView::enterEvent(QEvent *event)
{

    if(m_itemType == ItemType::Drag)
        return;

    QGraphicsView::enterEvent(event);

    if(m_itemType != ItemType::No){
        if(m_itemType == ItemType::Paint_Point || m_itemType == ItemType::Paint_NoPoint){
            //修改鼠标为绘图样式
            QCursor cursor = QCursor(QPixmap(iconPath+"cursor-size_Circle.png").scaled(m_qCircleR*2*m_scale,m_qCircleR*2*m_scale,
                                                                                       Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
            this->setCursor(cursor);
        }else if(m_itemType == ItemType::Drag){
            //拖动
            this->setCursor(Qt::OpenHandCursor);
        }else if(m_itemType == ItemType::Zoom){
            //缩放
            QCursor cursorIn = QCursor(QPixmap(iconPath+"cursor-zoomIn.png"));
            QCursor cursorOut = QCursor(QPixmap(iconPath+"cursor-zoomOut.png"));

            if(m_bZoom){
                this->setCursor(cursorIn);
            }else{
                this->setCursor(cursorOut);
            }
        }else{
            //其他绘制形状
            this->setCursor(Qt::CrossCursor);
        }
    }else{
        this->setCursor(Qt::ArrowCursor);
    }
    viewCursor = this->cursor();

}

void VisionGraphView::leaveEvent(QEvent *event)
{
    m_pMouseInfo_Label->hide();
}

#include <QTime>
#include <QPaintEvent>
void VisionGraphView::paintEvent(QPaintEvent *event)
{
//    QTime time;
//    time.start();

    QGraphicsView::paintEvent(event);

    QWidget *widget = this->viewport();
    if(widget == NULL)
        return;
    QPainter painter(widget);
    painter.setRenderHint(QPainter::Antialiasing,true);
    if(m_bFrameVisible){
        painter.setPen(QPen(m_FrameColor,0));
        painter.drawPolygon(this->mapFromScene(m_frameRect));
    }


//    QList<QLineF> lstLineF;
//    for(int i=0;i<200000;i++){
////        VisionLine* item = new VisionLine();
////        item->setLine(QLineF(50,50+i,150,50+i));
////        mScene->addItem(item);

//        QLineF lineF = QLineF(50,50+i,150,50+i);
//        lstLineF.append(lineF);
//    }
//    painter.drawLines(lstLineF.toVector());
//    qDebug()<<"111111111111111: "<<time.elapsed();
//    return;

    if(isCoordinate){
        //绘制交叉的坐标系
        int m_iLength = 50;
        painter.drawLine(this->mapFromScene(QPointF(0,0)),this->mapFromScene(QPointF(0+m_iLength,0)));
        painter.drawLine(this->mapFromScene(QPointF(0+m_iLength,0)),this->mapFromScene(QPointF(0+m_iLength-3,0-2)));
        painter.drawLine(this->mapFromScene(QPointF(0+m_iLength,0)),this->mapFromScene(QPointF(0+m_iLength-3,0+2)));

        painter.drawLine(this->mapFromScene(QPointF(0,0)),this->mapFromScene(QPointF(0,0+m_iLength)));
        painter.drawLine(this->mapFromScene(QPointF(0,0+m_iLength)),this->mapFromScene(QPointF(0-2,0+m_iLength-3)));
        painter.drawLine(this->mapFromScene(QPointF(0,0+m_iLength)),this->mapFromScene(QPointF(0+2,0+m_iLength-3)));
    }

    if(m_clearAll){
        m_clearAll = false;
    }

    painter.setPen(QPen(m_borderColor,0));  //区域采用填充的颜色，原因自己想
    if(m_graphType == GraphType::graphRegion){
        painter.setBrush(m_brushColor);
    }
    painter.drawPath(m_path);


//    time.start();
    painter.setPen(QPen(m_brushColor,0));  //区域采用填充的颜色，原因自己想
    QVector<QLineF> vecLines;
    for(int i=0;i<m_vecLines.size();i++){
//        qDebug()<<this->mapFromScene(m_vecLines.at(i).p1());
        QLineF lineF = QLineF(this->mapFromScene(m_vecLines.at(i).p1()),this->mapFromScene(m_vecLines.at(i).p2()));
        vecLines.append(lineF);
        painter.drawLine(lineF);
    }
    painter.drawLines(vecLines);
//    qDebug()<<"1111111111111: "<<time.elapsed()<<"  size: "<<m_vecLines.count();

    //绘制list region
    vector<XVPointRun> vec_point;
    for(int i=0;i<m_lstRegion.count();i++){
        vec_point.clear();
        vec_point = m_lstRegion[i].region.arrayPointRun;
        painter.setPen(QPen(m_lstRegion[i].color,0));
        XVPointRun pointRun;
        for(int i=0;i<vec_point.size();i++){
            pointRun = vec_point.at(i);
            painter.drawLine(this->mapFromScene(QPointF(pointRun.x,pointRun.y).toPoint()),
                             this->mapFromScene(QPointF(pointRun.x+pointRun.length,pointRun.y).toPoint()));
        }
    }


    //绘制不可编辑的region
    painter.setPen(QPen(m_brushColor_unEdit,0));  //非编辑区域有自己的颜色
    QVector<QLineF> vecLines_unEdit;
    for(int i=0;i<m_vecLines_unEdit.size();i++){
//        qDebug()<<this->mapFromScene(m_vecLines.at(i).p1());
        QLineF lineF = QLineF(this->mapFromScene(m_vecLines_unEdit.at(i).p1()),this->mapFromScene(m_vecLines_unEdit.at(i).p2()));
        vecLines_unEdit.append(lineF);
    }
    painter.drawLines(vecLines_unEdit);

}

void VisionGraphView::setItemType(ItemType type){

    //当ItemType为paint类型的时候，
    if(type == ItemType::No || type == ItemType::Zoom || type == ItemType::Drag){
        m_bPainter = false;
        m_bPress = false;  //绘制结束
    }else{
        m_bPainter = true;
    }
    m_itemType = type;

    m_vecPoint_Poly.clear();  //记录多边形的操作的点
    m_vecPoint_Region.clear();  //记录任意区域的操作的点

    if(m_itemType != ItemType::No){
        if(m_itemType == ItemType::Paint_Point || m_itemType == ItemType::Paint_NoPoint){
            //修改鼠标为绘图样式
            QCursor cursor = QCursor(QPixmap(iconPath+"cursor-size_Circle.png").scaled(m_qCircleR*2*m_scale,m_qCircleR*2*m_scale,
                                                                                       Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
            this->setCursor(cursor);
        }else if(m_itemType == ItemType::Drag){
            //拖动
            this->setCursor(Qt::OpenHandCursor);
        }else if(m_itemType == ItemType::Zoom){
            //缩放
            QCursor cursorIn = QCursor(QPixmap(iconPath+"cursor-zoomIn.png"));
            QCursor cursorOut = QCursor(QPixmap(iconPath+"cursor-zoomOut.png"));

            if(m_bZoom){
                this->setCursor(cursorOut);
                m_bZoom = false;
            }else{
                this->setCursor(cursorIn);
                m_bZoom = true;
            }

        }else{
            //其他绘制形状
            this->setCursor(Qt::CrossCursor);
        }
    }else{
        this->setCursor(Qt::ArrowCursor);
    }
    viewCursor = this->cursor();
}

void VisionGraphView::zoom(float scaleFactor)
{
    qreal scaleTemp = scaleFactor/m_scale;  //获取本次缩放相对于上次缩放的比例
    m_scale = scaleFactor;

    scale(scaleTemp, scaleTemp);
    //解决放大和缩小后，将scene的画布区域设置为view的区域，（view的区域转换为scene区域）
     //缩放后会自动调整scene的区域和view区域一致大小，使得scene不会由于缩放导致出现scroll
    this->scene()->setSceneRect(this->mapToScene(this->rect()).boundingRect());


    if(m_itemType == ItemType::Paint_Point || m_itemType == ItemType::Paint_NoPoint){
        //修改鼠标为绘图样式
        QCursor cursor = QCursor(QPixmap(iconPath+"cursor-size_Circle.png").scaled(m_qCircleR*2*m_scale,m_qCircleR*2*m_scale,
                                                                                   Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        this->setCursor(cursor);
        viewCursor = this->cursor();
    }


//    qDebug()<<this->matrix().m11()<<this->matrix().m12()<<this->matrix().m21()<<this->matrix().m22();
//    qDebug()<<"temp:"<<scaleTemp<<"m_scale:"<<m_scale<<"g_scale:"<<g_scale;

    this->scene()->update();
    return;
}

void VisionGraphView::back_region()
{
    if(m_vecRegion.count() <= 0)
        return;
    if(m_vecRegion.count()-1 > m_iIndex_Region){
        m_iIndex_Region++;
        m_region = m_vecRegion.at(m_vecRegion.count()-1-m_iIndex_Region);
        analysis_region(m_region);
        this->scene()->update();
    }
}

void VisionGraphView::front_region()
{
    if(m_vecRegion.count() <= 0 || m_vecRegion.count() <= 0)
        return;
    if(m_iIndex_Region > 0){
        m_iIndex_Region--;
        m_region = m_vecRegion.at(m_vecRegion.count()-1-m_iIndex_Region);
        analysis_region(m_region);
        this->scene()->update();
    }
}

void VisionGraphView::clearPainter()
{

    //todo 清除绘制的数据
    //给path赋值一个空path即可清空
    QPainterPath path;
    m_path = path;
    m_vecLines.clear();
    m_vecLines_unEdit.clear();

    m_clearAll = true;

    m_vecPoint_Poly.clear();
    m_vecPoint_Region.clear();
    m_vecRegion.clear();
    m_lstRegion.clear();

    //对m_region进行清空
    memset(&m_region, sizeof(m_region), 0);

    m_region.arrayPointRun.clear();
    m_region.frameHeight = 0;
    m_region.frameWidth = 0;

    push_region(m_region);


    this->scene()->update();
}

void VisionGraphView::setViewInfo_Visible(bool bVisible)
{
    if(bVisible){
        m_pLabelInfo->show();
    }else{
        m_pLabelInfo->hide();
    }
}

void VisionGraphView::setViewInfo_Pos(Corner corner)
{
//    qDebug()<<this->width()<<this->height() << "111111111" <<this->sceneRect();
    m_Corner = corner;
    if(corner == Corner::topLeft){
        m_pLabelInfo->move(2,2);

    }else if(corner == Corner::topRight){
        m_pLabelInfo->move(this->sceneRect().width()-2-m_pLabelInfo->width(),2);

    }else if(corner == Corner::bottomLeft){
        m_pLabelInfo->move(2,this->sceneRect().height()-2-m_pLabelInfo->height());

    }else if(corner == Corner::bottomRight){
        m_pLabelInfo->move(this->sceneRect().width()-2-m_pLabelInfo->width(),this->sceneRect().height()-2-m_pLabelInfo->height());
    }
}

void VisionGraphView::setViewInfo_Pos(qreal x, qreal y)
{
    m_pLabelInfo->move(x,y);
}

void VisionGraphView::setViewInfo_Size(QSize size)
{
    m_pLabelInfo->resize(size);
}

void VisionGraphView::setViewInfo_Size(qreal w, qreal h)
{
    m_pLabelInfo->resize(w,h);
}

void VisionGraphView::setViewInfo_text(QString text)
{
    m_pLabelInfo->setText(text);
}

void VisionGraphView::setViewInfo_Color(QColor backgroundColor, QColor textColor)
{

}

void VisionGraphView::setViewRegion_Size(qreal w, qreal h)
{
    m_frameRect.setWidth(w);
    m_frameRect.setHeight(h);
    this->scene()->update();
}

void VisionGraphView::setViewRegion_Visible(bool bVisible)
{
    m_bFrameVisible = bVisible;
    this->scene()->update();
}

void VisionGraphView::setViewRegion_Color(const QColor &color)
{
    m_FrameColor = color;
    this->scene()->update();
}

void VisionGraphView::viewRegion_OriginPos()
{
//    QRectF rf_1 = this->mapToScene(m_frameRect.toRect()).boundingRect();
    QRectF rf_1 = m_frameRect.toRect();
    QRectF rf_2 = this->mapToScene(this->rect()).boundingRect();
    this->scene()->setSceneRect((rf_1.width()-rf_2.width())/2,(rf_1.height()-rf_2.height())/2,
                                this->scene()->sceneRect().width(),this->scene()->sceneRect().height());
}

void VisionGraphView::itemCursorToViewCursor()
{
    if(m_itemType != ItemType::No){
        if(m_itemType == ItemType::Paint_Point || m_itemType == ItemType::Paint_NoPoint){
            //修改鼠标为绘图样式
            QCursor cursor = QCursor(QPixmap(iconPath+"cursor-size_Circle.png").scaled(m_qCircleR*2*m_scale,m_qCircleR*2*m_scale,
                                                                                       Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
            this->setCursor(cursor);
        }else if(m_itemType == ItemType::Drag){
            //拖动
            this->setCursor(Qt::OpenHandCursor);
        }else if(m_itemType == ItemType::Zoom){
            //缩放
            this->setCursor(Qt::ArrowCursor);
        }else{
            //其他绘制形状
            this->setCursor(Qt::CrossCursor);
        }
    }else{
        this->setCursor(Qt::ArrowCursor);
    }
    viewCursor = this->cursor();
}

void VisionGraphView::initRegion(XVRegion region)
{
    m_region = region;
    push_region(m_region);
    analysis_region(m_region);
    this->scene()->update();
}

void VisionGraphView::addRegion(XVRegionPair regionPair)
{
    m_lstRegion.append(regionPair);
}

void VisionGraphView::removeRegion(XVRegionPair regionPair)
{
    for(int i=0;i<m_lstRegion.count();i++){
        qDebug()<<m_lstRegion[i].value<<regionPair.value;
        if(m_lstRegion[i].value == regionPair.value){
            m_lstRegion.removeAt(i);
            break;
        }
    }
}

void VisionGraphView::setRegions(QList<XVRegionPair> lstRegionPair)
{
    m_lstRegion.append(lstRegionPair);
}

void VisionGraphView::clearRegion()
{
    m_lstRegion.clear();
}

void VisionGraphView::resize(const QSize &size)
{
    QGraphicsView::resize(size);
    this->scene()->setSceneRect(this->scene()->sceneRect().x(),this->scene()->sceneRect().y(),size.width(),size.height());
}

void VisionGraphView::resize(int w, int h)
{
    QGraphicsView::resize(w,h);
    this->scene()->setSceneRect(this->scene()->sceneRect().x(),this->scene()->sceneRect().y(),w,h);
}

qreal VisionGraphView::adjustSize(qreal w, qreal h)
{
    qreal qw = this->width()/w;
    qreal qh = this->height()/h;
    qreal q;
//    qDebug()<<qw<<qh;
    if(qw > qh){
        q = qh;
    }else{
        q = qw;
    }

    if(q > 5){
        q = 5;
    }
    zoom(q);

    m_frameRect.setWidth(w);
    m_frameRect.setHeight(h);
    viewRegion_OriginPos();
    return q;
}

QColor VisionGraphView::getPixel(qreal x, qreal y)
{
    QPixmap pixmap = this->grab(QRect(QPointF(x,y).toPoint(),QSize(-1,-1)));
    QColor color = QColor(0,0,0,0);
    if (!pixmap.isNull())
    {
        QImage image = pixmap.toImage();//将像素图转换为QImage
        if (!image.isNull()) //如果image不为空
        {
            if (image.valid(0, 0)) //坐标位置有效
            {
                color = image.pixel(0, 0);
            }
        }
    }
    return color;
}

void VisionGraphView::setCoordinateVisible(bool bVisible)
{
    isCoordinate = bVisible;
}

void VisionGraphView::updateRegion_UnEdit(XVRegion region){
//    m_Region_UnEdit = region;
    vector<XVPointRun> vec_point;
    vec_point = region.arrayPointRun;

    XVPointRun pointRun;
    QLineF lineF;
    m_vecLines_unEdit.clear();
    for(int i=0;i<vec_point.size();i++){
        pointRun = vec_point.at(i);
        lineF.setPoints((QPointF(pointRun.x,pointRun.y)),
                        (QPointF(pointRun.x+pointRun.length,pointRun.y)));
        m_vecLines_unEdit.append(lineF);
    }
}

void VisionGraphView::setRegionColor(QColor borderColor, QColor selectColor, QColor brushColor, QColor brushColor_unEdit)
{
    m_borderColor = borderColor;
    m_selectedColor = selectColor;
    m_brushColor = brushColor;
    m_brushColor_unEdit = brushColor_unEdit;
    this->scene()->update();
}


void VisionGraphView::slot_updateItem(ItemType type, QPainterPath path)
{
    return;
    if(m_graphType != GraphType::graphRegion)
        return;
    //编辑的控件在未确定之前，不调用算法生成点集合，临时绘制    item版本中作废
    m_path = this->mapFromScene(path);
}

XVRegion VisionGraphView::slot_updatePath(bool selected, VisionItem *item,ItemType type,QRectF rf,QPointF leftTop,qreal angle)
{
    if(m_graphType != GraphType::graphRegion)
        return m_region;

    if(!selected){
        qDebug()<<"create region";
        //编辑完成，获取已经确定的区域的点集合，同时将对应的临时path清空
        rf =  QRectF((rf.topLeft()),(rf.bottomRight()));
//        XVCreateRegionOut regionOut;
        if(type == ItemType::Paint_Rect){


            XVRegion region = createRectangle(rf,leftTop,angle);

            m_region = slot_CombineRegion(m_region,region,Union);

            push_region(m_region);
            analysis_region(m_region);

            QPainterPath path;
            m_path = path;

        }else if(type == ItemType::Paint_EllipseItem || type == ItemType::Paint_CirCle){
            XVRegion region = createEllipse(rf,leftTop,angle);

            m_region = slot_CombineRegion(m_region,region,Union);

            push_region(m_region);
            analysis_region(m_region);

            //给path赋值一个空path即可清空
            QPainterPath path;
            m_path = path;
        }
        if(item != NULL){
            item->hide();item->deleteLater();item = NULL;
        }
        this->scene()->update();
    }
    return m_region;
}

XVRegion VisionGraphView::slot_CreatePolygonF(bool selected, VisionItem *item, ItemType type, QVector<QPointF> vecPointF)
{
    if(m_graphType != GraphType::graphRegion)
        return m_region;

    if(selected)
        return m_region;

    QPolygonF polyF(vecPointF);

    XVRegion region = createPolygon(polyF);

    m_region = slot_CombineRegion(m_region,region,Union);

    push_region(m_region);
    analysis_region(m_region);

    QPainterPath path;
    m_path = path;

    if(item != NULL){
        item->hide();item->deleteLater();item = NULL;
    }
    this->scene()->update();
    return m_region;
}

XVRegion VisionGraphView::slot_CombineRegion(XVRegion region1, XVRegion region2, XVCombineRegionsType combineType)
{
    TwoRegionIn unionIn;
    unionIn.inRegion1 = region1;
    unionIn.inRegion2 = region2;
    unionIn.inRegion1.optional = ENABLE;
    unionIn.inRegion2.optional = ENABLE;

    RegionOut unionOut;
    if(combineType == XVCombineRegionsType::Union){

        typedef void (*RegionUnion)(TwoRegionIn &,RegionOut &);
         RegionUnion XVRegionUnion =
                 (RegionUnion) m_lib_XVRegionAnalysis.resolve("XVRegionUnion");
         if (XVRegionUnion)
             XVRegionUnion(unionIn,unionOut);

//        XVRegionUnion(unionIn,unionOut);
    }else if(combineType == XVCombineRegionsType::Difference){

        typedef void (*RegionDiff)(TwoRegionIn &,RegionOut &);
         RegionDiff XVRegionDifference =
                 (RegionDiff) m_lib_XVRegionAnalysis.resolve("XVRegionDifference");
         if (XVRegionDifference)
             XVRegionDifference(unionIn,unionOut);

//        XVRegionDifference(unionIn,unionOut);
    }
    return unionOut.outRegion;
}

QVector<QLineF> VisionGraphView::analysis_region(XVRegion region)
{
//    if(m_region == region)
//        return;

//    emit signal_RegionItem();
    //XVPointRun  起始点坐标和线的长度
    vector<XVPointRun> vec_point;
    vec_point = region.arrayPointRun;

    XVPointRun pointRun;
    QLineF lineF;
    m_vecLines.clear();
    for(int i=0;i<vec_point.size();i++){
        pointRun = vec_point.at(i);
        lineF.setPoints((QPointF(pointRun.x,pointRun.y)),
                        (QPointF(pointRun.x+pointRun.length,pointRun.y)));
        m_vecLines.append(lineF);
    }

    emit signal_RegionItem();
    return m_vecLines;
}

XVRegion VisionGraphView::createPolygon(QPolygonF polygonF)
{
    XVCreatePolygonRegionOut regionOut;
//    XVCreateRegionOut regionOut;
    XVCreatePolygonRegionIn regionIn;

    XVPath xvPath;
    vector<XVPoint2D> vec_point2D;

    for(int i=0;i<polygonF.count();i++){
        XVPoint2D point2D;
        point2D.x = polygonF.at(i).x();
        point2D.y = polygonF.at(i).y();
        vec_point2D.push_back(point2D);
    }
    xvPath.arrayPoint2D = vec_point2D;
    xvPath.closed = true;

    regionIn.inFrameWidth = m_frameRect.width();
    regionIn.inFrameHeight = m_frameRect.height();
    regionIn.inPolygon = xvPath;
    regionIn.inPolygon.optional = ENABLE;

    XVRegion region;


    typedef void (*PolygonRegion)(XVCreatePolygonRegionIn &,XVCreatePolygonRegionOut &);
     PolygonRegion XVCreatePolygonRegion =
             (PolygonRegion) m_lib_XVRegionAnalysis.resolve("XVCreatePolygonRegion");
     if (XVCreatePolygonRegion)
         XVCreatePolygonRegion(regionIn,regionOut);

     //    XVCreatePolygonRegion(regionIn,regionOut);
     region = regionOut.outRegion;


    return region;
}


XVRegion VisionGraphView::createEllipse(QRectF rf,QPointF leftTop, qreal angle)
{
    rf =  QRectF((rf.topLeft()),(rf.bottomRight()));

    XVRegion region;


    if(rf.width() == rf.height()){
        XVCreateCircleRegionOut regionOut;

        XVCreateCircleRegionIn regionIn;

        XVCircle2D xvCircle;
        XVPoint2D centerPointF;
        centerPointF.x = (float)(rf.x()+rf.width()/2);
        centerPointF.y = (float)(rf.y()+rf.height()/2);
        xvCircle.center = centerPointF;
        xvCircle.radius = rf.width()/2;


        //没有圆
        regionIn.inFrameWidth = m_frameRect.width();
        regionIn.inFrameHeight = m_frameRect.height();
        regionIn.inCircle = xvCircle;
        regionIn.inCircle.optional = ENABLE;
        regionIn.inCircle.center.optional = ENABLE;


        typedef void (*CircleRegion)(XVCreateCircleRegionIn &,XVCreateCircleRegionOut &);
         CircleRegion XVCreateCircleRegion =
                 (CircleRegion) m_lib_XVRegionAnalysis.resolve("XVCreateCircleRegion");
         if (XVCreateCircleRegion)
             XVCreateCircleRegion(regionIn,regionOut);

//        XVCreateCircleRegion(regionIn,regionOut);

        region = regionOut.outRegion;

    }else{

        XVCreateEllipseRegionOut regionOut;

        XVCreateEllipseRegionIn regionIn;

        XVRectangle2D xvRect;
        XVPoint2D leftPoint;
        leftPoint.x = (float)leftTop.x();
        leftPoint.y = (float)leftTop.y();
        xvRect.origin = leftPoint;
        xvRect.angle = angle;
        xvRect.height = (float)rf.height();
        xvRect.width = (float)rf.width();

        regionIn.inFrameWidth = m_frameRect.width();
        regionIn.inFrameHeight = m_frameRect.height();
        regionIn.inEllipse =xvRect;
        regionIn.inEllipse.optional = ENABLE;

        typedef void (*EllipseRegion)(XVCreateEllipseRegionIn &,XVCreateEllipseRegionOut &);
         EllipseRegion XVCreateEllipseRegion =
                 (EllipseRegion) m_lib_XVRegionAnalysis.resolve("XVCreateEllipseRegion");
         if (XVCreateEllipseRegion)
             XVCreateEllipseRegion(regionIn,regionOut);

//        XVCreateEllipseRegion(regionIn,regionOut);

        region = regionOut.outRegion;

    }
    return region;
}

XVRegion VisionGraphView::createRectangle(QRectF rf,QPointF leftTop, qreal angle)
{
    rf =  QRectF((rf.topLeft()),(rf.bottomRight()));
    XVCreateRectangleRegionOut regionOut;
    XVCreateRectangleRegionIn  regionIn;

    XVRectangle2D xvRect;
    XVPoint2D leftPoint;
    leftPoint.x = (float)leftTop.x();
    leftPoint.y = (float)leftTop.y();
    xvRect.origin = leftPoint;
    xvRect.angle = angle;
    xvRect.height = (float)rf.height();
    xvRect.width = (float)rf.width();

    regionIn.inFrameWidth = m_frameRect.width();
    regionIn.inFrameHeight = m_frameRect.height();
    regionIn.inRectangle =xvRect;
    regionIn.inRectangle.optional = ENABLE;
    regionIn.inRectangle.origin.optional = ENABLE;


    typedef void (*RectangleRegion_1)(XVCreateRectangleRegionIn &,XVCreateRectangleRegionOut &);
     RectangleRegion_1 XVCreateRectangleRegion_1 =
             (RectangleRegion_1) m_lib_XVRegionAnalysis.resolve("XVCreateRectangleRegion");
     if (XVCreateRectangleRegion_1){
         XVCreateRectangleRegion_1(regionIn,regionOut);
//         XVCreateRectangleRegion(regionIn,regionOut);
     }else{

     }

//    XVCreateRectangleRegion(regionIn,regionOut);

     //昨日进度：
     //1.解决VisionGraph商库的问题

    XVRegion region = regionOut.outRegion;

    return region;

}

XVRegion VisionGraphView::createLine(QLine line)
{
    XVCreateLineRegionIn regionIn1;
    XVCreateLineRegionOut regionOut1;

    qreal a1 = line.p1().y() - line.p2().y();
    qreal b1 = line.p2().x() - line.p1().x();
    //ax+by+c=0; 直线和圆相切得到四个点    圆心到线的距离等于半径
    qreal c1 =  - (a1*line.p1().x()+b1*line.p1().y());

    XVLine2D line2D;
    line2D.optional = ENABLE;
    line2D.a = a1;
    line2D.b = b1;
    line2D.c = c1;
    regionIn1.inLine = line2D;
    regionIn1.inFrameWidth = m_frameRect.width();
    regionIn1.inFrameHeight = m_frameRect.height();

    typedef void (*LineRegion)(XVCreateLineRegionIn &,XVCreateLineRegionOut &);
     LineRegion XVCreateLineRegion =
             (LineRegion) m_lib_XVRegionAnalysis.resolve("XVCreateLineRegion");
     if (XVCreateLineRegion)
         XVCreateLineRegion(regionIn1,regionOut1);

     XVRegion region = regionOut1.outRegion;

     return region;
}

void VisionGraphView::push_region(XVRegion region, int index)
{
    if(m_iIndex_Region == 0){
        //没有在中间插入，
        m_vecRegion.push_back(region);
    }else{
        m_vecRegion = m_vecRegion.mid(0,m_vecRegion.count()-m_iIndex_Region);
        m_vecRegion.push_back(region);
        m_iIndex_Region = 0;
    }
}

void VisionGraphView::detailMoveEvent(QMouseEvent *event)
{
    QPoint viewPos = event->pos();//获取视口坐标
    QPointF scenePos = this->mapToScene(viewPos);//将视口坐标转换为场景坐标

    //2.修改在点击选择选项的时候，item在选中情况下无法move    m_itemType != ItemType::No的原因

    if(m_itemType == ItemType::Paint_Rect){
        //绘制矩形
        QPainterPath path;
        path.addRect(QRectF(m_pressPointF,viewPos));
        m_path = path;
    }else if(m_itemType == ItemType::Paint_EllipseItem){
        //绘制椭圆
        QPainterPath path;
        QRectF rf = detail_ellipse_InRectToOutRect(QRectF(m_pressPointF,viewPos));
        path.addEllipse(rf);

//        path.addEllipse(QRectF(m_pressPointF,viewPos));
        m_path = path;
    }else if(m_itemType == ItemType::Paint_CirCle){
        //绘制圆
        QPainterPath path;
        QRectF rf = detail_ellipse_InRectToOutRect(QRectF(m_pressPointF,viewPos));
        if(rf.width() < rf.height()){
            rf.setRect(rf.x(),rf.y(),rf.height(),rf.height());
        }else{
            rf.setRect(rf.x(),rf.y(),rf.width(),rf.width());
        }
        path.addEllipse(rf);
        m_path = path;
    }else if(m_itemType == ItemType::Paint_Arc){
        //释放，记录坐标，有一个点，跟随鼠标绘制直线，有两个点，跟随鼠标绘制圆弧
        QPainterPath path;
        //获取已经存在的m_vecPoint_Poly存在一个点，绘制直线
        if(m_vecPoint_Poly.count() == 1){
            path = QPainterPath(this->mapFromScene(m_vecPoint_Poly[0]));
            path.lineTo(this->mapFromScene(scenePos));
        }else if(m_vecPoint_Poly.count() == 2){
            //m_vecPoint_Poly存在两个点，和动态的点，组合成一个圆
            qreal r;qreal angle;qreal spanAngle;QPointF center;qreal bDirect = 1;
            QList<qreal> lst = getArc(this->mapFromScene(m_vecPoint_Poly[0]),this->mapFromScene(scenePos),this->mapFromScene(m_vecPoint_Poly[1]));
            if(lst.count() == 0){
                //三点一线
                path = QPainterPath(this->mapFromScene(m_vecPoint_Poly[0]));
                path.lineTo(this->mapFromScene(scenePos));
                path.lineTo(this->mapFromScene(m_vecPoint_Poly[1]));
            }else if(lst.count() >= 6){
                center = QPointF(lst[0],lst[1]);
                r = lst[2];
                angle = lst[3];
                spanAngle = lst[4];
                bDirect = lst[5];
//                path = QPainterPath(this->mapFromScene(scenePos));
                if(bDirect == 1){
                    path.moveTo(this->mapFromScene(m_vecPoint_Poly[0]));  //绘制起点位置
                }else{
                    path.moveTo(this->mapFromScene(m_vecPoint_Poly[1]));  //绘制起点位置
                }
                path.arcTo(center.x()-r,center.y()-r,2*r,2*r,angle,spanAngle);
            }else{

            }
        }
        m_path = path;

    }else if(m_itemType == ItemType::Paint_Poly){
        QPainterPath path;
        QPolygonF poly(m_vecPoint_Poly);
        poly.insert(m_vecPoint_Poly.count(),scenePos);  //将最后一点替换成掉
        path.addPolygon(this->mapFromScene(poly));
        m_path = path;

    }else if(m_itemType == ItemType::Paint_Region){
        //鼠标绘制任意区域
        m_vecPoint_Region.append(scenePos);
        QPainterPath path;
        QPolygonF poly(m_vecPoint_Region);
        path.addPolygon(poly);
        m_path = this->mapFromScene(path);
    }else if(m_itemType == ItemType::Paint_Line){
//        m_Line.setPoints(m_pressPointF_scene.toPoint(),scenePos.toPoint());
        m_path = QPainterPath(this->mapFromScene(m_pressPointF_scene));
        m_path.lineTo(this->mapFromScene(scenePos));

    }else if(m_itemType == ItemType::Paint_polyLine){
        QPainterPath path;
        QPolygonF poly(m_vecPoint_Poly);
        poly.insert(m_vecPoint_Poly.count(),scenePos);  //将最后一点替换成掉
        path.addPolygon(this->mapFromScene(poly));
        m_path = path;
    }else if(m_itemType == ItemType::Paint_Point || m_itemType == ItemType::Paint_NoPoint){
        //鼠标绘制(擦除)
        //必须保证鼠标是一直按下的状态
        if(event->buttons() != Qt::LeftButton){
            //表示move事件是鼠标移动触发的，即在move过程中，按下的不是左键直接return
            //注意button()和buttons()之间的区别
            return;
        }
        //计算区域
        qreal a = viewPos.y() - m_lastPointF.y();
        qreal b = m_lastPointF.x() - viewPos.x();
        //ax+by+c=0; 直线和圆相切得到四个点    圆心到线的距离等于半径
        qreal c1 = m_qCircleR*m_scale*sqrt(a*a+b*b) - (a*m_lastPointF.x()+b*m_lastPointF.y());
        qreal c2 = -m_qCircleR*m_scale*sqrt(a*a+b*b) - (a*m_lastPointF.x()+b*m_lastPointF.y());
        //求过圆1和圆2的并且和l1和l2垂直的线的方程
        //la(圆1):bx-ay+ca = 0;  ca = ay-bx
        qreal ca = a*m_lastPointF.y() - b*m_lastPointF.x();

        //lb(圆2):bx-ay+cb = 0;
        qreal cb = a*viewPos.y() - b*viewPos.x();

        //A1x+B1x+C1=0;A2x+B2y+C2=0
        //if(A1*B2-A2*B1 != 0) 有唯一解  x=(B1*C2-B2*C1)/(A1*B2-A2*B1）  y=-(A1*C2-A2*C1)/(A1*B2-A2*B1）

        //与圆得到切点p --- 不容易求，计算过圆心的和l1垂直的线即可轻松得到交点
        //l1:ax+by+c1=0;   la:bx-ay+ca = 0; p1
        QPointF p1 = QPointF((b*ca-(-a)*c1)/(a*(-a)-b*b),-(a*ca-b*c1)/(a*(-a)-b*b));

        //l1:ax+by+c1=0;  lb:bx-ay+cb = 0; p2
        QPointF p2 = QPointF((b*cb-(-a)*c1)/(a*(-a)-b*b),-(a*cb-b*c1)/(a*(-a)-b*b));

        //l2:ax+by+c2=0;   lb:bx-ay+cb = 0; p3
        QPointF p3 = QPointF((b*cb-(-a)*c2)/(a*(-a)-b*b),-(a*cb-b*c2)/(a*(-a)-b*b));

        //l2:ax+by+c2=0;   la:bx-ay+ca = 0; p4
        QPointF p4 = QPointF((b*ca-(-a)*c2)/(a*(-a)-b*b),-(a*ca-b*c2)/(a*(-a)-b*b));

        QVector<QPointF> vec;
        vec.clear();
        vec.push_back(this->mapToScene(p1.toPoint()));
        vec.push_back(this->mapToScene(p2.toPoint()));
        vec.push_back(this->mapToScene(p3.toPoint()));
        vec.push_back(this->mapToScene(p4.toPoint()));

        QPolygonF polygonF(vec);

//        qDebug()<<c1<<c2<<"12121212121212"<<m_qCircleR;
//        if(m_qCircleR == 1){

//        }else{

            //合并区域
            QPainterPath path;
            path.addPolygon(polygonF);

            XVRegion region = createPolygon(polygonF);

            if(m_itemType == ItemType::Paint_Point){
                m_region = slot_CombineRegion(m_region,region,XVCombineRegionsType::Union);
            }else{
                m_region = slot_CombineRegion(m_region,region,XVCombineRegionsType::Difference);
            }
            //对两个path通过算法转换成region

            QPainterPath path1;
            path1.addEllipse(viewPos,m_qCircleR*m_scale,m_qCircleR*m_scale);

            QRectF rf11 = QRectF(this->mapToScene(QPoint(viewPos.x()-m_qCircleR*m_scale,viewPos.y()-m_qCircleR*m_scale)),
                                                  this->mapToScene(QPoint(viewPos.x()+m_qCircleR*m_scale,viewPos.y()+m_qCircleR*m_scale)));
            XVRegion region1 = createEllipse(rf11,rf11.topLeft(),0);

            if(m_itemType == ItemType::Paint_Point){
                m_region = slot_CombineRegion(m_region,region1,XVCombineRegionsType::Union);
            }else{
                m_region = slot_CombineRegion(m_region,region1,XVCombineRegionsType::Difference);
            }
//        }


        analysis_region(m_region);
    }
    this->scene()->update();
}

void VisionGraphView::detailPressEvent(QMouseEvent *event)
{
    QPoint viewPos = event->pos();//获取视口坐标
    QPointF scenePos = this->mapToScene(viewPos);//将视口坐标转换为场景坐标

    //当前只存在两种模式
    //第一次按下开始，第二次按下结束
    //第一次按下开始，直到双击或者右击结束或者一定数量的单击结束
    //
    m_pressPointF = viewPos;
    m_pressPointF_scene = scenePos;

    if(event->button() == Qt::RightButton){
        //多边形和折线右击结束绘制
        if(m_itemType == ItemType::Paint_Poly){
            emit signal_Item_poly(m_vecPoint_Poly,ItemType::Paint_Poly);
        }else if(m_itemType == ItemType::Paint_polyLine){
            emit signal_Item_poly(m_vecPoint_Poly,ItemType::Paint_polyLine);
        }
        m_bPress = false;  //绘制结束
        qDebug()<<"poly polyLine draw is finished!"<<m_vecPoint_Poly.count();
        //绘制结束
        QPainterPath path;
        m_path = path;
        m_vecPoint_Poly.clear();
        setItemType(ItemType::No);
    }else if(event->button() == Qt::LeftButton){
        m_bPress = true;  //表示在绘制过程中

        //绘制矩形
        if(m_itemType == ItemType::Paint_Rect){
            m_vecPoint_Poly.append(scenePos);
            if(m_vecPoint_Poly.count() >= 2){
                //绘制结束  记录的点击的点存在2个或者两个以上的时候
                QPointF topLeftPoint;
                QPointF bottomRightPoint;
                if(m_vecPoint_Poly[0].x() < m_vecPoint_Poly[1].x()){
                    topLeftPoint.setX(m_vecPoint_Poly[0].x());
                    bottomRightPoint.setX(m_vecPoint_Poly[1].x());
                }else{
                    topLeftPoint.setX(m_vecPoint_Poly[1].x());
                    bottomRightPoint.setX(m_vecPoint_Poly[0].x());
                }

                if(m_vecPoint_Poly[0].y() < m_vecPoint_Poly[1].y()){
                    topLeftPoint.setY(m_vecPoint_Poly[0].y());
                    bottomRightPoint.setY(m_vecPoint_Poly[1].y());
                }else{
                    topLeftPoint.setY(m_vecPoint_Poly[1].y());
                    bottomRightPoint.setY(m_vecPoint_Poly[0].y());
                }

                emit signal_Item(m_itemType,QRectF(topLeftPoint,bottomRightPoint));
                m_bPress = false;  //绘制结束

                QPainterPath path;
                m_path = path;
                m_vecPoint_Poly.clear();
                setItemType(ItemType::No);
            }
        }else if(m_itemType == ItemType::Paint_EllipseItem){
            m_vecPoint_Poly.append(scenePos);
            if(m_vecPoint_Poly.count() >= 2){
                //绘制结束
                QPointF topLeftPoint;
                QPointF bottomRightPoint;
                if(m_vecPoint_Poly[0].x() < m_vecPoint_Poly[1].x()){
                    topLeftPoint.setX(m_vecPoint_Poly[0].x());
                    bottomRightPoint.setX(m_vecPoint_Poly[1].x());
                }else{
                    topLeftPoint.setX(m_vecPoint_Poly[1].x());
                    bottomRightPoint.setX(m_vecPoint_Poly[0].x());
                }

                if(m_vecPoint_Poly[0].y() < m_vecPoint_Poly[1].y()){
                    topLeftPoint.setY(m_vecPoint_Poly[0].y());
                    bottomRightPoint.setY(m_vecPoint_Poly[1].y());
                }else{
                    topLeftPoint.setY(m_vecPoint_Poly[1].y());
                    bottomRightPoint.setY(m_vecPoint_Poly[0].y());
                }

                //点转化，绘制的事内接矩形的点，转化为外接的矩形的点
                QRectF rf = detail_ellipse_InRectToOutRect(QRectF(topLeftPoint,bottomRightPoint));
//                emit signal_Item(m_itemType,QRectF(topLeftPoint,bottomRightPoint));
                emit signal_Item(m_itemType,rf);
                m_bPress = false;  //绘制结束

                QPainterPath path;
                m_path = path;
                m_vecPoint_Poly.clear();
                setItemType(ItemType::No);
            }
        }else if(m_itemType == ItemType::Paint_CirCle){
            m_vecPoint_Poly.append(scenePos);
            if(m_vecPoint_Poly.count() >= 2){
                //绘制结束
                QPointF topLeftPoint;
                QPointF bottomRightPoint;
                if(m_vecPoint_Poly[0].x() < m_vecPoint_Poly[1].x()){
                    topLeftPoint.setX(m_vecPoint_Poly[0].x());
                    bottomRightPoint.setX(m_vecPoint_Poly[1].x());
                }else{
                    topLeftPoint.setX(m_vecPoint_Poly[1].x());
                    bottomRightPoint.setX(m_vecPoint_Poly[0].x());
                }

                if(m_vecPoint_Poly[0].y() < m_vecPoint_Poly[1].y()){
                    topLeftPoint.setY(m_vecPoint_Poly[0].y());
                    bottomRightPoint.setY(m_vecPoint_Poly[1].y());
                }else{
                    topLeftPoint.setY(m_vecPoint_Poly[1].y());
                    bottomRightPoint.setY(m_vecPoint_Poly[0].y());
                }

                //点转化，绘制的事内接矩形的点，转化为外接的矩形的点
                QRectF rf = detail_ellipse_InRectToOutRect(QRectF(topLeftPoint,bottomRightPoint));
//                emit signal_Item(m_itemType,QRectF(topLeftPoint,bottomRightPoint));
                if(rf.width() < rf.height()){
                    rf.setRect(rf.x(),rf.y(),rf.height(),rf.height());
                }else{
                    rf.setRect(rf.x(),rf.y(),rf.width(),rf.width());
                }

                emit signal_Item(m_itemType,rf);
                m_bPress = false;  //绘制结束

                QPainterPath path;
                m_path = path;
                m_vecPoint_Poly.clear();
                setItemType(ItemType::No);
            }
        }else if(m_itemType == ItemType::Paint_Arc){
            //释放，记录坐标，记录的是第三个点，则说明绘制结束
            m_vecPoint_Poly.append(scenePos);
            if(m_vecPoint_Poly.count() >= 3){
                //绘制结束
                emit signal_Item_poly(m_vecPoint_Poly,ItemType::Paint_Arc);
                m_bPress = false;  //绘制结束

                QPainterPath path;
                m_path = path;
                m_bPainter = false;
                //圆弧绘制完成，进行转换
                m_vecPoint_Poly.clear();
                //绘制圆弧结束
                setItemType(ItemType::No);
            }
        }else if(m_itemType == ItemType::Paint_Poly){
            m_vecPoint_Poly.append(scenePos);
        }else if(m_itemType == ItemType::Paint_CrossPoint){
            emit signal_Item_point(scenePos);
            setItemType(ItemType::No);
        }else if(m_itemType == ItemType::Paint_Line){
            m_vecPoint_Poly.append(scenePos);
            if(m_vecPoint_Poly.count() >= 2){
                //绘制结束
                m_Line.setPoints(m_vecPoint_Poly[0].toPoint(),m_vecPoint_Poly[1].toPoint());

                emit signal_Item_Line(m_Line);
                m_bPress = false;  //绘制结束

                QPainterPath path;
                m_path = path;
                m_vecPoint_Poly.clear();
                setItemType(ItemType::No);
            }

        }else if(m_itemType == ItemType::Paint_polyLine){
            m_vecPoint_Poly.append(scenePos);
        }else if(m_itemType == ItemType::Paint_Point || m_itemType == ItemType::Paint_NoPoint){

            //计算区域
            QPainterPath path1;
            path1.addEllipse(viewPos,m_qCircleR*m_scale,m_qCircleR*m_scale);

            QRectF rf11 = QRectF(this->mapToScene(QPoint(viewPos.x()-m_qCircleR*m_scale,viewPos.y()-m_qCircleR*m_scale)),
                                                  this->mapToScene(QPoint(viewPos.x()+m_qCircleR*m_scale,viewPos.y()+m_qCircleR*m_scale)));
            XVRegion region = createEllipse(rf11,rf11.topLeft(),0);

            if(m_itemType == ItemType::Paint_Point){
                m_region = slot_CombineRegion(m_region,region,XVCombineRegionsType::Union);
            }else{
                m_region = slot_CombineRegion(m_region,region,XVCombineRegionsType::Difference);
            }
            analysis_region(m_region);
        }
    }
}

QList<qreal> VisionGraphView::getArc(QPointF sP, QPointF mP, QPointF fP)
{
    QPointF center; qreal r; qreal angle; qreal spanAngle; qreal bDirect = 1;  //方向：1 sp->mp->fp  0 fp->mp->sp
    QList<qreal> lstData;
    lstData.clear();

    //三点确定一个圆,硬解，可得到表达式（三点一线的时候，则无法形成圆）
    double x1 = sP.x(), x2 = mP.x(), x3 = fP.x();
    double y1 = sP.y(), y2 = mP.y(), y3 = fP.y();
    double a = x1 - x2;
    double b = y1 - y2;
    double c = x1 - x3;
    double d = y1 - y3;
    double e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2.0;
    double f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2.0;
    double det = b * c - a * d;

    if((x1 == x2 && x1 == x3) || (y1 == y2 && y1 == y3))
    {
        //三点一线,
        return lstData;
    }

//    if( fabs(det) < 1e-5)
//    {
//        radius = -1;
//        return QPointF(0,0);
//    }

    double x0 = -(d * e - b * f) / det;
    double y0 = -(a * f - c * e) / det;
    center.setX(x0);
    center.setY(y0);
    r = hypot(x1 - x0, y1 - y0);

    //
    double angle1 = acos((x1-x0)/(hypot((x1-x0),(y1-y0))));
    double angle2 = acos((x2-x0)/(hypot((x2-x0),(y2-y0))));
    double angle3 = acos((x3-x0)/(hypot((x3-x0),(y3-y0))));
    if(y1-y0 < 0){
        angle1 = 2*Pi - angle1;
    }else{
        angle1 = angle1;
    }
    if(y3-y0 < 0){
        angle3 = 2*Pi - angle3;
    }else{
        angle3 = angle3;
    }

    if(y2-y0 < 0){
        angle2 = 2*Pi - angle2;
    }else{
        angle2 = angle2;
    }

    //上面计算的角度是基于QGraphicsView中的坐标，需要进行转换为数学坐标中的角度
    angle1 = 360-angle1*180/Pi;
    angle2 = 360-angle2*180/Pi;
    angle3 = 360-angle3*180/Pi;

//    qDebug()<<angle1<<angle2<<angle3;
    if(angle1 < angle3){
        //1是起点，3是终点
        if(angle2 < angle3 && angle2 > angle1){
            //2在中间，1-2-3
            angle = angle1;
            spanAngle = angle3 - angle1;
            bDirect = 1;
        }else{
            // 2在1-3外面   3-2-1
            angle = angle3;
            spanAngle = 360-(angle3 - angle1);
            bDirect = 0;
        }
    }else{
        //3是起点，1是终点  正方向--  3-2-1
        if(angle2 < angle1 && angle2 > angle3){
            //3-2-1
            angle = angle3;
            spanAngle = angle1 - angle3;
            bDirect = 0;
        }else{
            //1-2-3
            angle = angle1;
            spanAngle = 360-(angle1 - angle3);
            bDirect = 1;
        }
    }

    lstData.append({center.x(),center.y(),r,angle,spanAngle,bDirect});
//    qDebug()<<angle<<spanAngle;
    return lstData;

}

QRectF VisionGraphView::detail_ellipse_InRectToOutRect(QRectF rf)
{
    //rf是外接矩形。对角线与椭圆相交的点即为内接矩形
    //椭圆方程已知，直线已知

    //   x^2/(w/2)^2+y^2/(h/2)^2=1;  由于w和h本身包含了长短，故，可以作为一般方程式，
    //   直线方程，Ax+By+C=0;   两点 topLeft，bottomRight

    return rf;
    float A = rf.bottomRight().y() - rf.topLeft().y();
    float B = rf.topLeft().x() - rf.bottomRight().x();
    float C = rf.bottomRight().x()*rf.topLeft().y() - rf.topLeft().x()*rf.bottomRight().y();

    float a=rf.width()/2;
    float b=rf.height()/2;

    float m=B*B*(b*b)+(A*A*a*a);
    float n=2*B*C*b*b;
    float p=b*b*C*C-A*A*a*a*b*b;

    float m1=A*A*a*a+(B*B*b*b);
    float n1=2*A*C*a*a;
    float p1=C*C*a*a-B*B*b*b*a*a;

    qDebug()<<n*n-4*m*p<<p;
    if(n*n-4*m*p < 0 || n1*n1-4*m1*p1 < 0)
        return rf;
    float y1=(-n-sqrt(n*n-4*m*p))/(2*m);
    float y2=(-n+sqrt(n*n-4*m*p))/(2*m);
    float x1=(-n1-sqrt(n1*n1-4*m1*p1))/(2*m1);
    float x2=(-n1+sqrt(n1*n1-4*m1*p1))/(2*m1);
    return QRectF(QPointF(x1,y1),QPointF(x2,y2));
    /*
    float a=0,b=0,c=0; //a-x轴，b-y轴
    float x=0,y=0;
    x=fabs(rf.topLeft().x()-rf.bottomRight().x())/2;
    y=fabs(rf.topLeft().y()-rf.bottomRight().y())/2;
    float ftan = x/y;
    QPointF disP;
    if(x>y){
        //椭圆的焦点在x轴上
        c=x;
        a=(x*x)/sqrt(x*x-y*y);
        b=(x*y)/sqrt(x*x-y*y);
        disP = QPointF(a-x,(b-y)/ftan);

    }else if(x<y){
        //椭圆的焦点在y轴上
        c=y;
        a=(x*y)/sqrt(y*y-x*x);
        b=(y*y)/sqrt(y*y-x*x);
        disP = QPointF((a-x)*ftan,(b-y));
    }else{
        //圆
        c=x;
        a=2*x;
        b=2*x;
        disP = QPointF(a-x,(b-y));
    }
    QRectF rf1 = QRectF(rf.topLeft()-disP,rf.bottomRight()+disP);
    return rf;
    */
}

void VisionGraphView::slot_wheelEvent(QWheelEvent *event)
{
    // 获取当前的鼠标所在的view坐标;
    QPointF prev_viewPos = event->pos();
    // 获取当前鼠标相对于scene的位置;
     QPointF prev_scenePos = this->mapToScene(prev_viewPos.toPoint());

//     qDebug()<<prev_viewPos;
     qreal zoom = m_scale;
     if(event->delta() > 0){
         //放大
         zoom = zoom + 0.2;
     }else{
         if(zoom <= 0.3){
             zoom = 0.3;
         }else if(zoom <= 1){
             zoom = zoom - 0.1;
         }else{
             zoom = zoom - 0.2;
         }
     }

     qreal scaleTemp = zoom/m_scale;  //获取本次缩放相对于上次缩放的比例
     m_scale = zoom;

    scale(scaleTemp, scaleTemp);


    this->scene()->setSceneRect(this->mapToScene(this->rect()).boundingRect());

    //获取缩放后的scene坐标
    QPointF scenePos = this->mapToScene(prev_viewPos.toPoint());

    //获取缩放前后的坐标差值，即为需要进行move的位移
    QPointF disPointF = scenePos - prev_scenePos;

    this->scene()->setSceneRect(this->scene()->sceneRect().x()-disPointF.x(),this->scene()->sceneRect().y()-disPointF.y(),
                                this->scene()->sceneRect().width(),this->scene()->sceneRect().height());
//    this->scene()->update();

    emit signal_wheel(m_scale);   //将缩放的比例通知外部

//    qDebug()<<this->matrix().m11()<<this->matrix().m12()<<this->matrix().m21()<<this->matrix().m22();
//    qDebug()<<"temp:"<<scaleTemp<<"m_scale:"<<m_scale<<"g_scale:"<<g_scale;
    //TODO 可采用调用view的matrix来获取当前缩放比例，用于赋值g_scale，脱离全局变量,为了
}

void VisionGraphView::slotUpdateViewInfo_Pos()
{
    //设置了初始构造了sceneWidget后进行对m_frameRect居中
    this->scene()->setSceneRect((m_frameRect.width()-this->width())/2,(m_frameRect.height()-this->height())/2,
                                this->scene()->sceneRect().width(),this->scene()->sceneRect().height());

    if(m_Corner == Corner::topLeft){
        return;

    }else if(m_Corner == Corner::topRight){
        m_pLabelInfo->move(this->sceneRect().width()-2-m_pLabelInfo->width()-15,2);

    }else if(m_Corner == Corner::bottomLeft){
        m_pLabelInfo->move(2,this->sceneRect().height()-2-m_pLabelInfo->height()-15);

    }else if(m_Corner == Corner::bottomRight){
        m_pLabelInfo->move(this->sceneRect().width()-2-m_pLabelInfo->width()-15,this->sceneRect().height()-2-m_pLabelInfo->height()-15);
    }
}

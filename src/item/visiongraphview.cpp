#include "visiongraphview.h"
#include <QScrollBar>
#include "qdebug.h"
#include "visiongraphscene.h"
#include "../control/color.h"

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

}

void VisionGraphView::mouseMoveEvent(QMouseEvent *event)
{

    QPoint viewPos = event->pos();//获取视口坐标
    QPointF scenePos = this->mapToScene(viewPos);//将视口坐标转换为场景坐标

    emit signal_Move(viewPos);

    //show mouse info
    if(!m_pLabelInfo->isHidden()){
        QString text_pos="";
        QString text_rgb="";
        QString text_gray="";
//        m_pMouseInfo_Label->move(viewPos+QPoint(5,5));
        text_pos = (QStringLiteral("坐标:(")+QString::number(viewPos.x())+","+QString::number(viewPos.y())+")");

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
//                    qDebug() << text_rgb<<"   "<<text_gray;
                }
            }
        }
        m_pLabelInfo->setText(text_pos+"\n"+text_rgb+"\n"+text_gray);
    }

    if(m_bPress && m_itemType == ItemType::Drag){
//        QPointF disPointF = scenePos - this->mapToScene(m_lastPointF.toPoint());
        QPointF disPointF = viewPos - m_lastPointF;
        qDebug()<<"drag view"<<disPointF;
        m_lastPointF = viewPos;

        this->scene()->setSceneRect(this->scene()->sceneRect().x()-disPointF.x(),this->scene()->sceneRect().y()-disPointF.y(),
                                    this->scene()->sceneRect().width(),this->scene()->sceneRect().height());

//        this->scene()->update();
        return;
    }

    //2.修改在点击选择选项的时候，item在选中情况下无法move    m_itemType != ItemType::No的原因
    if(m_bPainter && m_bPress && m_itemType != ItemType::No){

        if(m_itemType == ItemType::Rect){
            //绘制矩形
            QPainterPath path;
            path.addRect(QRectF(m_pressPointF,viewPos));
            m_path = path;
        }else if(m_itemType == ItemType::EllipseItem){
            //绘制椭圆
            QPainterPath path;
            path.addEllipse(QRectF(m_pressPointF,viewPos));
            m_path = path;
        }else if(m_itemType == ItemType::Poly){
            QPainterPath path;
            QPolygonF poly(m_vecPoint_Poly);
            poly.insert(m_vecPoint_Poly.count(),scenePos);  //将最后一点替换成掉
            path.addPolygon(this->mapFromScene(poly));
            m_path = path;

        }else if(m_itemType == ItemType::Region){
            //鼠标绘制任意区域
            m_vecPoint_Region.append(scenePos);
            QPainterPath path;
            QPolygonF poly(m_vecPoint_Region);
            path.addPolygon(poly);
            m_path = this->mapFromScene(path);
        }else if(m_itemType == ItemType::Line){
            m_Line.setPoints(m_pressPointF_scene.toPoint(),scenePos.toPoint());
            m_path = QPainterPath(this->mapFromScene(m_pressPointF_scene));
            m_path.lineTo(this->mapFromScene(scenePos));

        }else if(m_itemType == ItemType::polyLine){

        }else if(m_itemType == ItemType::Point || m_itemType == ItemType::NoPoint){
            //鼠标绘制(擦除)

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


            //合并区域
            QPainterPath path;
            path.addPolygon(polygonF);

            XVRegion region = createPolygon(polygonF);

            if(m_itemType == ItemType::Point){
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

            if(m_itemType == ItemType::Point){
                m_region = slot_CombineRegion(m_region,region1,XVCombineRegionsType::Union);
            }else{
                m_region = slot_CombineRegion(m_region,region1,XVCombineRegionsType::Difference);
            }
            analysis_region(m_region);
        }
        this->scene()->update();
    }else{
        QGraphicsView::mouseMoveEvent(event);
    }
    m_lastPointF = viewPos;

}

void VisionGraphView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    QPoint viewPos = event->pos();//获取视口坐标
    QPointF scenePos = this->mapToScene(viewPos);//将视口坐标转换为场景坐标

    //检测鼠标点击是否点击在当前的可编辑的控件中
    m_bPress = true;
    m_pressPointF = viewPos;
    m_pressPointF_scene = scenePos;

    if(m_itemType == ItemType::Zoom){
        //缩放
        if(m_bZoom){
            //放大
            emit signal_wheel(1);
        }else{
            //缩小
            emit signal_wheel(-1);
        }
        return;
    }

    if(m_bPainter){
        if(event->button() == Qt::RightButton){
            if(m_itemType == ItemType::Rect){

            }else if(m_itemType == ItemType::EllipseItem){

            }else if(m_itemType == ItemType::Poly){
                m_vecPoint_Poly.append(this->mapToScene(m_releasePointF.toPoint()));
                emit signal_Item_poly(m_vecPoint_Poly);

                QPainterPath path;
                m_path = path;

                m_bPainter = false;
                //多边形绘制完成，进行转换

                m_vecPoint_Poly.clear();
                //绘制多边形结束
            }
        }else if(event->button() == Qt::LeftButton){
            //绘制矩形
            if(m_itemType == ItemType::Rect){

            }else if(m_itemType == ItemType::EllipseItem){

            }else if(m_itemType == ItemType::Poly){

                m_vecPoint_Poly.append(m_pressPointF_scene);

            }else if(m_itemType == ItemType::CrossPoint){

                emit signal_Item_point(m_pressPointF_scene);

            }else if(m_itemType == ItemType::Line){

            }else if(m_itemType == ItemType::polyLine){

            }else if(m_itemType == ItemType::Point || m_itemType == ItemType::NoPoint){

                //计算区域
                QPainterPath path1;
                path1.addEllipse(viewPos,m_qCircleR*m_scale,m_qCircleR*m_scale);

                QRectF rf11 = QRectF(this->mapToScene(QPoint(viewPos.x()-m_qCircleR*m_scale,viewPos.y()-m_qCircleR*m_scale)),
                                                      this->mapToScene(QPoint(viewPos.x()+m_qCircleR*m_scale,viewPos.y()+m_qCircleR*m_scale)));
                XVRegion region = createEllipse(rf11,rf11.topLeft(),0);

                if(m_itemType == ItemType::Point){
                    m_region = slot_CombineRegion(m_region,region,XVCombineRegionsType::Union);
                }else{
                    m_region = slot_CombineRegion(m_region,region,XVCombineRegionsType::Difference);
                }
                analysis_region(m_region);
            }
        }
    }


    this->scene()->update();
}

void VisionGraphView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);

    QPoint viewPos = event->pos();//获取视口坐标
    QPointF scenePos = this->mapToScene(viewPos);//将视口坐标转换为场景坐标

    m_releasePointF = viewPos;

    if(m_bPainter){

        if(m_itemType == Rect){
            QPointF topLeftPoint;
            QPointF bottomRightPoint;
            if(m_pressPointF_scene.x() < scenePos.x()){
                topLeftPoint.setX(m_pressPointF_scene.x());
                bottomRightPoint.setX(scenePos.x());
            }else{
                topLeftPoint.setX(scenePos.x());
                bottomRightPoint.setX(m_pressPointF_scene.x());
            }

            if(m_pressPointF_scene.y() < scenePos.y()){
                topLeftPoint.setY(m_pressPointF_scene.y());
                bottomRightPoint.setY(scenePos.y());
            }else{
                topLeftPoint.setY(scenePos.y());
                bottomRightPoint.setY(m_pressPointF_scene.y());
            }

            emit signal_Item(m_itemType,QRectF(topLeftPoint,bottomRightPoint));

            QPainterPath path;
            m_path = path;

            m_bPainter = false;
        }else if(m_itemType == EllipseItem){

            QPointF topLeftPoint;
            QPointF bottomRightPoint;
            if(m_pressPointF_scene.x() < scenePos.x()){
                topLeftPoint.setX(m_pressPointF_scene.x());
                bottomRightPoint.setX(scenePos.x());
            }else{
                topLeftPoint.setX(scenePos.x());
                bottomRightPoint.setX(m_pressPointF_scene.x());
            }

            if(m_pressPointF_scene.y() < scenePos.y()){
                topLeftPoint.setY(m_pressPointF_scene.y());
                bottomRightPoint.setY(scenePos.y());
            }else{
                topLeftPoint.setY(scenePos.y());
                bottomRightPoint.setY(m_pressPointF_scene.y());
            }

            emit signal_Item(m_itemType,QRectF(topLeftPoint,bottomRightPoint));

            QPainterPath path;
            m_path = path;

            m_bPainter = false;
        }else if(m_itemType == ItemType::Line){

            QPainterPath path;
            m_path = path;

            signal_Item_Line(m_Line);
            m_bPainter = false;

        }else if(m_itemType == ItemType::polyLine){

        }else if(m_itemType == ItemType::CrossPoint){
            m_bPainter = false;
        }else if(m_itemType == ItemType::Point || m_itemType == ItemType::NoPoint){
            //对于鼠标绘制，鼠标释放为一次记录
            push_region(m_region);
        }else if(m_itemType == ItemType::Poly){

        }else if(m_itemType == ItemType::Region){
            //鼠标释放后，将鼠标绘制的任意区域转换成算法提供的区域
            XVRegion region = createPolygon(this->mapToScene(m_path).toFillPolygon());
            m_region = slot_CombineRegion(m_region,region,XVCombineRegionsType::Union);
            push_region(m_region);
            analysis_region(m_region);

            QPainterPath path;
            m_path = path;
            m_vecPoint_Region.clear();
            this->scene()->update();
        }
    }

    m_lstPoint.clear();
    m_bPress = false;
}

void VisionGraphView::wheelEvent(QWheelEvent *event)
{
    emit signal_wheel(event->delta());
}

void VisionGraphView::enterEvent(QEvent *event)
{
    QGraphicsView::enterEvent(event);

    if(m_itemType != ItemType::No){
        if(m_itemType == ItemType::Point || m_itemType == ItemType::NoPoint){
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

    //设置鼠标所在位置的信息显示
    if(m_itemType == ItemType::No || m_itemType == ItemType::Zoom)
    {
//        m_pMouseInfo_Label->show();
    }else{
//        m_pMouseInfo_Label->hide();
    }
}

void VisionGraphView::leaveEvent(QEvent *event)
{
    m_pMouseInfo_Label->hide();
}

void VisionGraphView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);


    QPainter painter(this->viewport());    
    painter.setRenderHint(QPainter::Antialiasing,true);

    if(m_bFrameVisible){
        painter.setPen(QPen(m_FrameColor,0));
        painter.drawPolygon(this->mapFromScene(m_frameRect));
    }

    painter.setPen(QPen(brushColor,0));  //区域采用填充的颜色，原因自己想
    painter.setBrush(brushColor);


    if(m_bPainter){
    }

    painter.drawPath(m_path);

    if(m_clearAll){
        m_clearAll = false;
    }

    painter.setPen(QPen(brushColor,m_scale));  //区域采用填充的颜色，原因自己想
    qDebug()<<painter.pen().width()<<painter.pen().widthF();
    QVector<QLineF> vecLines;
    for(int i=0;i<m_vecLines.size();i++){
        QLineF lineF = QLineF(this->mapFromScene(m_vecLines.at(i).p1()),this->mapFromScene(m_vecLines.at(i).p2()));
        vecLines.append(lineF);
//        if(i % 2 == 0){
//            painter.drawLine(lineF);

////            painter.setPen(QPen(Qt::red,m_scale));
//        }else{
////            painter.setPen(QPen(Qt::blue,m_scale));
//        }
    }
    painter.drawLines(vecLines);
}

void VisionGraphView::setItemType(ItemType type){
    m_bPainter = true;
    m_itemType = type;

    m_vecPoint_Poly.clear();  //记录多边形的操作的点
    m_vecPoint_Region.clear();  //记录任意区域的操作的点

    if(m_itemType != ItemType::No){
        if(m_itemType == ItemType::Point || m_itemType == ItemType::NoPoint){
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
//    scale(1/m_scale, 1/m_scale);
    qreal scaleTemp = scaleFactor/m_scale;  //获取本次缩放相对于上次缩放的比例
    m_scale = scaleFactor;
    scale(scaleTemp, scaleTemp);
//    qDebug()<<m_scale<<scaleTemp;

    if(m_itemType == ItemType::Point || m_itemType == ItemType::NoPoint){
        //修改鼠标为绘图样式
        QCursor cursor = QCursor(QPixmap(iconPath+"cursor-size_Circle.png").scaled(m_qCircleR*2*m_scale,m_qCircleR*2*m_scale,
                                                                                   Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        this->setCursor(cursor);
        viewCursor = this->cursor();
    }

//    this->viewport()->update();
    this->scene()->update();
    return;

}

void VisionGraphView::back_region()
{
//    m_iIndex_Region++;
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

    m_clearAll = true;

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
    qDebug()<<this->width()<<this->height() << "111111111" <<this->sceneRect();
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
    qDebug()<<"setViewRegion_size  "<<w<<h;
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
    this->scene()->setSceneRect((m_frameRect.width()-this->width())/2,(m_frameRect.height()-this->height())/2,
                                this->scene()->sceneRect().width(),this->scene()->sceneRect().height());
}

void VisionGraphView::itemCursorToViewCursor()
{
    if(m_itemType != ItemType::No){
        if(m_itemType == ItemType::Point || m_itemType == ItemType::NoPoint){
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


void VisionGraphView::slot_updateItem(ItemType type, QPainterPath path)
{
    //编辑的控件在未确定之前，不调用算法生成点集合，临时绘制    item版本中作废
    m_path = this->mapFromScene(path);
}

void VisionGraphView::slot_updatePath(bool selected, VisionItem *item,ItemType type,QRectF rf,QPointF leftTop,qreal angle)
{
    if(!selected){
        //编辑完成，获取已经确定的区域的点集合，同时将对应的临时path清空
        rf =  QRectF((rf.topLeft()),(rf.bottomRight()));
        XVCreateRegionOut regionOut;
        if(type == Rect){


            XVRegion region = createRectangle(rf,leftTop,angle);

            m_region = slot_CombineRegion(m_region,region,Union);

            push_region(m_region);
            analysis_region(m_region);

            QPainterPath path;
            m_path = path;

        }else if(type == EllipseItem){
            XVRegion region = createEllipse(rf,leftTop,angle);

            m_region = slot_CombineRegion(m_region,region,Union);

            push_region(m_region);
            analysis_region(m_region);

            //给path赋值一个空path即可清空
            QPainterPath path;
            m_path = path;
        }

        item->hide();item->deleteLater();item = NULL;
    }
    this->scene()->update();
}

void VisionGraphView::slot_CreatePolygonF(bool selected, VisionItem *item, ItemType type, QVector<QPointF> vecPointF)
{
    if(selected)
        return;


    QPolygonF polyF(vecPointF);

    XVRegion region = createPolygon(polyF);

    m_region = slot_CombineRegion(m_region,region,Union);

    push_region(m_region);
    analysis_region(m_region);

    QPainterPath path;
    m_path = path;

    item->hide();item->deleteLater();item = NULL;
    this->scene()->update();
}

XVRegion VisionGraphView::slot_CombineRegion(XVRegion region1, XVRegion region2, XVCombineRegionsType combineType)
{
    XVCombineRegionsIn xvCombineRegionsIn;
    xvCombineRegionsIn.inCombineRegionsType = combineType;
    xvCombineRegionsIn.inRegion1 = &region1;
    xvCombineRegionsIn.inRegion2 = &region2;

    XVCombineRegionsOut xvCombineRegionsOut;


    XVCombineRegions(xvCombineRegionsIn,xvCombineRegionsOut);

    return xvCombineRegionsOut.RegionOut;

}

QVector<QLineF> VisionGraphView::analysis_region(XVRegion region)
{
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

    return m_vecLines;
}

XVRegion VisionGraphView::createPolygon(QPolygonF polygonF)
{
    XVCreateRegionOut regionOut;

    XVPath xvPath;
    vector<XVPoint2D> vec_point2D;

    for(int i=0;i<polygonF.count();i++){
        XVPoint2D point2D;
        point2D.x = polygonF.at(i).x();
        point2D.y = polygonF.at(i).y();
        vec_point2D.push_back(point2D);
    }
    xvPath.arrayPoint2D = vec_point2D;

    regionIn.inType = XVCreateRegionType::Polygon;
    regionIn.inFrameWidth = m_frameRect.width();
    regionIn.inFrameHeight = m_frameRect.height();
    regionIn.inPolygon = xvPath;

    XVCreateRegion(regionIn,regionOut);

    XVRegion region;

    region = regionOut.outregion;

    return region;
}

//XVRegion VisionGraphView::createCircle(QRectF rf)
//{

//}

XVRegion VisionGraphView::createEllipse(QRectF rf,QPointF leftTop, qreal angle)
{
    rf =  QRectF((rf.topLeft()),(rf.bottomRight()));
    XVCreateRegionOut regionOut;

    if(rf.width() == rf.height()){
        XVCircle2D xvCircle;
        XVPoint2D centerPointF;
        centerPointF.x = (float)(rf.x()+rf.width()/2);
        centerPointF.y = (float)(rf.y()+rf.height()/2);
        xvCircle.center = centerPointF;
        xvCircle.radius = rf.width()/2;


        //没有圆
        regionIn.inType = XVCreateRegionType::Circle;
        regionIn.inFrameWidth = m_frameRect.width();
        regionIn.inFrameHeight = m_frameRect.height();
        regionIn.inCircle2D = xvCircle;

        XVBox xvBox;
        XVPoint2D left;
        left.x = (float)leftTop.x();
        left.y = (float)leftTop.y();
        xvBox.origin = left;
        xvBox.width = (float)rf.width();
        xvBox.height = (float)rf.height();
        regionIn.inBox = xvBox;
    }else{
        XVRectangle2D xvRect;
        XVPoint2D leftPoint;
        leftPoint.x = (float)leftTop.x();
        leftPoint.y = (float)leftTop.y();
        xvRect.origin = leftPoint;
        xvRect.angle = angle;
        xvRect.height = (float)rf.height();
        xvRect.width = (float)rf.width();

        regionIn.inType = XVCreateRegionType::Ellipse;
        regionIn.inFrameWidth = m_frameRect.width();
        regionIn.inFrameHeight = m_frameRect.height();
        regionIn.inRectangle =xvRect;

        XVBox xvBox;
        xvBox.origin = leftPoint;
        xvBox.width = (float)rf.width();
        xvBox.height = (float)rf.height();
        regionIn.inBox = xvBox;
    }


    XVCreateRegion(regionIn,regionOut);

    XVRegion region;

    region = regionOut.outregion;

    return region;
}

XVRegion VisionGraphView::createRectangle(QRectF rf,QPointF leftTop, qreal angle)
{
    rf =  QRectF((rf.topLeft()),(rf.bottomRight()));
    XVCreateRegionOut regionOut;

    XVRectangle2D xvRect;
    XVPoint2D leftPoint;
    leftPoint.x = (float)leftTop.x();
    leftPoint.y = (float)leftTop.y();
    xvRect.origin = leftPoint;
    xvRect.angle = angle;
    xvRect.height = (float)rf.height();
    xvRect.width = (float)rf.width();

    regionIn.inType = XVCreateRegionType::Rectangle;
    regionIn.inFrameWidth = m_frameRect.width();
    regionIn.inFrameHeight = m_frameRect.height();
    regionIn.inRectangle =xvRect;

    XVBox xvBox;
    xvBox.origin = leftPoint;
    xvBox.width = (float)rf.width();
    xvBox.height = (float)rf.height();
    regionIn.inBox = xvBox;


    XVCreateRegion(regionIn,regionOut);

    XVRegion region = regionOut.outregion;

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

void VisionGraphView::slotUpdateViewInfo_Pos()
{
    qDebug()<<this->x()<<this->y()<<this->width()<<this->height() << "22222222" <<this->sceneRect();
//    m_frameRect.setRect(this->x(),this->y(),this->width(),this->height());
//    this->scene()->sceneRect().setTopLeft(QPointF((this->width()-this->scene()->sceneRect().width())/2,(this->height()-this->scene()->sceneRect().height())/2));
//    m_frameRect.setRect(this->scene()->sceneRect().x(),this->scene()->sceneRect().y(),
//                        this->scene()->sceneRect().width(),this->scene()->sceneRect().height());

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

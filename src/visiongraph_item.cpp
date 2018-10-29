#include "visiongraph_item.h"

#include <QDebug>
#include <QtMath>
#include <QFileDialog>
#include <QDateTime>


VisionGraph_Item::VisionGraph_Item(ItemModel model, QWidget *parent) : QFrame(parent)
{
    setFixedSize(1200,800);
    mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    m_model = model;

    initScene();

//    initLayout();
}



void VisionGraph_Item::initScene()
{
    sceneWidget = new QWidget(this);
    sceneWidget->setFixedSize(800,600);

    view = new VisionGraphView(sceneWidget);
    QObject::connect(view,SIGNAL(signal_Item(ItemType,QRectF)),this,SLOT(slot_addItem(ItemType,QRectF)));
    QObject::connect(view,SIGNAL(signal_Item_poly(QVector<QPointF>)),this,SLOT(slot_addPoly(QVector<QPointF>)));
    QObject::connect(view,SIGNAL(signal_Item_point(QPointF)),this,SLOT(slot_addPoint(QPointF)));
    QObject::connect(view,SIGNAL(signal_Item_Line(QLine)),this,SLOT(slot_addLine(QLine)));
    QObject::connect(view,SIGNAL(signal_Move(QPointF)),this,SLOT(slot_mouseMove(QPointF)));
    QObject::connect(view,SIGNAL(signal_wheel(qreal)),this,SLOT(slot_wheel(qreal)));

    scene = new VisionGraphScene(sceneWidget);
    scene->setSceneRect(0,0,800,600);
    view->setScene(scene);
    view->setSceneRect(0,0,800,600);

    m_bkPixmapItem = new QGraphicsPixmapItem();
    m_bkPixmapItem->setPixmap(QPixmap(":/bgk.bmp").scaled(800,600));
    scene->addItem(m_bkPixmapItem);

    m_mousePixmap = new QGraphicsPixmapItem();
    m_mousePixmap->setPos(scene->width()/2-10,scene->height()/2-10);
    m_mousePixmap->setPixmap(QPixmap(":/icon/cursor-size_Circle.png").scaled(10*2,10*2));
    scene->addItem(m_mousePixmap);
    m_mousePixmap->hide();


    //显示操作信息
//    label_Operation = new QLabel(this);
//    label_Operation->setText(QStringLiteral(""));
//    label_Operation->show();
//    label_Operation->setFixedWidth(400);

}


void VisionGraph_Item::initTool_V()
{
    //选中按钮---绘制规则形状的时候，绘制完成后默认选中，此时高亮，其他时间都是灰色

    sys_selected_action = new QAction(QIcon(":/icon/select.png"),QStringLiteral(""));
    sys_selected_action->setIconText(QStringLiteral("选择"));
    connect(sys_selected_action,SIGNAL(triggered(bool)),this,SLOT(slot_selected_action()));
    //拖动按钮---拖动整个绘制的区域的位置---目前暂时不提供（后期加）
    sys_drag_action = new QAction(QIcon(":/icon/drag.png"),QStringLiteral("拖动当前视图"));
    sys_drag_action->setIconText(QStringLiteral("拖动"));
    connect(sys_drag_action,SIGNAL(triggered(bool)),this,SLOT(slot_drag_action()));
    //放大镜功能
    sys_zoom_action = new QAction(QIcon(":/icon/zoom.png"),QStringLiteral("缩放"));
    sys_zoom_action->setIconText(QStringLiteral("缩放"));
    connect(sys_zoom_action,SIGNAL(triggered(bool)),this,SLOT(slot_zoom_action()));


    //鼠标擦除
    sys_mouseClear_action = new QAction(QIcon(":/icon/clear.png"),QStringLiteral("擦除"));
    sys_mouseClear_action->setIconText(QStringLiteral("擦除"));
    sys_mouseClear_action->setText("mouseClear");
    connect(sys_mouseClear_action,SIGNAL(triggered(bool)),this,SLOT(slot_mouseClear_action()));
    //鼠标绘制
    sys_mousePainter_action = new QAction(QIcon(":/icon/painter.png"),QStringLiteral("绘制"));
    sys_mousePainter_action->setIconText(QStringLiteral("绘制"));
    sys_mousePainter_action->setText("mousePainter");
    connect(sys_mousePainter_action,SIGNAL(triggered(bool)),this,SLOT(slot_mousePainter_action()));

    //矩形
    sys_rect_action = new QAction(QIcon(":/icon/rect.png"),QStringLiteral("新建一个矩形区域"));
    sys_rect_action->setIconText(QStringLiteral("矩形"));
    sys_rect_action->setText("rectangle");
    connect(sys_rect_action,SIGNAL(triggered(bool)),this,SLOT(slot_rect_action()));
    //椭圆
    sys_ellipse_action = new QAction(QIcon(":/icon/ellipse.png"),QStringLiteral("新建一个椭圆区域"));
    sys_ellipse_action->setIconText(QStringLiteral("椭圆或者圆"));
    sys_ellipse_action->setText("ellipse");
    connect(sys_ellipse_action,SIGNAL(triggered(bool)),this,SLOT(slot_ellipse_action()));
    //不规则多边形---直线连接各点
    sys_poly_action = new QAction(QIcon(":/icon/poly.png"),QStringLiteral("新建一个不规则多边形区域"));
    sys_poly_action->setIconText(QStringLiteral("多边形"));
    sys_poly_action->setText("poly");
    connect(sys_poly_action,SIGNAL(triggered(bool)),this,SLOT(slot_poly_action()));
    //不规则圆形---曲线连接各点
    sys_poly_elli_action = new QAction(QIcon(":/icon/poly_elli.png"),QStringLiteral("任意区域：绘制不规则区域"));
    sys_poly_elli_action->setIconText(QStringLiteral("任意区域"));
    sys_poly_elli_action->setText("region");
    connect(sys_poly_elli_action,SIGNAL(triggered(bool)),this,SLOT(slot_poly_elli_action()));

    sys_point_action = new QAction(QIcon(":/icon/point.png"),QStringLiteral("绘制点"));
    sys_point_action->setIconText(QStringLiteral("点"));
    sys_point_action->setText("point");
    connect(sys_point_action,SIGNAL(triggered(bool)),this,SLOT(slot_point_action()));

    sys_line_action = new QAction(QIcon(":/icon/line.png"),QStringLiteral("绘制直线"));
    sys_line_action->setIconText(QStringLiteral("直线"));
    sys_line_action->setText("line");
    connect(sys_line_action,SIGNAL(triggered(bool)),this,SLOT(slot_line_action()));

    sys_polyLine_action = new QAction(QIcon(":/icon/polyline.png"),QStringLiteral("绘制折线"));
    sys_polyLine_action->setIconText(QStringLiteral("折线"));
    sys_polyLine_action->setText("polyLine");
    connect(sys_polyLine_action,SIGNAL(triggered(bool)),this,SLOT(slot_polyLine_action()));

    //调整鼠标的大小--针对鼠标擦除和鼠标绘制

    QAction *action = new QAction();
    action->setEnabled(false);
//    action->setDisabled(true);

    tool_painter = new QToolBar;
    //    tool_painter->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tool_painter->setMinimumHeight(20);
    tool_painter->setMovable(false);

    tool_painter->addAction(sys_selected_action);
    tool_painter->addAction(sys_drag_action);
    tool_painter->addAction(sys_zoom_action);
    tool_painter->addAction(action);

    tool_painter->addAction(action);

    if(m_model == ItemModel::un_self){
        tool_painter->addAction(sys_rect_action);
        tool_painter->addAction(sys_ellipse_action);
        tool_painter->addAction(sys_poly_action);
        tool_painter->addAction(sys_point_action);
        tool_painter->addAction(sys_line_action);
        tool_painter->addAction(action);
    }
}

void VisionGraph_Item::initTool_H()
{
    sys_open_project = new QAction(QIcon(":/icon/open.png"),QStringLiteral("打开"));
    sys_open_project->setIconText(QStringLiteral("打开"));
    connect(sys_open_project,SIGNAL(triggered(bool)),this,SLOT(slot_open_project()));

    sys_save_action = new QAction(QIcon(":/icon/save.png"),QStringLiteral("保存"));
    sys_save_action->setIconText(QStringLiteral("保存"));
    connect(sys_save_action,SIGNAL(triggered(bool)),this,SLOT(slot_save_action()));

    //撤销按钮（回滚）历史
    sys_front_action = new QAction(QIcon(":/icon/back.png"),QStringLiteral("撤销"));
    sys_front_action->setIconText(QStringLiteral("撤销"));
    connect(sys_front_action,SIGNAL(triggered(bool)),this,SLOT(slot_front_action()));
    //撤销按钮（后滚）未来
    sys_next_action = new QAction(QIcon(":/icon/front.png"),QStringLiteral("恢复"));
    sys_next_action->setIconText(QStringLiteral("恢复"));
    connect(sys_next_action,SIGNAL(triggered(bool)),this,SLOT(slot_next_action()));
    //清空绘图区域
    sys_clear_action = new QAction(QIcon(":/icon/delect.png"),QStringLiteral("清理"));
    sys_clear_action->setIconText(QStringLiteral("清理"));
    connect(sys_clear_action,SIGNAL(triggered(bool)),this,SLOT(slot_clear_action()));

    sys_remove_item = new QAction(QIcon(":/icon/remove.png"),QStringLiteral("删除当前选中的item"));
    sys_remove_item->setIconText(QStringLiteral("删除"));
    connect(sys_remove_item,SIGNAL(triggered(bool)),this,SLOT(slot_removeItem_action()));
    //调整鼠标的大小--针对鼠标擦除和鼠标绘制

    //显示区域的信息，view的大小，缩放比例，鼠标的信息
    QWidget *infoWidget = new QWidget();

    QLabel *label_w = new QLabel;
    label_w->setText(QStringLiteral("宽度:"));
    label_w->show();

    QLineEdit *lineEdit_w = new QLineEdit;
    lineEdit_w->setText(QString::number(1200));
    lineEdit_w->setFixedWidth(50);
    lineEdit_w->show();

    QLabel *label_h = new QLabel;
    label_h->setText(QStringLiteral("高度:"));
    label_h->show();

    QLineEdit *lineEdit_h = new QLineEdit;
    lineEdit_h->setText(QString::number(800));
    lineEdit_h->setFixedWidth(50);
    lineEdit_w->show();

    QLabel *label_size = new QLabel;
    label_size->setText(QStringLiteral("尺寸:"));
    label_size->show();

    comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->lineEdit()->setValidator(new QIntValidator(0, 100,comboBox->lineEdit())); //0, 100为输入的数字值范围
    comboBox->addItem("10%");
    comboBox->addItem("25%");
    comboBox->addItem("50%");
    comboBox->addItem("100%");
    comboBox->addItem("200%");
    comboBox->addItem("500%");
    comboBox->setCurrentText("100%");
    connect(comboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(slot_SizeChanged(QString)));

    if(m_toolButtonDirection_operation == ToolButtonDirection::leftDirection ||
            m_toolButtonDirection_operation == ToolButtonDirection::rightDirection){
        QVBoxLayout* vBoxLayout = new QVBoxLayout;
        infoWidget->setLayout(vBoxLayout);

        vBoxLayout->addWidget(label_w);
        vBoxLayout->addWidget(lineEdit_w);
        vBoxLayout->addWidget(label_h);
        vBoxLayout->addWidget(lineEdit_h);
        vBoxLayout->addSpacing(50);
        vBoxLayout->addWidget(label_size);
        vBoxLayout->addWidget(comboBox);
        vBoxLayout->addStretch();
    }else{
        QHBoxLayout* hBoxLayout = new QHBoxLayout;
        infoWidget->setLayout(hBoxLayout);


        hBoxLayout->addWidget(label_w);
        hBoxLayout->addWidget(lineEdit_w);
        hBoxLayout->addWidget(label_h);
        hBoxLayout->addWidget(lineEdit_h);
        hBoxLayout->addSpacing(50);
        hBoxLayout->addWidget(label_size);
        hBoxLayout->addWidget(comboBox);
        hBoxLayout->addStretch();
    }

    infoWidget->show();

    tool_operation = new QToolBar;
    //    tool_operation->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tool_operation->setMovable(false);

    tool_operation->addAction(sys_open_project);
    tool_operation->addAction(sys_save_action);

    tool_operation->addAction(sys_clear_action);
    tool_operation->addAction(sys_remove_item);

    tool_operation->addSeparator();

    tool_operation->addWidget(infoWidget);


}

void VisionGraph_Item::initLayout()
{
    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    QVBoxLayout *vBoxLayout = new QVBoxLayout;

    initTool_H();
    initTool_V();

    if(m_toolButtonDirection_painter == ToolButtonDirection::leftDirection){
        tool_painter->setOrientation(Qt::Vertical);

        if(m_toolButtonDirection_operation == ToolButtonDirection::leftDirection){
            tool_operation->setOrientation(Qt::Vertical);
            hBoxLayout->addWidget(tool_operation);
            hBoxLayout->addWidget(tool_painter);
            hBoxLayout->addWidget(sceneWidget);
            hBoxLayout->addStretch();

            vBoxLayout->addLayout(hBoxLayout);
            vBoxLayout->addStretch();
        }else if(m_toolButtonDirection_operation == ToolButtonDirection::topDirection){

            hBoxLayout->addWidget(tool_painter);
            hBoxLayout->addWidget(sceneWidget);
            hBoxLayout->addStretch();

            vBoxLayout->addWidget(tool_operation);
            vBoxLayout->addLayout(hBoxLayout);
            vBoxLayout->addStretch();
        }else if(m_toolButtonDirection_operation == ToolButtonDirection::rightDirection){
            tool_operation->setOrientation(Qt::Vertical);

            hBoxLayout->addWidget(tool_painter);
            hBoxLayout->addWidget(sceneWidget);
            hBoxLayout->addWidget(tool_operation);
            hBoxLayout->addStretch();

            vBoxLayout->addLayout(hBoxLayout);
            vBoxLayout->addStretch();
        }else if(m_toolButtonDirection_operation == ToolButtonDirection::bottomDirection){
            hBoxLayout->addWidget(tool_painter);
            hBoxLayout->addWidget(sceneWidget);
            hBoxLayout->addStretch();

            vBoxLayout->addLayout(hBoxLayout);
            vBoxLayout->addWidget(tool_operation);
            vBoxLayout->addStretch();
        }


    }else if(m_toolButtonDirection_painter == ToolButtonDirection::topDirection){

        if(m_toolButtonDirection_operation == ToolButtonDirection::leftDirection){
            tool_operation->setOrientation(Qt::Vertical);
            hBoxLayout->addWidget(tool_operation);
            hBoxLayout->addWidget(sceneWidget);
            hBoxLayout->addStretch();

            vBoxLayout->addWidget(tool_painter);
            vBoxLayout->addLayout(hBoxLayout);
            vBoxLayout->addStretch();

        }else if(m_toolButtonDirection_operation == ToolButtonDirection::topDirection){

            vBoxLayout->addLayout(hBoxLayout);
            vBoxLayout->addWidget(tool_operation);
            vBoxLayout->addWidget(tool_painter);
            vBoxLayout->addWidget(sceneWidget);
            vBoxLayout->addStretch();

        }else if(m_toolButtonDirection_operation == ToolButtonDirection::rightDirection){
            tool_operation->setOrientation(Qt::Vertical);

            hBoxLayout->addWidget(sceneWidget);
            hBoxLayout->addWidget(tool_operation);
            hBoxLayout->addStretch();

            vBoxLayout->addWidget(tool_painter);
            vBoxLayout->addLayout(hBoxLayout);
            vBoxLayout->addStretch();
        }else if(m_toolButtonDirection_operation == ToolButtonDirection::bottomDirection){

            vBoxLayout->addWidget(tool_painter);
            vBoxLayout->addLayout(hBoxLayout);
            vBoxLayout->addWidget(tool_operation);
            vBoxLayout->addStretch();
        }

    }else if(m_toolButtonDirection_painter == ToolButtonDirection::rightDirection){
        tool_painter->setOrientation(Qt::Vertical);

        if(m_toolButtonDirection_operation == ToolButtonDirection::leftDirection){
            tool_operation->setOrientation(Qt::Vertical);

            hBoxLayout->addWidget(tool_operation);
            hBoxLayout->addWidget(sceneWidget);
            hBoxLayout->addWidget(tool_painter);
            hBoxLayout->addStretch();

            vBoxLayout->addLayout(hBoxLayout);
            vBoxLayout->addStretch();
        }else if(m_toolButtonDirection_operation == ToolButtonDirection::topDirection){

            hBoxLayout->addWidget(sceneWidget);
            hBoxLayout->addWidget(tool_painter);
            hBoxLayout->addStretch();

            vBoxLayout->addWidget(tool_operation);
            vBoxLayout->addLayout(hBoxLayout);
            vBoxLayout->addStretch();
        }else if(m_toolButtonDirection_operation == ToolButtonDirection::rightDirection){
            tool_operation->setOrientation(Qt::Vertical);

            hBoxLayout->addWidget(sceneWidget);
            hBoxLayout->addWidget(tool_painter);
            hBoxLayout->addWidget(tool_operation);
            hBoxLayout->addStretch();

            vBoxLayout->addLayout(hBoxLayout);
            vBoxLayout->addStretch();
        }else if(m_toolButtonDirection_operation == ToolButtonDirection::bottomDirection){
            hBoxLayout->addWidget(sceneWidget);
            hBoxLayout->addWidget(tool_painter);
            hBoxLayout->addStretch();

            vBoxLayout->addLayout(hBoxLayout);
            vBoxLayout->addWidget(tool_operation);
            vBoxLayout->addStretch();
        }

    }else if(m_toolButtonDirection_painter == ToolButtonDirection::bottomDirection){

        if(m_toolButtonDirection_operation == ToolButtonDirection::leftDirection){
            tool_operation->setOrientation(Qt::Vertical);
            hBoxLayout->addWidget(tool_operation);
            hBoxLayout->addWidget(sceneWidget);

            vBoxLayout->addLayout(hBoxLayout);
            vBoxLayout->addWidget(tool_painter);
        }else if(m_toolButtonDirection_operation == ToolButtonDirection::topDirection){

            vBoxLayout->addLayout(hBoxLayout);
            vBoxLayout->addWidget(tool_operation);
            vBoxLayout->addWidget(sceneWidget);
            vBoxLayout->addWidget(tool_painter);
        }else if(m_toolButtonDirection_operation == ToolButtonDirection::rightDirection){
            tool_operation->setOrientation(Qt::Vertical);

            hBoxLayout->addWidget(sceneWidget);
            hBoxLayout->addWidget(tool_operation);

            vBoxLayout->addLayout(hBoxLayout);
            vBoxLayout->addWidget(tool_painter);

        }else if(m_toolButtonDirection_operation == ToolButtonDirection::bottomDirection){

            vBoxLayout->addWidget(sceneWidget);
            vBoxLayout->addWidget(tool_operation);
            vBoxLayout->addWidget(tool_operation);
        }
    }

    mainLayout->addLayout(vBoxLayout);
    mainLayout->addStretch();
}



void VisionGraph_Item::addRect(QRectF rf, bool bEdit)
{
    if(bEdit){
        VisionRectItem* item = new VisionRectItem(true);
        QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
        QObject::connect(item,&QObject::destroyed,[=](){
            m_curVisionItem = nullptr;
        });
        item->setRect(rf);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);

    }
}

void VisionGraph_Item::addEllipse(QRectF rf)
{
    VisionEllipseItem *item = new VisionEllipseItem(true);
    QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
    QObject::connect(item,&QObject::destroyed,[=](){
        m_curVisionItem = nullptr;
    });
    item->setRect(rf);
    scene->addItem(item);
    m_curVisionItem = item;
    m_lstItem.push_back(item);

}

void VisionGraph_Item::addLine(QLine line)
{
    VisionLineItem *item = new VisionLineItem();
    QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
    QObject::connect(item,&QObject::destroyed,[=](){
        m_curVisionItem = nullptr;
    });
    item->setLine(line.p1(),line.p2());
    scene->addItem(item);
    m_curVisionItem = item;
    m_lstItem.push_back(item);
}

void VisionGraph_Item::addLines(QList<QLine> lstLine)
{

}

void VisionGraph_Item::addPolygon(QVector<QPointF> vecPointF)
{
    VisionPolygon *item = new VisionPolygon();
    QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
    QObject::connect(item,&QObject::destroyed,[=](){
        m_curVisionItem = nullptr;
    });
    if(vecPointF.count() > 0){
        item->setPointFs(vecPointF,true);
    }else{
        item->setPointFs(vecPointF,false);
    }
    scene->addItem(item);
    m_curVisionItem = item;
    m_lstItem.push_back(item);
}

void VisionGraph_Item::addPoint(QPointF pointF)
{
    VisionCrossPointItem *item = new VisionCrossPointItem();
//    QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
    QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
//    QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QVector<QPointF>)),view,SLOT(slot_CreatePolygonF(bool,VisionItem*,ItemType,QVector<QPointF>)));
    QObject::connect(item,&QObject::destroyed,[=](){
        m_curVisionItem = nullptr;
    });
    item->setPoint(pointF);
    scene->addItem(item);
    m_curVisionItem = item;
    m_lstItem.push_back(item);
}


int VisionGraph_Item::setBkImg(QImage image)
{
    if (image.isNull())
        return -1;
    if (m_bkPixmapItem == NULL)
    {
        m_bkPixmapItem = new QGraphicsPixmapItem();
        scene->addItem(m_bkPixmapItem);
    }
    m_bkPixmapItem->setPixmap(QPixmap::fromImage(image));
    return 0;
}

void VisionGraph_Item::slot_selected_action()
{
    view->setItemType(ItemType::No);
    m_itemType = ItemType::No;
//    label_Operation->setText(QStringLiteral("无状态"));
}

void VisionGraph_Item::slot_drag_action()
{
    view->setItemType(ItemType::Drag);
    m_itemType = ItemType::Drag;
//    label_Operation->setText(QStringLiteral("通过鼠标的拖动，拖动视图区域"));
}

void VisionGraph_Item::slot_zoom_action()
{
    view->setItemType(ItemType::Zoom);
    m_itemType = ItemType::Zoom;
//    label_Operation->setText(QStringLiteral("通过鼠标的滚轮，缩放视图区域"));
}

void VisionGraph_Item::slot_mousePainter_action()
{
    view->setItemType(ItemType::Point);
    m_itemType = ItemType::Point;
//    label_Operation->setText(QStringLiteral("点击绘制任意图形"));

}

void VisionGraph_Item::slot_mouseClear_action()
{
    view->setItemType(ItemType::NoPoint);
    m_itemType = ItemType::NoPoint;
//    label_Operation->setText(QStringLiteral("点击绘制任意图形"));


}

void VisionGraph_Item::slot_save_action()
{

    if (m_bkPixmapItem == NULL) return;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                      "/",
                                                      tr("Images (*.png *.bmp *.jpg)"));
    if(fileName == ""){
        qDebug()<<"save is failure";
        return;
    }

    qDebug()<<fileName;
    QPixmap map = m_bkPixmapItem->pixmap();
    if (!map.isNull())
    {
        //默认采用时间命名法，
        /*
        QDateTime dataTime = QDateTime::currentDateTime();
        QString imageName = QString::number(dataTime.date().year())+QString::number(dataTime.date().month())+
                QString::number(dataTime.date().day())+"_"
                +QString::number(dataTime.time().hour())+QString::number(dataTime.time().minute())+
                QString::number(dataTime.time().second())+".bmp";
                */
//        map.save(fileName,"BMP");

        QImage image(scene->width(), scene->height(),QImage::Format_ARGB32);
        QPainter painter(&image);
        painter.setRenderHint(QPainter::Antialiasing);
        scene->render(&painter);

        bool saveSuccess =  image.save(fileName,"BMP");
        Q_ASSERT(saveSuccess == true);
    }
//    emit signal_SaveBkImg();
}

void VisionGraph_Item::slot_rect_action()
{
    view->setItemType(ItemType::Rect);
    m_itemType = ItemType::Rect;
//    label_Operation->setText(QStringLiteral("拖动到开始创建一个新区域 Rectangle"));

}

void VisionGraph_Item::slot_ellipse_action()
{
    view->setItemType(ItemType::EllipseItem);
    m_itemType = ItemType::EllipseItem;
//    label_Operation->setText(QStringLiteral("拖动到开始创建一个新区域 Ellipse"));

}

void VisionGraph_Item::slot_poly_action()
{
    view->setItemType(ItemType::Poly);
    m_itemType = ItemType::Poly;
//    label_Operation->setText(QStringLiteral("拖动到开始创建一个新区域 path"));

}

void VisionGraph_Item::slot_poly_elli_action()
{
    view->setItemType(ItemType::Region);
    m_itemType = ItemType::Region;
//    label_Operation->setText(QStringLiteral("点击，创建任意的多边形"));
}

void VisionGraph_Item::slot_point_action()
{
    view->setItemType(ItemType::CrossPoint);
    m_itemType = ItemType::CrossPoint;
//    label_Operation->setText(QStringLiteral("点击，创建一个点"));
}

void VisionGraph_Item::slot_line_action()
{
    view->setItemType(ItemType::Line);
    m_itemType = ItemType::Line;
//    label_Operation->setText(QStringLiteral("点击，创建一个线段"));
}

void VisionGraph_Item::slot_polyLine_action()
{
    view->setItemType(ItemType::polyLine);
    m_itemType = ItemType::polyLine;
//    label_Operation->setText(QStringLiteral("点击，创建折线段"));
}

void VisionGraph_Item::slot_open_project()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                      "/",
                                                      tr("Images (*.png *.bmp *.jpg)"));

    qDebug()<<fileName;
    if(fileName != ""){
        m_bkPixmapItem->setPixmap(QPixmap(fileName).scaled(800,600));
    }
}

void VisionGraph_Item::slot_front_action()
{
//    view->back_region();
}

void VisionGraph_Item::slot_next_action()
{
//    view->front_region();
}

void VisionGraph_Item::slot_clear_action()
{
    //清除当前的item
//    for(int i=0;i<m_lstItem.count();i++){
//        VisionItem* item = m_lstItem[i];
//        item->deleteLater();
//        item = NULL;
//    }
    view->clearPainter();
    for(int i=0;i<m_lstItem.count();i++){
        scene->removeItem(m_lstItem[i]);
        m_lstItem[i]->deleteLater();
        m_lstItem[i] = NULL;
    }
    m_lstItem.clear();
    m_curVisionItem = NULL;
//    scene->clear();  //会将scene中的所有的item都delete
}

void VisionGraph_Item::slot_removeItem_action()
{
    //直接进行筛选，不考虑当前的
    if(m_lstItem.count() == 0)
        return;

    for(int i=0;i<m_lstItem.count();i++){
        if(m_lstItem[i] == m_curVisionItem){
            m_lstItem.removeAt(i);
            break;
        }
    }
    scene->removeItem(m_curVisionItem);
    m_curVisionItem = NULL;

    /*
    qDebug()<<"remove curVisionItem";
    if(m_curVisionItem != NULL){
        if(!m_curVisionItem->getEdit()){
            qDebug()<<"m_curVisionItem is false";
            return;
        }

        for(int i=0;i<m_lstItem.count();i++){
            if(m_lstItem[i] == m_curVisionItem){
                m_lstItem.removeAt(i);
                break;
            }
        }
        scene->removeItem(m_curVisionItem);
        m_curVisionItem = NULL;
    }else{
        qDebug()<<"m_curVisionItem is NULL";
    }
    */
}

void VisionGraph_Item::slot_addItem(ItemType type, QRectF rf)
{
    if(type == Rect){
        addRect(rf);
    }else if(type == EllipseItem){
        addEllipse(rf);
    }
}

void VisionGraph_Item::slot_addPoly(QVector<QPointF> vecPointF)
{
    addPolygon(vecPointF);
}

void VisionGraph_Item::slot_addPoint(QPointF pointF)
{
    addPoint(pointF);
}

void VisionGraph_Item::slot_addLine(QLine line)
{
    addLine(line);
}

void VisionGraph_Item::slot_mouseMove(QPointF pointF)
{
    m_mousePixmap->hide();
}


QPainterPath VisionGraph_Item::and_Item(QPainterPath path1,QPainterPath path2)
{
    //获取到一个公共的区域，将该区域的表达式传给每个item，在绘制每个item 的时候，判断绘制的点是否在公共区域，在的话绘制特殊颜色，不在的话，绘制其他颜色
    //A和B的交集 属于A并且也属于B
    return (path1+path2)-(path1-path2)-(path2-path1);
}

QPainterPath VisionGraph_Item::sub_Item(QPainterPath path1,QPainterPath path2)
{
    //A和B的差集  属于A，但不属于B的点
    return path1.subtracted(path2);
}

QPainterPath VisionGraph_Item::or_Item(QPainterPath path1,QPainterPath path2)
{
    //A和B的并集 属于A或者属于B
    return path1.united(path2);
}

QPainterPath VisionGraph_Item::nor_Item(QPainterPath path1,QPainterPath path2)
{
    //A异或B，属于A并且不属于B 或者 属于B并且不属于A
    return (path2-path1)+(path1-path2);
}


void VisionGraph_Item::slot_Press(VisionItem *item, bool bSelected,bool bIn,qreal x,qreal y)
{
    //修改，该函数的触发，改成有基类VisionItem进行触发，限制在点击item的时候触发

    //修改哪些item的zValue的值，需要根据点击的pos来定位在该pos的item有哪些

    //change zValue

    //点击item，如果该item是被选中的，则直接改为未选中，同时判断其底部是否有其他的item
    //如果有，则将该item的zValue值设为5，同时将该item的状态设置为选中状态

    //需要对基类添加的函数，设置选中和未选中的接口，获取选中状态的接口,获取item的painterPath，获取坐标是否在item的有效区域内

    QList<VisionItem*> lstClickedItem;
//    qDebug()<<m_lstItem.count()<<x<<y;
    for(int i=0;i<m_lstItem.count();i++){
        //点击了某一个item的无效区域，该item的z值是0，显示是in area，
        //clicked some item's uneffect area, and this item's z value is 0, this if think it is in area
        //but this item’s mousePressEvent() will think the click event is uneffect,and no deal with

        //此处判断修改，改为传输坐标给item，返回值为该坐标是否在该item内部---   true-in  false-out
        if(m_lstItem[i]->getType() == ItemType::Rect){
            VisionRectItem* itemTest = (VisionRectItem*)m_lstItem[i];
            if(itemTest->getPosInArea(x,y)){
                qDebug()<<"VisionRectItem in of range";
                lstClickedItem.push_back(m_lstItem[i]);
            }else{
                qDebug()<<"VisionRectItem out of range";
            }
        }else if (m_lstItem[i]->getType() == ItemType::EllipseItem) {
            VisionEllipseItem* itemTest = (VisionEllipseItem*)m_lstItem[i];
            if(itemTest->getPosInArea(x,y)){
                qDebug()<<"VisionEllipseItem in of range";
                lstClickedItem.push_back(m_lstItem[i]);
            }else{
                qDebug()<<"VisionEllipseItem out of range";
            }
        }else if (m_lstItem[i]->getType() == ItemType::Poly) {
            VisionPolygon* itemTest = (VisionPolygon*)m_lstItem[i];
            if(itemTest->getPosInArea(x,y)){
                qDebug()<<"VisionPolygon in of range";
                lstClickedItem.push_back(m_lstItem[i]);
            }else{
                qDebug()<<"VisionPolygon out of range";
            }
        }else if(m_lstItem[i]->getType() == ItemType::CrossPoint){
            VisionCrossPointItem* itemTest = (VisionCrossPointItem*)m_lstItem[i];
            if(itemTest->getPosInArea(x,y)){
                qDebug()<<"VisionCrossPointItem in of range";
                lstClickedItem.push_back(m_lstItem[i]);
            }else{
                qDebug()<<"VisionCrossPointItem out of range";
            }
        }else if(m_lstItem[i]->getType() == ItemType::Line){
            VisionLineItem* itemTest = (VisionLineItem*)m_lstItem[i];
            if(itemTest->getPosInArea(x,y)){
                qDebug()<<"VisionLineItem in of range";
                lstClickedItem.push_back(m_lstItem[i]);
            }else{
                qDebug()<<"VisionLineItem out of range";
            }
        }else{
            VisionRectItem* itemTest = (VisionRectItem*)m_lstItem[i];
            if(itemTest->getPosInArea(x,y)){
                qDebug()<<"in of range";
                lstClickedItem.push_back(m_lstItem[i]);
            }else{
                qDebug()<<"out of range";
            }

        }
    }

    if(lstClickedItem.count() == 1){
        lstClickedItem[0]->setZValue(5);
        m_curVisionItem = lstClickedItem[0];
        lstClickedItem[0]->setSelected(true);
        lstClickedItem[0]->scene()->update();
        return;
    }

    for(int j=0;j<lstClickedItem.count();j++){
        if(lstClickedItem[j]->isSelected()){
            if(j == lstClickedItem.count()-1){
                lstClickedItem[0]->setZValue(5);
                m_curVisionItem = lstClickedItem[lstClickedItem.count()-1];  //此处逻辑有点小问题，z=5的不是当前选中的，是下一次即将被选中的
                lstClickedItem[0]->setSelected(true);
                lstClickedItem[0]->scene()->update();
            }else{
                lstClickedItem[j+1]->setZValue(5);
                m_curVisionItem = lstClickedItem[j];
                lstClickedItem[j+1]->setSelected(true);
                lstClickedItem[j+1]->scene()->update();
            }
            lstClickedItem[j]->setZValue(0);
            lstClickedItem[j]->setSelected(false);
            break;
        }
    }

    //    qDebug()<<rectItem1->zValue()<<ellipseItem1->zValue()<<ellipseItem2->zValue();
}

void VisionGraph_Item::slot_wheel(qreal delta)
{
    if(delta > 0){
        //放大
        if(m_zoom >= 5){
            m_zoom  = 5;
        }else{
            m_zoom = m_zoom + 0.1;
        }
    }else{
        if(m_zoom <= 0.25){
            m_zoom  = 0.25;
        }else{
            m_zoom = m_zoom - 0.1;
        }
    }
    comboBox->setCurrentText(QString::number(m_zoom*100)+"%");
}

void VisionGraph_Item::slot_SizeChanged(QString currentSize)
{
    qDebug()<<" view scale size is changed : "<<currentSize;
    QString str = currentSize.mid(0,currentSize.indexOf("%"));
    if(!currentSize.contains("%") && currentSize != ""){
        comboBox->setEditText(currentSize+"%");
        return;
    }
    bool ok;
    float scale = str.toFloat(&ok);
    if(ok){
        view->zoom(scale/100);
    }
}

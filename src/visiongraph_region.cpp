#include "visiongraph_region.h"

#include <QSpinBox>
#include <QSlider>
#include <QLineEdit>
#include <QDebug>
#include <QMatrix>
#include <QFileDialog>

VisionGraph_Region::VisionGraph_Region(ToolButtonDirection toolButtonDirect,QWidget *parent) : QFrame(parent)
{
//    setMinimumSize(1200,800);
    mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);

    m_toolButtonDirection = toolButtonDirect;
    initScene();
    initLayout(toolButtonDirect);

}

void VisionGraph_Region::setSceneWidgetSize(QSize size)
{
    sceneWidget->resize(size);
}

void VisionGraph_Region::setSceneWidgetSize(qreal w, qreal h)
{
    sceneWidget->resize(w,h);
}


void VisionGraph_Region::initScene()
{

    sceneWidget = new VisionGraphWidget(this);
    sceneWidget->setMinimumSize(400,300);
    connect(sceneWidget,SIGNAL(signal_sizeChanged(qreal,qreal)),this,SLOT(slot_SizeChanged(qreal,qreal)));

    view = new VisionGraphView(sceneWidget);
    QObject::connect(view,SIGNAL(signal_Item(ItemType,QRectF)),this,SLOT(slot_addItem(ItemType,QRectF)));
    QObject::connect(view,SIGNAL(signal_Item_poly(QVector<QPointF>)),this,SLOT(slot_addPoly(QVector<QPointF>)));
    QObject::connect(view,SIGNAL(signal_Move(QPointF)),this,SLOT(slot_mouseMove(QPointF)));
    QObject::connect(view,SIGNAL(signal_wheel(qreal)),this,SLOT(slot_wheel(qreal)));
    scene = new VisionGraphScene(sceneWidget);
    connect(scene,SIGNAL(signal_MouseMove(qreal,qreal)),this,SLOT(slot_SceneMouseMove(qreal,qreal)));

    scene->setSceneRect(0,0,sceneWidget->width(),sceneWidget->height());
    view->setScene(scene);
    view->setSceneRect(0,0,sceneWidget->width(),sceneWidget->height());

    m_bkPixmapItem = new QGraphicsPixmapItem();
    m_bkPixmapItem->setPixmap(QPixmap(":/bgk.bmp"));
    scene->addItem(m_bkPixmapItem);

    m_mousePixmap = new QGraphicsPixmapItem();
    m_mousePixmap->setPos(scene->width()/2-10,scene->height()/2-10);
    m_mousePixmap->setPixmap(QPixmap(iconPath+"cursor-size_Circle.png").scaled(10*2,10*2));
    scene->addItem(m_mousePixmap);


    //显示坐标和操作信息

}

void VisionGraph_Region::initTool_painter()
{

}

void VisionGraph_Region::initTool_operation()
{
    sys_open_action = new QAction(QIcon(iconPath+"open.png"),QStringLiteral("打开"));
    sys_open_action->setIconText(QStringLiteral("打开"));
    connect(sys_open_action,SIGNAL(triggered(bool)),this,SLOT(slot_open_action()));

    sys_save_action = new QAction(QIcon(iconPath+"save.png"),QStringLiteral("保存"));
    sys_save_action->setIconText(QStringLiteral("保存"));
    connect(sys_save_action,SIGNAL(triggered(bool)),this,SLOT(slot_save_action()));
    //撤销按钮（回滚）历史
    sys_front_action = new QAction(QIcon(iconPath+"back.png"),QStringLiteral("撤销"));
    sys_front_action->setIconText(QStringLiteral("撤销"));
    connect(sys_front_action,SIGNAL(triggered(bool)),this,SLOT(slot_front_action()));
    //撤销按钮（后滚）未来
    sys_next_action = new QAction(QIcon(iconPath+"front.png"),QStringLiteral("恢复"));
    sys_next_action->setIconText(QStringLiteral("恢复"));
    connect(sys_next_action,SIGNAL(triggered(bool)),this,SLOT(slot_next_action()));
    //清空绘图区域
    sys_clear_action = new QAction(QIcon(iconPath+"delect.png"),QStringLiteral("清理"));
    sys_clear_action->setIconText(QStringLiteral("清理"));
    connect(sys_clear_action,SIGNAL(triggered(bool)),this,SLOT(slot_clear_action()));

    //调整鼠标的大小--针对鼠标擦除和鼠标绘制
    tool_Widget = new QToolBar;
    tool_Widget->setMinimumHeight(20);
    tool_Widget->setMovable(false);

    tool_Widget->addAction(sys_open_action);
    tool_Widget->addAction(sys_save_action);
    tool_Widget->addAction(sys_front_action);
    tool_Widget->addAction(sys_next_action);
    tool_Widget->addAction(sys_clear_action);
    tool_Widget->addSeparator();





    //选中按钮---绘制规则形状的时候，绘制完成后默认选中，此时高亮，其他时间都是灰色
    sys_selected_action = new QAction(QIcon(iconPath+"select.png"),QStringLiteral(""));
    sys_selected_action->setIconText(QStringLiteral("选择"));
    connect(sys_selected_action,SIGNAL(triggered(bool)),this,SLOT(slot_selected_action()));
    //拖动按钮---拖动整个绘制的区域的位置---目前暂时不提供（后期加）
    sys_drag_action = new QAction(QIcon(iconPath+"drag.png"),QStringLiteral("拖动当前视图"));
    sys_drag_action->setIconText(QStringLiteral("拖动"));
    connect(sys_drag_action,SIGNAL(triggered(bool)),this,SLOT(slot_drag_action()));
    //放大镜功能
    sys_zoom_action = new QAction(QIcon(iconPath+"zoom.png"),QStringLiteral("缩放"));
    sys_zoom_action->setIconText(QStringLiteral("缩放"));
    connect(sys_zoom_action,SIGNAL(triggered(bool)),this,SLOT(slot_zoom_action()));


    //鼠标擦除
    sys_mouseClear_action = new QAction(QIcon(iconPath+"clear.png"),QStringLiteral("擦除"));
    sys_mouseClear_action->setIconText(QStringLiteral("擦除"));
    sys_mouseClear_action->setText("mouseClear");
    connect(sys_mouseClear_action,SIGNAL(triggered(bool)),this,SLOT(slot_mouseClear_action()));
    //鼠标绘制
    sys_mousePainter_action = new QAction(QIcon(iconPath+"painter.png"),QStringLiteral("绘制"));
    sys_mousePainter_action->setIconText(QStringLiteral("绘制"));
    sys_mousePainter_action->setText("mousePainter");
    connect(sys_mousePainter_action,SIGNAL(triggered(bool)),this,SLOT(slot_mousePainter_action()));


    //矩形
    sys_rect_action = new QAction(QIcon(iconPath+"rect.png"),QStringLiteral("新建一个矩形区域"));
    sys_rect_action->setIconText(QStringLiteral("矩形"));
    sys_rect_action->setText("rectangle");
    connect(sys_rect_action,SIGNAL(triggered(bool)),this,SLOT(slot_rect_action()));
    //椭圆
    sys_ellipse_action = new QAction(QIcon(iconPath+"ellipse.png"),QStringLiteral("新建一个椭圆区域"));
    sys_ellipse_action->setIconText(QStringLiteral("椭圆或者圆"));
    sys_ellipse_action->setText("ellipse");
    connect(sys_ellipse_action,SIGNAL(triggered(bool)),this,SLOT(slot_ellipse_action()));
    //不规则多边形---直线连接各点
    sys_poly_action = new QAction(QIcon(iconPath+"poly.png"),QStringLiteral("新建一个不规则多边形区域"));
    sys_poly_action->setIconText(QStringLiteral("多边形"));
    sys_poly_action->setText("poly");
    connect(sys_poly_action,SIGNAL(triggered(bool)),this,SLOT(slot_poly_action()));
    //不规则圆形---曲线连接各点
    sys_poly_elli_action = new QAction(QIcon(iconPath+"poly_elli.png"),QStringLiteral("任意区域：绘制不规则区域"));
    sys_poly_elli_action->setIconText(QStringLiteral("任意区域"));
    sys_poly_elli_action->setText("region");
    connect(sys_poly_elli_action,SIGNAL(triggered(bool)),this,SLOT(slot_poly_elli_action()));


    //调整鼠标的大小--针对鼠标擦除和鼠标绘制

//    tool_painter->setStyleSheet(QString::fromUtf8("border:1px solid red"));
    tool_Widget->addAction(sys_selected_action);
    tool_Widget->addAction(sys_drag_action);
    tool_Widget->addAction(sys_zoom_action);
    tool_Widget->addSeparator();

    tool_Widget->addAction(sys_mouseClear_action);
    tool_Widget->addAction(sys_mousePainter_action);
    tool_Widget->addSeparator();

    tool_Widget->addAction(sys_rect_action);
    tool_Widget->addAction(sys_ellipse_action);
    tool_Widget->addAction(sys_poly_action);
    tool_Widget->addAction(sys_poly_elli_action);
    tool_Widget->addSeparator();

    connect(tool_Widget,SIGNAL(actionTriggered(QAction*)),this,SLOT(slot_actionTriggered(QAction*)));








    QLabel *label = new QLabel;
    label->setText(QStringLiteral("大小"));
    label->setAlignment(Qt::AlignCenter);
    label->setMinimumHeight(20);
    label->show();

    QLabel *label_slider = new QLabel;

    QSlider *pSlider = new QSlider(label_slider);
    if(m_toolButtonDirection == ToolButtonDirection::leftDirection ||
            m_toolButtonDirection == ToolButtonDirection::rightDirection){
        label_slider->setFixedSize(40,120);
        pSlider->setOrientation(Qt::Vertical);  // 竖直方向
        pSlider->setFixedHeight(100);
        pSlider->setMinimumWidth(20);
        QHBoxLayout *layout = new QHBoxLayout(label_slider);
        layout->addWidget(pSlider);
        layout->addStretch();
    }else{
        label_slider->setFixedSize(120,40);

        QVBoxLayout *layout = new QVBoxLayout(label_slider);

        pSlider->setOrientation(Qt::Horizontal);
        pSlider->setFixedWidth(100);
        pSlider->setMinimumHeight(20);
        layout->addWidget(pSlider);
        layout->addStretch();
    }

    pSlider->setMinimum(1);  // 最小值
    pSlider->setMaximum(300);  // 最大值
    pSlider->setSingleStep(1);  // 步长

    // 微调框
    QSpinBox *pSpinBox = new QSpinBox;
    pSpinBox->setMinimum(1);  // 最小值
    pSpinBox->setMaximum(300);  // 最大值
    pSpinBox->setSingleStep(1);  // 步长

    // 连接信号槽（相互改变）
    connect(pSpinBox, SIGNAL(valueChanged(int)), pSlider, SLOT(setValue(int)));
    connect(pSlider, SIGNAL(valueChanged(int)), pSpinBox, SLOT(setValue(int)));
    connect(pSlider,SIGNAL(valueChanged(int)),this,SLOT(slot_valueChanged(int)));

    tool_Widget->addWidget(label);
    tool_Widget->addWidget(label_slider);
    tool_Widget->addWidget(pSpinBox);
    tool_Widget->addSeparator();





    //显示区域的信息，view的大小，缩放比例，鼠标的信息
    QWidget *infoWidget = new QWidget();

    QLabel *label_w = new QLabel;
    label_w->setText(QStringLiteral("宽度:"));
    label_w->show();

    QLineEdit *lineEdit_w = new QLineEdit;
    lineEdit_w->setText(QString::number(view->width()));
    lineEdit_w->setFixedWidth(35);
    lineEdit_w->show();

    QLabel *label_h = new QLabel;
    label_h->setText(QStringLiteral("高度:"));
    label_h->show();

    QLineEdit *lineEdit_h = new QLineEdit;
    lineEdit_h->setText(QString::number(view->height()));
    lineEdit_h->setFixedWidth(35);
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

    if(m_toolButtonDirection == ToolButtonDirection::leftDirection ||
            m_toolButtonDirection == ToolButtonDirection::rightDirection){
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


    tool_Widget->addWidget(infoWidget);
    tool_Widget->addSeparator();
}

void VisionGraph_Region::initLayout(ToolButtonDirection toolButtonDirect)
{
    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    QVBoxLayout *vBoxLayout = new QVBoxLayout;

    m_toolButtonDirection = toolButtonDirect;
    initTool_operation();
    initTool_painter();


    if(m_toolButtonDirection == ToolButtonDirection::leftDirection){
        tool_Widget->setOrientation(Qt::Vertical);

        hBoxLayout->addWidget(tool_Widget);
        hBoxLayout->addWidget(sceneWidget);

        vBoxLayout->addLayout(hBoxLayout);
    }else if(m_toolButtonDirection == ToolButtonDirection::topDirection){
        tool_Widget->setOrientation(Qt::Horizontal);

        vBoxLayout->addWidget(tool_Widget);
        vBoxLayout->addWidget(sceneWidget);

    }else if(m_toolButtonDirection == ToolButtonDirection::rightDirection){
        tool_Widget->setOrientation(Qt::Vertical);

        hBoxLayout->addWidget(sceneWidget);
        hBoxLayout->addWidget(tool_Widget);

        vBoxLayout->addLayout(hBoxLayout);
    }else if(m_toolButtonDirection == ToolButtonDirection::bottomDirection){
        tool_Widget->setOrientation(Qt::Horizontal);

        vBoxLayout->addWidget(sceneWidget);
        vBoxLayout->addWidget(tool_Widget);
    }

    mainLayout->addLayout(vBoxLayout);
}

void VisionGraph_Region::addRect(QRectF rf, bool bEdit)
{
    if(bEdit){
        VisionRectItem* item = new VisionRectItem(true);
        QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
        QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)),view,SLOT(slot_updatePath(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)));
        QObject::connect(item,&QObject::destroyed,[=](){
            m_curVisionItem = nullptr;
        });
        item->setRect(rf);
        scene->addItem(item);
        m_curVisionItem = item;
    }
}

void VisionGraph_Region::addEllipse(QRectF rf)
{
    VisionEllipseItem *item = new VisionEllipseItem(true);
    QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
    QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)),view,SLOT(slot_updatePath(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)));
    QObject::connect(item,&QObject::destroyed,[=](){
        m_curVisionItem = nullptr;
    });
    item->setRect(rf);
    scene->addItem(item);
    m_curVisionItem = item;
}

void VisionGraph_Region::addLine(QLine line)
{
    //todo
    VisionLineItem *item = new VisionLineItem();
    QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
    QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)),view,SLOT(slot_updatePath(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)));
    QObject::connect(item,&QObject::destroyed,[=](){
        m_curVisionItem = nullptr;
    });
    item->setLine(line.p1(),line.p2());
    scene->addItem(item);
    m_curVisionItem = item;
}

void VisionGraph_Region::addLines(QList<QLine> lstLine)
{

}

void VisionGraph_Region::addPolygon(QVector<QPointF> vecPointF)
{
    VisionPolygon *item = new VisionPolygon();
    QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
    QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QVector<QPointF>)),view,SLOT(slot_CreatePolygonF(bool,VisionItem*,ItemType,QVector<QPointF>)));
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
}

void VisionGraph_Region::addPoint(QPointF pointF)
{
    // todo
    VisionCrossPointItem *item = new VisionCrossPointItem();
    QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
    QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QVector<QPointF>)),view,SLOT(slot_CreatePolygonF(bool,VisionItem*,ItemType,QVector<QPointF>)));
    QObject::connect(item,&QObject::destroyed,[=](){
        m_curVisionItem = nullptr;
    });
    item->setPoint(pointF);
    scene->addItem(item);
    m_curVisionItem = item;
}


int VisionGraph_Region::setBkImg(QImage image)
{
    if (image.isNull())
        return -1;
    if (m_bkPixmapItem == NULL)
    {
        m_bkPixmapItem = new QGraphicsPixmapItem();
        scene->addItem(m_bkPixmapItem);
    }
    m_bkPixmapItem->setPixmap(QPixmap::fromImage(image));

    //根据Scene中的元件来确定Scene的大小  背景图片作为scene的大小，当设置背景图片的时候，scene的大小跟随变化
//    if (image.width() > viewWidth)
//        viewWidth = image.width();
//    if (image.height() > viewHeight)
//        viewHeight = image.height();
//    this->setSceneRect(viewX,viewY,viewWidth,viewHeight);

    return 0;
}

void VisionGraph_Region::slot_selected_action()
{

}

void VisionGraph_Region::slot_drag_action()
{
    view->setItemType(ItemType::Drag);
    m_itemType = ItemType::Drag;
//    label_Operation->setText(QStringLiteral("通过鼠标的拖动，拖动视图区域"));
}

void VisionGraph_Region::slot_zoom_action()
{
    view->setItemType(ItemType::Zoom);
    m_itemType = ItemType::Zoom;
//    label_Operation->setText(QStringLiteral("通过鼠标的滚轮，缩放视图区域"));
//    this->
}

void VisionGraph_Region::slot_mousePainter_action()
{
    view->setItemType(ItemType::Point);
    m_itemType = ItemType::Point;
//    label_Operation->setText(QStringLiteral("点击绘制任意图形"));

}

void VisionGraph_Region::slot_mouseClear_action()
{
    view->setItemType(ItemType::NoPoint);
    m_itemType = ItemType::NoPoint;
//    label_Operation->setText(QStringLiteral("点击绘制任意图形"));


}

void VisionGraph_Region::slot_rect_action()
{
    view->setItemType(ItemType::Rect);
    m_itemType = ItemType::Rect;
//    label_Operation->setText(QStringLiteral("拖动到开始创建一个新区域 Rectangle"));
}

void VisionGraph_Region::slot_ellipse_action()
{
    view->setItemType(ItemType::EllipseItem);
    m_itemType = ItemType::EllipseItem;
//    label_Operation->setText(QStringLiteral("拖动到开始创建一个新区域 Ellipse"));

}

void VisionGraph_Region::slot_poly_action()
{
    view->setItemType(ItemType::Poly);
    m_itemType = ItemType::Poly;
//    label_Operation->setText(QStringLiteral("拖动到开始创建一个新区域 path"));

}

void VisionGraph_Region::slot_poly_elli_action()
{
    view->setItemType(ItemType::Region);
    m_itemType = ItemType::Region;
//    label_Operation->setText(QStringLiteral("点击，创建任意的多边形"));
}

void VisionGraph_Region::slot_open_action()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                      "/",
                                                      tr("Images (*.png *.bmp *.jpg)"));

    qDebug()<<fileName;
    if(fileName != ""){
        m_bkPixmapItem->setPixmap(QPixmap(fileName).scaled(800,600));
    }
}

void VisionGraph_Region::slot_save_action()
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
}

void VisionGraph_Region::slot_front_action()
{
    view->back_region();
}

void VisionGraph_Region::slot_next_action()
{
    view->front_region();
}

void VisionGraph_Region::slot_clear_action()
{
//    scene->clear();
    view->clearPainter();
    //清除当前的item
    if(m_curVisionItem != nullptr){
        m_curVisionItem->hide();
        m_curVisionItem->deleteLater();
        m_curVisionItem = nullptr;
    }
}

void VisionGraph_Region::slot_addItem(ItemType type, QRectF rf)
{
    if(type == Rect){
        addRect(rf);
    }else if(type == EllipseItem){
        addEllipse(rf);
    }
}

void VisionGraph_Region::slot_addPoly(QVector<QPointF> vecPointF)
{
    addPolygon(vecPointF);
}

void VisionGraph_Region::slot_mouseMove(QPointF pointF)
{
//    m_mousePixmap->hide();
//    label_mousePos->setText(QString::number(pointF.x())+" : "+QString::number(pointF.y()));
}

void VisionGraph_Region::slot_wheel(qreal delta)
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

void VisionGraph_Region::slot_valueChanged(int qR)
{
    m_mousePixmap->show();
    m_mousePixmap->setPixmap(QPixmap(iconPath+"cursor-size_Circle.png").scaled(qR,qR));
    m_mousePixmap->setPos(view->width()/2-m_mousePixmap->boundingRect().width()/2,view->height()/2-m_mousePixmap->boundingRect().height()/2);
    view->setPainterCursorR((qreal)qR/2);
}

void VisionGraph_Region::slot_SizeChanged(QString currentSize)
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

void VisionGraph_Region::slot_SizeChanged(qreal w, qreal h)
{
    qDebug()<<"sceneWidget size is changed";

    view->resize(sceneWidget->width()+2,sceneWidget->height()+2);
    scene->setSceneRect(0,0,sceneWidget->width(),sceneWidget->height());
    view->setScene(scene);
    view->setSceneRect(0,0,sceneWidget->width(),sceneWidget->height());
    view->slotUpdateViewInfo_Pos();
}

void VisionGraph_Region::slot_SceneMouseMove(qreal x, qreal y)
{
//    qDebug()<<x<<y;
    m_mousePixmap->hide();
//    label_mousePos->setText("scene pos : "+QString::number(x)+" : "+QString::number(y));
}

void VisionGraph_Region::slot_actionTriggered(QAction *action)
{
//    this->hide();
//    this->show();
//    for(int i=0;)ellp
    if(action->text() == "rectangle" || action->text() == "ellipse" || action->text() == "poly" ||
            action->text() == "region" || action->text() == "mousePainter" || action->text() == "mouseClear"){
        if(m_curVisionItem != nullptr){
            m_curVisionItem->setEdit(false);
            m_curVisionItem->setSelected(false);
            m_curVisionItem->scene()->update();
        }
    }
}


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

    scene->setSceneRect(0,0,800,600);
    view->setScene(scene);
//    view->setSceneRect(0,0,800,600);

    m_bkPixmapItem = new QGraphicsPixmapItem();
    m_bkPixmapItem->setPixmap(QPixmap(":/bgk.bmp"));
    scene->addItem(m_bkPixmapItem);

    m_mousePixmap = new QGraphicsPixmapItem();
    m_mousePixmap->setPos(scene->width()/2-10,scene->height()/2-10);
    m_mousePixmap->setPixmap(QPixmap(iconPath+"cursor-size_Circle.png").scaled(10*2,10*2,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    m_mousePixmap->hide();
    scene->addItem(m_mousePixmap);

    //显示坐标和操作信息
//    scene->setGrid_Visible(true);
//    scene->setGrid_Size(QSize(50,50));
}

void VisionGraph_Region::initTool_operation()
{
    QAction* sys_open_action = new QAction(QIcon(iconPath+"open.png"),QStringLiteral("打开"));
    sys_open_action->setIconText(QStringLiteral("打开"));
    connect(sys_open_action,SIGNAL(triggered(bool)),this,SLOT(slot_open_action()));
    sys_open_button = new QToolButton;
    sys_open_button->setDefaultAction(sys_open_action);

    QAction* sys_save_action = new QAction(QIcon(iconPath+"save.png"),QStringLiteral("保存"));
    sys_save_action->setIconText(QStringLiteral("保存"));
    connect(sys_save_action,SIGNAL(triggered(bool)),this,SLOT(slot_save_action()));
    sys_save_button = new QToolButton;
    sys_save_button->setDefaultAction(sys_save_action);
    //撤销按钮（回滚）历史
    QAction* sys_front_action = new QAction(QIcon(iconPath+"back.png"),QStringLiteral("撤销"));
    sys_front_action->setIconText(QStringLiteral("撤销"));
    connect(sys_front_action,SIGNAL(triggered(bool)),this,SLOT(slot_front_action()));
    sys_front_button = new QToolButton;
    sys_front_button->setDefaultAction(sys_front_action);
    //撤销按钮（后滚）未来
    QAction* sys_next_action = new QAction(QIcon(iconPath+"front.png"),QStringLiteral("恢复"));
    sys_next_action->setIconText(QStringLiteral("恢复"));
    connect(sys_next_action,SIGNAL(triggered(bool)),this,SLOT(slot_next_action()));
    sys_next_button = new QToolButton;
    sys_next_button->setDefaultAction(sys_next_action);
    //清空绘图区域
    QAction* sys_clear_action = new QAction(QIcon(iconPath+"delect.png"),QStringLiteral("清理"));
    sys_clear_action->setIconText(QStringLiteral("清理"));
    connect(sys_clear_action,SIGNAL(triggered(bool)),this,SLOT(slot_clear_action()));
    sys_clear_button = new QToolButton;
    sys_clear_button->setDefaultAction(sys_clear_action);

    //调整鼠标的大小--针对鼠标擦除和鼠标绘制
    tool_Widget = new QToolBar;
    tool_Widget->setMinimumHeight(20);
    tool_Widget->setMovable(false);

    m_lstAction.append(tool_Widget->addWidget(sys_open_button));
    m_lstAction.append(tool_Widget->addWidget(sys_save_button));
    m_lstAction.append(tool_Widget->addWidget(sys_front_button));
    m_lstAction.append(tool_Widget->addWidget(sys_next_button));
    m_lstAction.append(tool_Widget->addWidget(sys_clear_button));
    tool_Widget->addSeparator();
    m_lstToolBtn.append(sys_open_button);
    m_lstToolBtn.append(sys_save_button);
    m_lstToolBtn.append(sys_front_button);
    m_lstToolBtn.append(sys_next_button);
    m_lstToolBtn.append(sys_clear_button);




    //选中按钮---绘制规则形状的时候，绘制完成后默认选中，此时高亮，其他时间都是灰色
    QAction* sys_selected_action = new QAction(QIcon(iconPath+"select.png"),QStringLiteral(""));
    sys_selected_action->setIconText(QStringLiteral("选择"));
    connect(sys_selected_action,SIGNAL(triggered(bool)),this,SLOT(slot_selected_action()));
    sys_selected_button = new QToolButton;
    sys_selected_button->setDefaultAction(sys_selected_action);
    //拖动按钮---拖动整个绘制的区域的位置---目前暂时不提供（后期加）
    QAction* sys_drag_action = new QAction(QIcon(iconPath+"drag.png"),QStringLiteral("拖动当前视图"));
    sys_drag_action->setIconText(QStringLiteral("拖动"));
    connect(sys_drag_action,SIGNAL(triggered(bool)),this,SLOT(slot_drag_action()));
    sys_drag_button = new QToolButton;
    sys_drag_button->setDefaultAction(sys_drag_action);
    //放大镜功能
    QAction* sys_zoom_action = new QAction(QIcon(iconPath+"zoom.png"),QStringLiteral("缩放"));
    sys_zoom_action->setIconText(QStringLiteral("缩放"));
    connect(sys_zoom_action,SIGNAL(triggered(bool)),this,SLOT(slot_zoom_action()));
    sys_zoom_button = new QToolButton;
    sys_zoom_button->setDefaultAction(sys_zoom_action);


    //鼠标擦除
    QAction* sys_mouseClear_action = new QAction(QIcon(iconPath+"clear.png"),QStringLiteral("擦除"));
    sys_mouseClear_action->setIconText(QStringLiteral("擦除"));
    sys_mouseClear_action->setText("mouseClear");
    connect(sys_mouseClear_action,SIGNAL(triggered(bool)),this,SLOT(slot_mouseClear_action()));
    sys_mouseClear_button = new QToolButton;
    sys_mouseClear_button->setDefaultAction(sys_mouseClear_action);
    //鼠标绘制
    QAction* sys_mousePainter_action = new QAction(QIcon(iconPath+"painter.png"),QStringLiteral("绘制"));
    sys_mousePainter_action->setIconText(QStringLiteral("绘制"));
    sys_mousePainter_action->setText("mousePainter");
    connect(sys_mousePainter_action,SIGNAL(triggered(bool)),this,SLOT(slot_mousePainter_action()));
    sys_mousePainter_button = new QToolButton;
    sys_mousePainter_button->setDefaultAction(sys_mousePainter_action);


    //矩形
    QAction* sys_rect_action = new QAction(QIcon(iconPath+"rect.png"),QStringLiteral("新建一个矩形区域"));
    sys_rect_action->setIconText(QStringLiteral("矩形"));
    sys_rect_action->setText("rectangle");
    connect(sys_rect_action,SIGNAL(triggered(bool)),this,SLOT(slot_rect_action()));
    sys_rect_button = new QToolButton;
    sys_rect_button->setDefaultAction(sys_rect_action);

    //椭圆
    QAction* sys_ellipse_action = new QAction(QIcon(iconPath+"ellipse.png"),QStringLiteral("新建一个椭圆区域"));
    sys_ellipse_action->setIconText(QStringLiteral("椭圆或者圆"));
    sys_ellipse_action->setText("ellipse");
    connect(sys_ellipse_action,SIGNAL(triggered(bool)),this,SLOT(slot_ellipse_action()));
    sys_ellipse_button = new QToolButton;
    sys_ellipse_button->setDefaultAction(sys_ellipse_action);
    //不规则多边形---直线连接各点
    QAction* sys_poly_action = new QAction(QIcon(iconPath+"poly.png"),QStringLiteral("新建一个不规则多边形区域"));
    sys_poly_action->setIconText(QStringLiteral("多边形"));
    sys_poly_action->setText("poly");
    connect(sys_poly_action,SIGNAL(triggered(bool)),this,SLOT(slot_poly_action()));
    sys_poly_button = new QToolButton;
    sys_poly_button->setDefaultAction(sys_poly_action);
    //不规则圆形---曲线连接各点
    QAction* sys_poly_elli_action = new QAction(QIcon(iconPath+"poly_elli.png"),QStringLiteral("任意区域：绘制不规则区域"));
    sys_poly_elli_action->setIconText(QStringLiteral("任意区域"));
    sys_poly_elli_action->setText("region");
    connect(sys_poly_elli_action,SIGNAL(triggered(bool)),this,SLOT(slot_poly_elli_action()));
    sys_poly_elli_button = new QToolButton;
    sys_poly_elli_button->setDefaultAction(sys_poly_elli_action);

    //调整鼠标的大小--针对鼠标擦除和鼠标绘制

    m_lstAction.append(tool_Widget->addWidget(sys_selected_button));
    m_lstAction.append(tool_Widget->addWidget(sys_drag_button));
    m_lstAction.append(tool_Widget->addWidget(sys_zoom_button));
    tool_Widget->addSeparator();

    m_lstAction.append(tool_Widget->addWidget(sys_mouseClear_button));
    m_lstAction.append(tool_Widget->addWidget(sys_mousePainter_button));
    tool_Widget->addSeparator();

    m_lstAction.append(tool_Widget->addWidget(sys_rect_button));
    m_lstAction.append(tool_Widget->addWidget(sys_ellipse_button));
    m_lstAction.append(tool_Widget->addWidget(sys_poly_button));
    m_lstAction.append(tool_Widget->addWidget(sys_poly_elli_button));
    m_insertAction = tool_Widget->addSeparator();

    connect(tool_Widget,SIGNAL(actionTriggered(QAction*)),this,SLOT(slot_actionTriggered(QAction*)));

    m_lstToolBtn.append(sys_selected_button);
    m_lstToolBtn.append(sys_drag_button);
    m_lstToolBtn.append(sys_zoom_button);
    m_lstToolBtn.append(sys_mouseClear_button);
    m_lstToolBtn.append(sys_mousePainter_button);
    m_lstToolBtn.append(sys_rect_button);
    m_lstToolBtn.append(sys_ellipse_button);
    m_lstToolBtn.append(sys_poly_button);
    m_lstToolBtn.append(sys_poly_elli_button);






    QLabel *label = new QLabel;
    label->setText(QStringLiteral("大小"));
    label->setAlignment(Qt::AlignCenter);
//    label->set
//    label->setMinimumHeight(20);

    label_slider = new QLabel;


    pSlider = new QSlider(label_slider);
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

    pSlider->setValue(10);  //默认值
    tool_Widget->addWidget(label);
    tool_Widget->addWidget(label_slider);
    tool_Widget->addWidget(pSpinBox);
    tool_Widget->addSeparator();





    //显示区域的信息，view的大小，缩放比例，鼠标的信息
    infoWidget_Action = new QAction;
    infoWidget = new QWidget();

    label_w = new QLabel;
    label_w->setText(QStringLiteral("宽度:"));

    // 微调框
    pSpinBox_w = new QSpinBox;
    pSpinBox_w->setMinimum(1);  // 最小值
    pSpinBox_w->setMaximum(5000);  // 最大值
    pSpinBox_w->setSingleStep(5);  // 步长
    pSpinBox_w->setValue(800);
    pSpinBox_w->setStyleSheet("QSpinBox::up-button{width:0;height:0;}"
        "QSpinBox::down-button{width:0;height:0;}");
    connect(pSpinBox_w,SIGNAL(valueChanged(int)),this,SLOT(slot_SpinBox_ViewRegionSize(int)));

    label_h = new QLabel;
    label_h->setText(QStringLiteral("高度:"));

    // 微调框
    pSpinBox_h = new QSpinBox;
    pSpinBox_h->setMinimum(1);  // 最小值
    pSpinBox_h->setMaximum(5000);  // 最大值
    pSpinBox_h->setSingleStep(5);  // 步长
    pSpinBox_h->setValue(600);
    pSpinBox_h->setStyleSheet("QSpinBox::up-button{width:0;height:0;}"
        "QSpinBox::down-button{width:0;height:0;}");
    connect(pSpinBox_h,SIGNAL(valueChanged(int)),this,SLOT(slot_SpinBox_ViewRegionSize(int)));


    label_size = new QLabel;
    label_size->setText(QStringLiteral("尺寸:"));

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
        vBoxLayout->addWidget(pSpinBox_w);
        vBoxLayout->addWidget(label_h);
        vBoxLayout->addWidget(pSpinBox_h);

        vBoxLayout->setSpacing(10);
        vBoxLayout->addWidget(label_size);
        vBoxLayout->addWidget(comboBox);

        tool_Widget->setMinimumWidth(45);
    }else{
        QHBoxLayout* hBoxLayout = new QHBoxLayout;
        infoWidget->setLayout(hBoxLayout);

        hBoxLayout->addWidget(label_w);
        hBoxLayout->addWidget(pSpinBox_w);
        hBoxLayout->addWidget(label_h);
        hBoxLayout->addWidget(pSpinBox_h);

        hBoxLayout->setSpacing(10);
        hBoxLayout->addWidget(label_size);
        hBoxLayout->addWidget(comboBox);

        tool_Widget->setMinimumHeight(45);
    }
    infoWidget->show();

    QToolBar* tool_infoWidget = new QToolBar;
    tool_infoWidget->addWidget(infoWidget);
    tool_infoWidget->addSeparator();

    if(m_toolButtonDirection == ToolButtonDirection::leftDirection ||
            m_toolButtonDirection == ToolButtonDirection::rightDirection){
        tool_infoWidget->setOrientation(Qt::Vertical);
    }else{
        tool_infoWidget->setOrientation(Qt::Horizontal);
    }

    infoWidget_Action = tool_Widget->addWidget(tool_infoWidget);

    qDebug()<<tool_Widget->width()<<tool_Widget->height();

    for(int i=0;i<m_lstToolBtn.count();i++){
        m_lstToolBtn[i]->setToolButtonStyle(m_ToolStyle);
        m_lstToolBtn[i]->setIconSize(m_ToolIconSize);
        m_lstToolBtn[i]->setFixedSize(m_ToolBtnSize);
    }
}

void VisionGraph_Region::initLayout(ToolButtonDirection toolButtonDirect)
{
    m_hBoxLayout = new QHBoxLayout;
    m_vBoxLayout = new QVBoxLayout;

    m_toolButtonDirection = toolButtonDirect;
    initTool_operation();

    if(m_toolButtonDirection == ToolButtonDirection::leftDirection){
        tool_Widget->setOrientation(Qt::Vertical);

        m_hBoxLayout->addWidget(tool_Widget);
        m_hBoxLayout->addWidget(sceneWidget);

        m_vBoxLayout->addLayout(m_hBoxLayout);
    }else if(m_toolButtonDirection == ToolButtonDirection::topDirection){
        tool_Widget->setOrientation(Qt::Horizontal);

        m_vBoxLayout->addWidget(tool_Widget);
        m_vBoxLayout->addWidget(sceneWidget);

    }else if(m_toolButtonDirection == ToolButtonDirection::rightDirection){
        tool_Widget->setOrientation(Qt::Vertical);

        m_hBoxLayout->addWidget(sceneWidget);
        m_hBoxLayout->addWidget(tool_Widget);

        m_vBoxLayout->addLayout(m_hBoxLayout);
    }else if(m_toolButtonDirection == ToolButtonDirection::bottomDirection){
        tool_Widget->setOrientation(Qt::Horizontal);

        m_vBoxLayout->addWidget(sceneWidget);
        m_vBoxLayout->addWidget(tool_Widget);
    }

    mainLayout->addLayout(m_vBoxLayout);
}

VisionRectItem *VisionGraph_Region::addRect(QRectF rf, bool bEdit)
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
        return item;
    }
    return NULL;
}

QGraphicsRectItem *VisionGraph_Region::_addRect(const QRectF &rect, const QPen &pen, const QBrush &brush)
{
    return scene->addRect(rect,pen,brush);
}

QGraphicsPolygonItem *VisionGraph_Region::_addPolygon(const QPolygonF &polygon, const QPen &pen, const QBrush &brush)
{
    return scene->addPolygon(polygon,pen,brush);
}

QGraphicsLineItem *VisionGraph_Region::_addLine(const QLineF &line, const QPen &pen)
{
    return scene->addLine(line,pen);
}

QGraphicsEllipseItem *VisionGraph_Region::_addEllipse(const QRectF &rect, const QPen &pen, const QBrush &brush)
{
    return scene->addEllipse(rect,pen,brush);
}

VisionCrossPointItem *VisionGraph_Region::_addPoint(QPointF pointF)
{
    // todo
    VisionCrossPointItem *item = new VisionCrossPointItem();
    item->setPoint(pointF);
    scene->addItem(item);
    return item;
}

VisionChainItem *VisionGraph_Region::_addChain(QList<QPointF> lstP)
{
    VisionChainItem* item = new VisionChainItem();
    item->setChainPos(lstP);
    scene->addItem(item);
    return item;
}

VisionEllipseItem *VisionGraph_Region::addEllipse(QRectF rf)
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
    return item;
}

VisionLineItem *VisionGraph_Region::addLine(QLine line)
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
    return item;
}

void VisionGraph_Region::addLines(QList<QLine> lstLine)
{

}

VisionPolygon *VisionGraph_Region::addPolygon(QVector<QPointF> vecPointF)
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
    return item;
}

VisionCrossPointItem *VisionGraph_Region::addPoint(QPointF pointF)
{
    // todo
    VisionCrossPointItem *item = new VisionCrossPointItem(true);
    QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
    QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QVector<QPointF>)),view,SLOT(slot_CreatePolygonF(bool,VisionItem*,ItemType,QVector<QPointF>)));
    QObject::connect(item,&QObject::destroyed,[=](){
        m_curVisionItem = nullptr;
    });
    item->setPoint(pointF);
    scene->addItem(item);
    m_curVisionItem = item;
    return item;
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

void VisionGraph_Region::setToolButton_Direction(ToolButtonDirection direct){
    m_toolButtonDirection = direct;

    if(infoWidget != NULL){
        infoWidget->deleteLater();
        infoWidget = NULL;
    }
    infoWidget = new QWidget();

    tool_Widget->removeAction(infoWidget_Action);
    if(m_toolButtonDirection == ToolButtonDirection::leftDirection ||
            m_toolButtonDirection == ToolButtonDirection::rightDirection){

        label_slider->setFixedSize(40,120);
        pSlider->setOrientation(Qt::Vertical);  // 竖直方向
        pSlider->setFixedHeight(100);
        pSlider->setMinimumWidth(20);

        QVBoxLayout* vBoxLayout = new QVBoxLayout;
        infoWidget->setLayout(vBoxLayout);

        vBoxLayout->addWidget(label_w);
        vBoxLayout->addWidget(pSpinBox_w);
        vBoxLayout->addWidget(label_h);
        vBoxLayout->addWidget(pSpinBox_h);

        vBoxLayout->setSpacing(5);
        vBoxLayout->addWidget(label_size);
        vBoxLayout->addWidget(comboBox);

        tool_Widget->setMinimumWidth(45);
    }else{

        label_slider->setFixedSize(120,40);
        pSlider->setOrientation(Qt::Horizontal);  // shuiping方向
        pSlider->setFixedWidth(100);
        pSlider->setMinimumHeight(20);

        QHBoxLayout* hBoxLayout = new QHBoxLayout;
        infoWidget->setLayout(hBoxLayout);

        hBoxLayout->addWidget(label_w);
        hBoxLayout->addWidget(pSpinBox_w);
        hBoxLayout->addWidget(label_h);
        hBoxLayout->addWidget(pSpinBox_h);

        hBoxLayout->setSpacing(5);
        hBoxLayout->addWidget(label_size);
        hBoxLayout->addWidget(comboBox);

        tool_Widget->setMinimumHeight(45);
    }

    QToolBar *tool_infoWidget = new QToolBar;
    tool_infoWidget->addWidget(infoWidget);
    tool_infoWidget->addSeparator();

    if(m_toolButtonDirection == ToolButtonDirection::leftDirection ||
            m_toolButtonDirection == ToolButtonDirection::rightDirection){
        tool_infoWidget->setOrientation(Qt::Vertical);
    }else{
        tool_infoWidget->setOrientation(Qt::Horizontal);
    }

    infoWidget_Action = tool_Widget->addWidget(tool_infoWidget);

    if(m_hBoxLayout != NULL){
        m_hBoxLayout->deleteLater();
        m_hBoxLayout = NULL;
    }
    if(m_vBoxLayout != NULL){
        m_vBoxLayout->deleteLater();
        m_vBoxLayout = NULL;
    }

    m_hBoxLayout = new QHBoxLayout;
    m_vBoxLayout = new QVBoxLayout;

    qDebug()<<tool_Widget->width()<<tool_Widget->height();

    if(m_toolButtonDirection == ToolButtonDirection::leftDirection){
        tool_Widget->setOrientation(Qt::Vertical);

        m_hBoxLayout->addWidget(tool_Widget);
        m_hBoxLayout->addWidget(sceneWidget);

        m_vBoxLayout->addLayout(m_hBoxLayout);
    }else if(m_toolButtonDirection == ToolButtonDirection::topDirection){
        tool_Widget->setOrientation(Qt::Horizontal);

        m_vBoxLayout->addWidget(tool_Widget);
        m_vBoxLayout->addWidget(sceneWidget);

    }else if(m_toolButtonDirection == ToolButtonDirection::rightDirection){
        tool_Widget->setOrientation(Qt::Vertical);

        m_hBoxLayout->addWidget(sceneWidget);
        m_hBoxLayout->addWidget(tool_Widget);

        m_vBoxLayout->addLayout(m_hBoxLayout);
    }else if(m_toolButtonDirection == ToolButtonDirection::bottomDirection){
        tool_Widget->setOrientation(Qt::Horizontal);

        m_vBoxLayout->addWidget(sceneWidget);
        m_vBoxLayout->addWidget(tool_Widget);
    }


    mainLayout->addLayout(m_vBoxLayout);
}

void VisionGraph_Region::setViewInfo_Visible(bool bVisible)
{
    view->setViewInfo_Visible(bVisible);
}

QToolButton *VisionGraph_Region::getToolButton(ToolButtonType type)
{
    switch(type)
    {
    case ToolButtonType::ToolButtonSys_selected:
        return sys_selected_button;
    case ToolButtonType::ToolButtonSys_drag:
        return sys_drag_button;
    case ToolButtonType::ToolButtonSys_zoom:
        return sys_zoom_button;
    case ToolButtonType::ToolButtonSys_mousePainter:
        return sys_mousePainter_button;
    case ToolButtonType::ToolButtonSys_mouseClear:
        return sys_mouseClear_button;
    case ToolButtonType::ToolButtonSys_save:
        return sys_save_button;
    case ToolButtonType::ToolButtonSys_rect:
        return sys_rect_button;
    case ToolButtonType::ToolButtonSys_ellipse:
        return sys_ellipse_button;
    case ToolButtonType::ToolButtonSys_poly:
        return sys_poly_button;
    case ToolButtonType::ToolButtonSys_poly_elli:
        return sys_poly_elli_button;
//    case ToolButtonType::ToolButtonSys_point:
//        return sys_point_button;
//    case ToolButtonType::ToolButtonSys_line:
//        return sys_line_button;
//    case ToolButtonType::ToolButtonSys_polyLine:
//        return sys_polyLine_button;
    case ToolButtonType::ToolButtonSys_open_project:
        return sys_open_button;
    case ToolButtonType::ToolButtonSys_front:
        return sys_front_button;
    case ToolButtonType::ToolButtonSys_next:
        return sys_next_button;
    case ToolButtonType::ToolButtonSys_clear:
        return sys_clear_button;
//    case ToolButtonType::ToolButtonSys_remove_item:
//        return sys_remove_item_button;
    default:
        return NULL;
    }
}

bool VisionGraph_Region::removeToolButton(ToolButtonType type)
{
    QToolButton* toolButton = NULL;
    switch(type)
    {
    case ToolButtonType::ToolButtonSys_selected:
        toolButton = sys_selected_button;
        break;
    case ToolButtonType::ToolButtonSys_drag:
        toolButton = sys_drag_button;
        break;
    case ToolButtonType::ToolButtonSys_zoom:
        toolButton = sys_zoom_button;
        break;
    case ToolButtonType::ToolButtonSys_mousePainter:
        toolButton = sys_mousePainter_button;
        break;
    case ToolButtonType::ToolButtonSys_mouseClear:
        toolButton = sys_mouseClear_button;
        break;
    case ToolButtonType::ToolButtonSys_save:
        toolButton = sys_save_button;
        break;
    case ToolButtonType::ToolButtonSys_rect:
//        tool_Widget->removeAction(m_lstAction);
        toolButton = sys_rect_button;
        break;
    case ToolButtonType::ToolButtonSys_ellipse:
        toolButton = sys_ellipse_button;
        break;
    case ToolButtonType::ToolButtonSys_poly:
        toolButton = sys_poly_button;
        break;
    case ToolButtonType::ToolButtonSys_poly_elli:
        toolButton = sys_poly_elli_button;
        break;
    case ToolButtonType::ToolButtonSys_open_project:
        toolButton = sys_open_button;
        break;
    case ToolButtonType::ToolButtonSys_front:
        toolButton = sys_front_button;
        break;
    case ToolButtonType::ToolButtonSys_next:
        toolButton = sys_next_button;
        break;
    case ToolButtonType::ToolButtonSys_clear:
        toolButton = sys_clear_button;
        break;
    default:
        return false;
    }

    for(int i=0;i<m_lstToolBtn.count();i++){
        if(m_lstToolBtn[i] == toolButton){
            tool_Widget->removeAction(m_lstAction[i]);
            break;
        }
    }
    return true;
}

void VisionGraph_Region::addToolButton(QToolButton *btn)
{
    btn->setToolButtonStyle(m_ToolStyle);
    btn->setIconSize(m_ToolIconSize);
    btn->setFixedSize(m_ToolBtnSize);
    qDebug()<<m_lstToolBtn.count();
    //
    m_lstAction.append(tool_Widget->insertWidget(m_insertAction,btn));
    m_lstToolBtn.append(btn);
}

void VisionGraph_Region::removeToolBarInfoWidget()
{
    tool_Widget->removeAction(infoWidget_Action);
}

void VisionGraph_Region::setViewRegion_Size(qreal w, qreal h)
{
    view->setViewRegion_Size(w,h);
    pSpinBox_w->setValue(w);
    pSpinBox_h->setValue(h);
}

void VisionGraph_Region::setViewRegion_Visible(bool bVisible)
{
    view->setViewRegion_Visible(bVisible);
}

void VisionGraph_Region::setViewRegion_Color(const QColor &color)
{
    view->setViewRegion_Color(color);
}

void VisionGraph_Region::slot_selected_action()
{
    view->setItemType(ItemType::No);
    m_itemType = ItemType::No;
//    label_Operation->setText(QStringLiteral("通过鼠标的拖动，拖动视图区域"));
}

void VisionGraph_Region::slot_drag_action()
{
    view->setItemType(ItemType::Drag);
    m_itemType = ItemType::Drag;
//    label_Operation->setText(QStringLiteral("通过鼠标的拖动，拖动视图区域"));
}

void VisionGraph_Region::slot_zoom_action()
{
    view->viewRegion_OriginPos();
//    view->setItemType(ItemType::Zoom);
//    m_itemType = ItemType::Zoom;
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
        m_bkPixmapItem->setPixmap(QPixmap(fileName).scaled(800,600,Qt::KeepAspectRatioByExpanding));
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
    m_mousePixmap->setPixmap(QPixmap(iconPath+"cursor-size_Circle.png").scaled(qR,qR,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    qreal qx = view->sceneRect().x()+view->sceneRect().width()/2;
    qreal qy = view->sceneRect().y()+view->sceneRect().height()/2;
//    qDebug()<<qx<<qy;
    m_mousePixmap->setPos(qx-m_mousePixmap->boundingRect().width()/2,qy-m_mousePixmap->boundingRect().height()/2);
    view->setPainterCursorR((qreal)qR/2);
}

void VisionGraph_Region::slot_SizeChanged(QString currentSize)
{
//    qDebug()<<" view scale size is changed : "<<currentSize;
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


//    view->viewport()->move(100,100);
    view->resize(sceneWidget->width(),sceneWidget->height());
//    scene->setSceneRect(0,0,sceneWidget->width(),sceneWidget->height());
//    view->setScene(scene);
//    view->setSceneRect(0,0,sceneWidget->width(),sceneWidget->height());
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

void VisionGraph_Region::slot_SpinBox_ViewRegionSize(int w)
{
    view->setViewRegion_Size(pSpinBox_w->value(),pSpinBox_h->value());
}


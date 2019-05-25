#include "visiongraph_.h"

#include <QDebug>
#include <QtMath>
#include <QFileDialog>
#include <QDateTime>
#include <QWidget>
#include <QFileDialog>

#include "visiongraph.h"
VisionGraph_::VisionGraph_(GraphType type, ToolButtonDirection toolButtonDirect, QWidget *parent) : QFrame(parent)
{
    mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);

    m_toolButtonDirection = toolButtonDirect;
    m_graphType = type;

    initScene();
    initLayout(toolButtonDirect);

    setGraphType(type);

    connect(this,SIGNAL(signal_itemFinished(VisionItem*)),this,SLOT(slotItemFinished(VisionItem*)));

}

VisionGraph_::~VisionGraph_()
{
    delete sys_selected_button;
    delete sys_drag_button;
    delete sys_zoom_button;  //将拖动的恢复到当前窗口
    delete sys_fit_button;  //调整比例，适应当前窗口
    delete sys_mousePainter_button;
    delete sys_mouseClear_button;
    delete sys_save_button;
    delete sys_rect_button;
    delete sys_ellipse_button;
    delete sys_circle_button;
    delete sys_arc_button;
    delete sys_poly_button;
    delete sys_poly_elli_button;
    delete sys_point_button;
    delete sys_line_button;
    delete sys_polyLine_button;

    //右侧工具栏 -- 功能类
    delete sys_open_project_button;  //打开工程
    delete sys_front_button;  //撤销
    delete sys_next_button;   //取消撤销
    delete sys_clear_button;  //清空绘图区域
    delete sys_remove_item_button;  //删除当前选中的item

    delete tool_infoWidget;
//    delete infoWidget;
}


void VisionGraph_::setGraphType(GraphType type)
{
    m_graphType = type;
    slot_GraphTypeChanged(type);
    view->setGraphType(type);
}

void VisionGraph_::setSceneWidgetSize(QSize size)
{
    sceneWidget->resize(size);
}

void VisionGraph_::setSceneWidgetSize(qreal w, qreal h)
{
    sceneWidget->resize(w,h);
}

void VisionGraph_::setThemeColor(ThemeColor theme)
{
    QColor selectedColor,borderColor,brushColor;
    if(theme == ThemeColor::dark){
        selectedColor = QColor(255,0,0);
        borderColor = QColor(255,0,0);
        brushColor = QColor(255,0,0,160);
//        regionColor = QColor(255,0,0);
    }else if(theme == ThemeColor::lightBlue){
        selectedColor = QColor(0,0,0);
        borderColor = QColor(100,149,237);
        brushColor = QColor(50,75,119,70);
//        regionColor = QColor(255,0,0);
    }else{
        selectedColor = QColor(255,0,0);
        borderColor = QColor(255,0,0);
        brushColor = QColor(255,0,0,160);
//        regionColor = QColor(255,0,0);
    }

    setRectColor(borderColor,selectedColor,brushColor);
    setEllipseColor(borderColor,selectedColor,brushColor);
    setCircleColor(borderColor,selectedColor,brushColor);
    setPolyColor(borderColor,selectedColor,brushColor);
    setPolyLineColor(borderColor,selectedColor,brushColor);
    setArcColor(borderColor,selectedColor,brushColor);
    setPointColor(borderColor,selectedColor,brushColor);
    setLineColor(borderColor,selectedColor,brushColor);

    setRegionColor(borderColor,selectedColor,brushColor);

    setListRegionColor(borderColor,selectedColor,brushColor);

}


void VisionGraph_::initScene()
{
    sceneWidget = new VisionGraphWidget;
    sceneWidget->setMinimumSize(400,300);
    connect(sceneWidget,SIGNAL(signal_sizeChanged(qreal,qreal)),this,SLOT(slot_SizeChanged(qreal,qreal)));

    view = new VisionGraphView(sceneWidget);
    QObject::connect(view,SIGNAL(signal_Item(ItemType,QRectF)),this,SLOT(slot_addItem(ItemType,QRectF)));
    QObject::connect(view,SIGNAL(signal_Item_poly(QVector<QPointF>,ItemType)),this,SLOT(slot_addPoly(QVector<QPointF>,ItemType)));
    QObject::connect(view,SIGNAL(signal_Item_point(QPointF)),this,SLOT(slot_addPoint(QPointF)));
    QObject::connect(view,SIGNAL(signal_Item_Line(QLine)),this,SLOT(slot_addLine(QLine)));
    QObject::connect(view,SIGNAL(signal_Move(QPointF)),this,SLOT(slot_mouseMove(QPointF)));
    QObject::connect(view,SIGNAL(signal_wheel(qreal)),this,SLOT(slot_wheel(qreal)));

    QObject::connect(view,SIGNAL(signal_RegionItem()),this,SLOT(slot_addRegion()));

    scene = new VisionGraphScene(sceneWidget);
    connect(scene,SIGNAL(signal_MouseMove(qreal,qreal)),this,SLOT(slot_SceneMouseMove(qreal,qreal)));
    scene->setSceneRect(0,0,800,600);
    view->setScene(scene);

    m_bkPixmapItem = new QGraphicsPixmapItem();
    scene->addItem(m_bkPixmapItem);

    m_mousePixmap = new QGraphicsPixmapItem();
    m_mousePixmap->setPos(scene->width()/2-10,scene->height()/2-10);
    m_mousePixmap->setPixmap(QPixmap(iconPath+"cursor-size_Circle.png").scaled(10*2,10*2));
    scene->addItem(m_mousePixmap);
    m_mousePixmap->hide();
}


void VisionGraph_::initTool_operation()
{
    QAction* sys_open_project = new QAction(QIcon(QPixmap(iconPath+"open.png").scaled(50,50)),QStringLiteral("打开"),this);
    sys_open_project->setIconText(QStringLiteral("打开"));
    connect(sys_open_project,SIGNAL(triggered(bool)),this,SLOT(slot_open_project()));
    sys_open_project_button = new QToolButton;
    sys_open_project_button->setDefaultAction(sys_open_project);

    QAction* sys_save_action = new QAction(QIcon(QPixmap(iconPath+"save.png").scaled(50,50)),QStringLiteral("保存"),this);
    sys_save_action->setIconText(QStringLiteral("保存"));
    connect(sys_save_action,SIGNAL(triggered(bool)),this,SLOT(slot_save_action()));
    sys_save_button = new QToolButton;
    sys_save_button->setDefaultAction(sys_save_action);
    //撤销按钮（回滚）历史
    QAction* sys_front_action = new QAction(QIcon(QPixmap(iconPath+"back.png").scaled(50,50)),QStringLiteral("撤销"),this);
    sys_front_action->setIconText(QStringLiteral("撤销"));
    connect(sys_front_action,SIGNAL(triggered(bool)),this,SLOT(slot_front_action()));
    sys_front_button = new QToolButton;
    sys_front_button->setDefaultAction(sys_front_action);
    //撤销按钮（后滚）未来
    QAction* sys_next_action = new QAction(QIcon(QPixmap(iconPath+"front.png").scaled(50,50)),QStringLiteral("恢复"),this);
    sys_next_action->setIconText(QStringLiteral("恢复"));
    connect(sys_next_action,SIGNAL(triggered(bool)),this,SLOT(slot_next_action()));
    sys_next_button = new QToolButton;
    sys_next_button->setDefaultAction(sys_next_action);
    //清空绘图区域
    QAction* sys_clear_action = new QAction(QIcon(QPixmap(iconPath+"delect.png").scaled(50,50)),QStringLiteral("清理"),this);
    sys_clear_action->setIconText(QStringLiteral("清理"));
    connect(sys_clear_action,SIGNAL(triggered(bool)),this,SLOT(slot_clear_action()));
    sys_clear_button = new QToolButton;
    sys_clear_button->setDefaultAction(sys_clear_action);
    QAction* sys_remove_item = new QAction(QIcon(QPixmap(iconPath+"remove.png").scaled(50,50)),QStringLiteral("删除当前选中的item"),this);
    sys_remove_item->setShortcut(QKeySequence::Delete);
    sys_remove_item->setIconText(QStringLiteral("删除"));
    connect(sys_remove_item,SIGNAL(triggered(bool)),this,SLOT(slot_removeItem_action()));
    sys_remove_item_button = new QToolButton;
    sys_remove_item_button->setDefaultAction(sys_remove_item);
    //调整鼠标的大小--针对鼠标擦除和鼠标绘制

    tool_Widget = new QToolBar;
    tool_Widget->setMinimumHeight(20);
    tool_Widget->setMovable(false);

//    m_lstAction.append(tool_Widget->addWidget(sys_open_project_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_save_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_front_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_next_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_clear_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_remove_item_button));
//    tool_Widget->addSeparator();

    m_lstToolBtn.append(sys_open_project_button);
    m_lstToolBtn.append(sys_save_button);
    m_lstToolBtn.append(sys_front_button);
    m_lstToolBtn.append(sys_next_button);
    m_lstToolBtn.append(sys_clear_button);
    m_lstToolBtn.append(sys_remove_item_button);

    //选中按钮---绘制规则形状的时候，绘制完成后默认选中，此时高亮，其他时间都是灰色
    QAction* sys_selected_action = new QAction(QIcon(QPixmap(iconPath+"select.png").scaled(50,50)),QStringLiteral(""),this);
    sys_selected_action->setIconText(QStringLiteral("选择"));
    connect(sys_selected_action,SIGNAL(triggered(bool)),this,SLOT(slot_selected_action()));
    sys_selected_button = new QToolButton;
    sys_selected_button->setDefaultAction(sys_selected_action);
    //拖动按钮---拖动整个绘制的区域的位置
    QAction* sys_drag_action = new QAction(QIcon(QPixmap(iconPath+"drag.png").scaled(50,50)),QStringLiteral("拖动当前视图"),this);
    sys_drag_action->setIconText(QStringLiteral("拖动"));
    connect(sys_drag_action,SIGNAL(triggered(bool)),this,SLOT(slot_drag_action()));
    sys_drag_button = new QToolButton;
    sys_drag_button->setDefaultAction(sys_drag_action);
    //放大镜功能  --->> 恢复到起始地点
    QAction* sys_zoom_action = new QAction(QIcon(QPixmap(iconPath+"zoom.png").scaled(50,50)),QStringLiteral("居中"),this);
    sys_zoom_action->setIconText(QStringLiteral("居中"));
    connect(sys_zoom_action,SIGNAL(triggered(bool)),this,SLOT(slot_zoom_action()));
    sys_zoom_button = new QToolButton;
    sys_zoom_button->setDefaultAction(sys_zoom_action);

    //图片自适应
    QAction* sys_fit_action = new QAction(QIcon(QPixmap(iconPath+"zoomfit.png").scaled(50,50)),QStringLiteral("自适应"),this);
    sys_fit_action->setIconText(QStringLiteral("自适应"));
    connect(sys_fit_action,SIGNAL(triggered(bool)),this,SLOT(slot_fit_action()));
    sys_fit_button = new QToolButton;
    sys_fit_button->setDefaultAction(sys_fit_action);

    //鼠标擦除
    QAction* sys_mouseClear_action = new QAction(QIcon(QPixmap(iconPath+"clear.png").scaled(50,50)),QStringLiteral("擦除"),this);
    sys_mouseClear_action->setIconText(QStringLiteral("擦除"));
    sys_mouseClear_action->setText("mouseClear");
    connect(sys_mouseClear_action,SIGNAL(triggered(bool)),this,SLOT(slot_mouseClear_action()));
    sys_mouseClear_button = new QToolButton;
    sys_mouseClear_button->setDefaultAction(sys_mouseClear_action);
    //鼠标绘制
    QAction* sys_mousePainter_action = new QAction(QIcon(QPixmap(iconPath+"painter.png").scaled(50,50)),QStringLiteral("绘制"),this);
    sys_mousePainter_action->setIconText(QStringLiteral("绘制"));
    sys_mousePainter_action->setText("mousePainter");
    connect(sys_mousePainter_action,SIGNAL(triggered(bool)),this,SLOT(slot_mousePainter_action()));
    sys_mousePainter_button = new QToolButton;
    sys_mousePainter_button->setDefaultAction(sys_mousePainter_action);
    //矩形
    QAction* sys_rect_action = new QAction(QIcon(QPixmap(iconPath+"rect.png").scaled(50,50)),QStringLiteral("新建一个矩形区域"),this);
    sys_rect_action->setIconText(QStringLiteral("矩形"));
    sys_rect_action->setText("rectangle");
    connect(sys_rect_action,SIGNAL(triggered(bool)),this,SLOT(slot_rect_action()));
    sys_rect_button = new QToolButton;
    sys_rect_button->setDefaultAction(sys_rect_action);
    //椭圆
    QAction* sys_ellipse_action = new QAction(QIcon(QPixmap(iconPath+"ellipse.png").scaled(50,50)),QStringLiteral("新建一个椭圆区域"),this);
    sys_ellipse_action->setIconText(QStringLiteral("椭圆或者圆"));
    sys_ellipse_action->setText("ellipse");
    connect(sys_ellipse_action,SIGNAL(triggered(bool)),this,SLOT(slot_ellipse_action()));
    sys_ellipse_button = new QToolButton;
    sys_ellipse_button->setDefaultAction(sys_ellipse_action);
    //圆
    QAction* sys_circle_action = new QAction(QIcon(QPixmap(iconPath+"circle.png").scaled(50,50)),QStringLiteral("新建一个圆区域"),this);
    sys_circle_action->setIconText(QStringLiteral("圆"));
    sys_circle_action->setText("circle");
    connect(sys_circle_action,SIGNAL(triggered(bool)),this,SLOT(slot_circle_action()));
    sys_circle_button = new QToolButton;
    sys_circle_button->setDefaultAction(sys_circle_action);
    //圆弧
    QAction* sys_arc_action = new QAction(QIcon(QPixmap(iconPath+"arc.png").scaled(50,50)),QStringLiteral("新建一个圆弧"),this);
    sys_arc_action->setIconText(QStringLiteral("圆弧"));
    sys_arc_action->setText("Arc");
    connect(sys_arc_action,SIGNAL(triggered(bool)),this,SLOT(slot_arc_action()));
    sys_arc_button = new QToolButton;
    sys_arc_button->setDefaultAction(sys_arc_action);
    //不规则多边形---直线连接各点
    QAction* sys_poly_action = new QAction(QIcon(QPixmap(iconPath+"poly.png").scaled(50,50)),QStringLiteral("新建一个不规则多边形区域"),this);
    sys_poly_action->setIconText(QStringLiteral("多边形"));
    sys_poly_action->setText("poly");
    connect(sys_poly_action,SIGNAL(triggered(bool)),this,SLOT(slot_poly_action()));
    sys_poly_button = new QToolButton;
    sys_poly_button->setDefaultAction(sys_poly_action);
    //不规则圆形---曲线连接各点
    QAction* sys_poly_elli_action = new QAction(QIcon(QPixmap(iconPath+"poly_elli.png").scaled(50,50)),QStringLiteral("任意区域：绘制不规则区域"),this);
    sys_poly_elli_action->setIconText(QStringLiteral("任意区域"));
    sys_poly_elli_action->setText("region");
    connect(sys_poly_elli_action,SIGNAL(triggered(bool)),this,SLOT(slot_poly_elli_action()));
    sys_poly_elli_button = new QToolButton;
    sys_poly_elli_button->setDefaultAction(sys_poly_elli_action);

    QAction* sys_point_action = new QAction(QIcon(QPixmap(iconPath+"point.png").scaled(50,50)),QStringLiteral("绘制点"),this);
    sys_point_action->setIconText(QStringLiteral("点"));
    sys_point_action->setText("point");
    connect(sys_point_action,SIGNAL(triggered(bool)),this,SLOT(slot_point_action()));
    sys_point_button = new QToolButton;
    sys_point_button->setDefaultAction(sys_point_action);

    QAction* sys_line_action = new QAction(QIcon(QPixmap(iconPath+"line.png").scaled(50,50)),QStringLiteral("绘制直线"),this);
    sys_line_action->setIconText(QStringLiteral("直线"));
    sys_line_action->setText("line");
    connect(sys_line_action,SIGNAL(triggered(bool)),this,SLOT(slot_line_action()));
    sys_line_button = new QToolButton;
    sys_line_button->setDefaultAction(sys_line_action);

    QAction* sys_polyLine_action = new QAction(QIcon(QPixmap(iconPath+"polyline.png").scaled(50,50)),QStringLiteral("绘制折线"),this);
    sys_polyLine_action->setIconText(QStringLiteral("折线"));
    sys_polyLine_action->setText("polyLine");
    connect(sys_polyLine_action,SIGNAL(triggered(bool)),this,SLOT(slot_polyLine_action()));
    sys_polyLine_button = new QToolButton;
    sys_polyLine_button->setDefaultAction(sys_polyLine_action);

    //调整鼠标的大小--针对鼠标擦除和鼠标绘制

//    m_lstAction.append(tool_Widget->addWidget(sys_selected_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_drag_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_zoom_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_fit_button));
//    m_insertAction = tool_Widget->addSeparator();

//    m_lstAction.append(tool_Widget->addWidget(sys_mouseClear_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_mousePainter_button));
//    tool_Widget->addSeparator();

//    m_lstAction.append(tool_Widget->addWidget(sys_rect_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_ellipse_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_poly_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_poly_elli_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_point_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_line_button));
//    m_insertAction = tool_Widget->addSeparator();

    connect(tool_Widget,SIGNAL(actionTriggered(QAction*)),this,SLOT(slot_actionTriggered(QAction*)));

    m_lstToolBtn.append(sys_selected_button);
    m_lstToolBtn.append(sys_drag_button);
    m_lstToolBtn.append(sys_zoom_button);
    m_lstToolBtn.append(sys_fit_button);
    m_lstToolBtn.append(sys_mouseClear_button);
    m_lstToolBtn.append(sys_mousePainter_button);
    m_lstToolBtn.append(sys_rect_button);
    m_lstToolBtn.append(sys_ellipse_button);
    m_lstToolBtn.append(sys_circle_button);
    m_lstToolBtn.append(sys_arc_button);
    m_lstToolBtn.append(sys_poly_button);
    m_lstToolBtn.append(sys_poly_elli_button);
    m_lstToolBtn.append(sys_point_button);
    m_lstToolBtn.append(sys_line_button);

    //设置绘制鼠标的大小
    label_mouseSizeText = new QLabel;
    label_mouseSizeText->setText(QStringLiteral("大小"));
    label_mouseSizeText->setAlignment(Qt::AlignCenter);

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
    pSpinBox = new QSpinBox;
    pSpinBox->setMinimum(1);  // 最小值
    pSpinBox->setMaximum(300);  // 最大值
    pSpinBox->setSingleStep(1);  // 步长

    // 连接信号槽（相互改变）
    connect(pSpinBox, SIGNAL(valueChanged(int)), pSlider, SLOT(setValue(int)));
    connect(pSlider, SIGNAL(valueChanged(int)), pSpinBox, SLOT(setValue(int)));
    connect(pSlider,SIGNAL(valueChanged(int)),this,SLOT(slot_valueChanged(int)));

    pSlider->setValue(10);  //默认值
//    tool_Widget->addWidget(label_mouseSizeText);
//    tool_Widget->addWidget(label_slider);
//    tool_Widget->addWidget(pSpinBox);
//    tool_Widget->addSeparator();

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
    pSpinBox_w->setStyleSheet("QSpinBox::up-button{width:0;height:0;}"
        "QSpinBox::down-button{width:0;height:0;}");
    pSpinBox_w->setValue(800);
    connect(pSpinBox_w,SIGNAL(valueChanged(int)),this,SLOT(slot_SpinBox_ViewRegionSize(int)));

    label_h = new QLabel;
    label_h->setText(QStringLiteral("高度:"));

    // 微调框
    pSpinBox_h = new QSpinBox;
    pSpinBox_h->setMinimum(1);  // 最小值
    pSpinBox_h->setMaximum(5000);  // 最大值
    pSpinBox_h->setSingleStep(5);  // 步长
    pSpinBox_h->setStyleSheet("QSpinBox::up-button{width:0;height:0;}"
        "QSpinBox::down-button{width:0;height:0;}");
    pSpinBox_h->setValue(600);
    connect(pSpinBox_h,SIGNAL(valueChanged(int)),this,SLOT(slot_SpinBox_ViewRegionSize(int)));


    label_size = new QLabel;
    label_size->setText(QStringLiteral("尺寸:"));

    comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->lineEdit()->setValidator(new QIntValidator(0,10,comboBox->lineEdit())); //0, 100为输入的数字值范围
    comboBox->addItem("0.10");
    comboBox->addItem("0.25");
    comboBox->addItem("0.50");
    comboBox->addItem("1.00");
    comboBox->addItem("2.00");
    comboBox->addItem("5.00");
    comboBox->setCurrentText("1.00");
    comboBox->lineEdit()->setAlignment(Qt::AlignLeft);
    QLineEdit* lineEdit = comboBox->lineEdit();
//    connect(lineEdit,SIGNAL(returnPressed()),this,SLOT(slot_SizeChanged()));
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

    tool_infoWidget = new QToolBar;
    tool_infoWidget->addWidget(infoWidget);
    tool_infoWidget->addSeparator();

    if(m_toolButtonDirection == ToolButtonDirection::leftDirection ||
            m_toolButtonDirection == ToolButtonDirection::rightDirection){
        tool_infoWidget->setOrientation(Qt::Vertical);
    }else{
        tool_infoWidget->setOrientation(Qt::Horizontal);
    }

//    infoWidget_Action = tool_Widget->addWidget(tool_infoWidget);

    for(int i=0;i<m_lstToolBtn.count();i++){
        m_lstToolBtn[i]->setToolButtonStyle(m_ToolStyle);
        m_lstToolBtn[i]->setIconSize(m_ToolIconSize);
        m_lstToolBtn[i]->setFixedSize(m_ToolBtnSize);
    }
}

void VisionGraph_::initToolBar()
{

}

void VisionGraph_::initLayout(ToolButtonDirection toolButtonDirect)
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

bool VisionGraph_::checkoutItem()
{
    if(m_graphType == GraphType::graphRegion || m_graphType == GraphType::graph_Info)
        return true;

//    this->scene->update();


    //在进行交互的时候进行check   程序调用addItem是否有效？
    if(m_viewType == ViewType::singleItem){
        //当view要求单一item的时候，执行函数体
        //存在item,判断，删除当前view中的item，并进行绘制 or 不做操作
        if(m_lstItem.count() >= 1){
            return false;
        }else{
            return true;
        }
    }else if(m_viewType == ViewType::_singleItem){
        if(m_lstItem.count() >= 1){
//            slot_removeItem_action();
            view->clearPainter();
            if(m_curVisionItem != nullptr){
                m_curVisionItem->hide();
                m_curVisionItem = nullptr;
            }
            //m_lstItem存在内存泄漏的可能
        }
        return true;
    }else{
        return true;
    }
}

vector<VisionItem*> VisionGraph_::getData()
{
    return m_lstItem.toVector().toStdVector();
}

VisionItem *VisionGraph_::getCurData()
{
//    qDebug()<<m_curVisionItem->getType();
    if(m_curVisionItem == NULL)
        return NULL;

    return m_curVisionItem;
}

void VisionGraph_::setRectColor(QColor borderColor, QColor selectColor, QColor brushColor)
{
    borderColor_Rect = borderColor;
    selectedColor_Rect = selectColor;
    brushColor_Rect = brushColor;
}

void VisionGraph_::setEllipseColor(QColor borderColor, QColor selectColor, QColor brushColor)
{
    borderColor_Ellipse = borderColor;
    selectedColor_Ellipse = selectColor;
    brushColor_Ellipse = brushColor;
}

void VisionGraph_::setCircleColor(QColor borderColor, QColor selectColor, QColor brushColor)
{
    borderColor_Circle = borderColor;
    selectedColor_Circle = selectColor;
    brushColor_Circle = brushColor;
}

void VisionGraph_::setPolyColor(QColor borderColor, QColor selectColor, QColor brushColor)
{
    borderColor_Poly = borderColor;
    selectedColor_Poly = selectColor;
    brushColor_Poly = brushColor;
}

void VisionGraph_::setPolyLineColor(QColor borderColor, QColor selectColor, QColor brushColor)
{
    borderColor_PolyLine = borderColor;
    selectedColor_PolyLine = selectColor;
    brushColor_PolyLine = brushColor;
}

void VisionGraph_::setArcColor(QColor borderColor, QColor selectColor, QColor brushColor)
{
    borderColor_Arc = borderColor;
    selectedColor_Arc = selectColor;
    brushColor_Arc = brushColor;
}

void VisionGraph_::setPointColor(QColor borderColor, QColor selectColor, QColor brushColor)
{
    borderColor_Point = borderColor;
    selectedColor_Point = selectColor;
    brushColor_Point = brushColor;
}

void VisionGraph_::setLineColor(QColor borderColor, QColor selectColor, QColor brushColor)
{
    borderColor_Line = borderColor;
    selectedColor_Line = selectColor;
    brushColor_Line = brushColor;
}

void VisionGraph_::setRegionColor(QColor borderColor, QColor selectColor, QColor brushColor, QColor brushColor_unEdit)
{
    view->setRegionColor(borderColor,selectColor,brushColor,brushColor_unEdit);
}

void VisionGraph_::setListRegionColor(QColor borderColor, QColor selectColor, QColor brushColor)
{
    borderColor_Region = borderColor;
    selectedColor_Region = selectColor;
    brushColor_Region = brushColor;
}

QGraphicsRectItem *VisionGraph_::_addRect(const QRectF &rect, const QPen &pen, const QBrush &brush)
{
    return scene->addRect(rect,pen,brush);
}

QGraphicsPolygonItem *VisionGraph_::_addPolygon(const QPolygonF &polygon, const QPen &pen, const QBrush &brush)
{
    return scene->addPolygon(polygon,pen,brush);
}

QGraphicsLineItem *VisionGraph_::_addLine(const QLineF &line, const QPen &pen)
{
    return scene->addLine(line,pen);
}

QGraphicsEllipseItem *VisionGraph_::_addEllipse(const QRectF &rect, const QPen &pen, const QBrush &brush)
{
    return scene->addEllipse(rect,pen,brush);
}

VisionCrossPointItem *VisionGraph_::_addPoint(QPointF pointF, bool edit, qreal length, bool color_enable, QColor color)
{
    VisionCrossPointItem *item = new VisionCrossPointItem(edit,length,color_enable,color);
    item->setPoint(pointF);
    scene->addItem(item);
    return item;
}

VisionChainItem *VisionGraph_::_addChain(QList<QPointF> lstP, bool bClosed, bool bEdit, bool color_enable, QColor color)
{
    VisionChainItem* item = new VisionChainItem(bClosed,bEdit,color_enable,color);
    item->setChainPos(lstP);
    scene->addItem(item);
    return item;
}

VisionArrow *VisionGraph_::_addArrow(QPointF pointF, bool bEdit, bool color_enable, QColor color)
{
    VisionArrow* item = new VisionArrow(bEdit,color_enable,color);
    item->setPointF(pointF);
    item->setColor(color);
    scene->addItem(item);
    return item;
}

VisionCoordinateItem *VisionGraph_::_addCoordinate(QPointF p, qreal angle, qreal length, bool bEdit, bool color_enable, QColor color)
{
    //绘制坐标系，目前的坐标系都是不可编辑的
    VisionCoordinateItem* item = new VisionCoordinateItem(bEdit,color_enable,color);
    item->setPointF(p);
    item->setColor(color);
    item->setAngle(angle);
    item->setCoordinateLength(length);
    scene->addItem(item);
    return item;
}

VisionRectItem *VisionGraph_::addRect(QRectF rf, qreal angle, bool bEdit, bool bRotation, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    if(!checkoutItem())
        return NULL;

    if(bEdit){
        VisionRectItem* item = new VisionRectItem(bEdit,bRotation,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
        QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
        QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)),view,SLOT(slot_updatePath(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)));
        QObject::connect(item,SIGNAL(signalChanged(VisionItem*)),this,SIGNAL(signal_Changed(VisionItem*)));

        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setRect(rf,angle);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }else{
        VisionRectItem* item = new VisionRectItem(bEdit,bRotation,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setRect(rf,angle);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }
    return NULL;
}

VisionArrow *VisionGraph_::addArrow(QPointF pointF, bool bEdit, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    //特殊的控件
    VisionArrow* item = new VisionArrow(bEdit,color_enable,borderColor,selectedColor,brushColor);
    QObject::connect(item,&QObject::destroyed,[=](){
        m_lstItem.removeOne(item);
        m_curVisionItem = nullptr;

    });
    item->setPointF(pointF);
    item->setColor(borderColor);
    scene->addItem(item);
    m_curVisionItem = item;
    m_lstItem.push_back(item);
    return item;
}

VisionEllipseItem *VisionGraph_::addEllipse(QRectF rf, qreal angle, bool bEdit, bool bRotation, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    if(!checkoutItem())
        return NULL;

    if(bEdit){
        VisionEllipseItem *item = new VisionEllipseItem(bEdit,bRotation,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
        QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
        QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)),view,SLOT(slot_updatePath(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)));
        QObject::connect(item,SIGNAL(signalChanged(VisionItem*)),this,SIGNAL(signal_Changed(VisionItem*)));

        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setRect(rf,angle);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }else{
        VisionEllipseItem* item = new VisionEllipseItem(bEdit,bRotation,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setRect(rf,angle);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }
}

VisionCircleItem *VisionGraph_::addCircle(QRectF rf, bool bEdit, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    if(!checkoutItem())
        return NULL;

    if(bEdit){
        VisionCircleItem *item = new VisionCircleItem(bEdit,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
        QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
        QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)),view,SLOT(slot_updatePath(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)));
        QObject::connect(item,SIGNAL(signalChanged(VisionItem*)),this,SIGNAL(signal_Changed(VisionItem*)));

        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setCircle(rf);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }else{
        VisionCircleItem* item = new VisionCircleItem(bEdit,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setCircle(rf);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }
}


VisionArcItem *VisionGraph_::addArc(QPointF sP, QPointF mP, QPointF fP, bool bEdit, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    if(!checkoutItem())
        return NULL;

    if(bEdit){
        VisionArcItem *item = new VisionArcItem(bEdit,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
        QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
        QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)),view,SLOT(slot_updatePath(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)));
        QObject::connect(item,SIGNAL(signalChanged(VisionItem*)),this,SIGNAL(signal_Changed(VisionItem*)));

        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setPointFs(sP,mP,fP);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }else{
        VisionArcItem *item = new VisionArcItem(bEdit,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setPointFs(sP,mP,fP);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }
}

VisionArcItem *VisionGraph_::addArc(QPointF center, qreal r, qreal angle, qreal spanAngle, bool bEdit, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    if(!checkoutItem())
        return NULL;

    if(bEdit){
        VisionArcItem *item = new VisionArcItem(bEdit,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
        QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
        QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)),view,SLOT(slot_updatePath(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)));
        QObject::connect(item,SIGNAL(signalChanged(VisionItem*)),this,SIGNAL(signal_Changed(VisionItem*)));

        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setArc(center, r, angle, spanAngle);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }else{
        VisionArcItem *item = new VisionArcItem(bEdit,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setArc(center, r, angle, spanAngle);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }
}

VisionLineItem *VisionGraph_::addLine(QLine line, bool bEdit, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    if(!checkoutItem())
        return NULL;

    if(bEdit){
        VisionLineItem *item = new VisionLineItem(bEdit,line.p1(),line.p2(),0,color_enable,borderColor,selectedColor,brushColor);

        QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
        QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
        QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)),view,SLOT(slot_updatePath(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)));
        QObject::connect(item,SIGNAL(signalChanged(VisionItem*)),this,SIGNAL(signal_Changed(VisionItem*)));

        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
    //    item->setLine(line.p1(),line.p2());
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }else{
        VisionLineItem *item = new VisionLineItem(bEdit,line.p1(),line.p2(),0,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }
}

VisionLine *VisionGraph_::addLines(QList<QLineF> lstLineF, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    //特殊控件添加---只能通过程序添加
    VisionLine *item = new VisionLine(color_enable,borderColor,selectedColor,brushColor);
    item->setLines(lstLineF);
    scene->addItem(item);
    m_curVisionItem = item;
    m_lstItem.push_back(item);
    emit signal_itemFinished(item);
    return item;
}

VisionPolygon *VisionGraph_::addPolygon(QVector<QPointF> vecPointF, bool bClose, bool bEdit, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    if(!checkoutItem())
        return NULL;

    if(bEdit){
        if(vecPointF.count() <= 0)
            return NULL;
        qDebug()<<"add polygon";
        VisionPolygon *item = new VisionPolygon(bClose,bEdit,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
        QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
        QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType, QVector<QPointF>)),view,SLOT(slot_CreatePolygonF(bool,VisionItem*,ItemType, QVector<QPointF>)));
        QObject::connect(item,SIGNAL(signalChanged(VisionItem*)),this,SIGNAL(signal_Changed(VisionItem*)));

        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
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
        emit signal_itemFinished(item);
        return item;
    }else{
        if(vecPointF.count() <= 0)
            return NULL;
        VisionPolygon *item = new VisionPolygon(bClose,bEdit,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
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
        emit signal_itemFinished(item);
        return item;
    }
}

VisionCrossPointItem* VisionGraph_::addPoint(QPointF pointF, bool bEdit, qreal length, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    if(!checkoutItem())
        return NULL;

    if(bEdit){
        VisionCrossPointItem *item = new VisionCrossPointItem(bEdit,length,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
        QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
        QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)),view,SLOT(slot_updatePath(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)));
        QObject::connect(item,SIGNAL(signalChanged(VisionItem*)),this,SIGNAL(signal_Changed(VisionItem*)));

        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setPoint(pointF);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }else{
        VisionCrossPointItem *item = new VisionCrossPointItem(bEdit,length,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setPoint(pointF);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }
}

VisionPoint *VisionGraph_::addPointFs(QList<QPointF> lstP, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    VisionPoint *item = new VisionPoint(color_enable,borderColor,selectedColor,brushColor);
    item->setPointFs(lstP);
    scene->addItem(item);
    m_curVisionItem = item;
    m_lstItem.push_back(item);
    emit signal_itemFinished(item);
    return item;
}

VisionChainItem *VisionGraph_::addChain(QList<QPointF> lstP, bool close, bool edit, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    if(!checkoutItem())
        return NULL;

    if(edit){
        VisionChainItem *item = new VisionChainItem(close,edit,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
        QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
        QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)),view,SLOT(slot_updatePath(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)));
        QObject::connect(item,SIGNAL(signalChanged(VisionItem*)),this,SIGNAL(signal_Changed(VisionItem*)));

        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setChainPos(lstP);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }else{
        VisionChainItem* item = new VisionChainItem(close,edit,color_enable,borderColor,selectedColor,brushColor);
        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setChainPos(lstP);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }
}

VisionLineItemFitting *VisionGraph_::addLineFitting(QLine line, bool bEdit, qreal length, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    if(!checkoutItem())
        return NULL;

    if(bEdit){
        VisionLineItemFitting *item = new VisionLineItemFitting(bEdit,line.p1(),line.p2(),length,0,color_enable,borderColor,selectedColor,brushColor);

        QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
        QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
        QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)),view,SLOT(slot_updatePath(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)));
        QObject::connect(item,SIGNAL(signalChanged(VisionItem*)),this,SIGNAL(signal_Changed(VisionItem*)));

        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }else{
        VisionLineItemFitting *item = new VisionLineItemFitting(bEdit,line.p1(),line.p2(),length,0,color_enable,borderColor,selectedColor,brushColor);

        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }
}

VisionArcItemFitting *VisionGraph_::addArcFitting(QPointF sP, QPointF mP, QPointF fP, bool bEdit, qreal length, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    if(!checkoutItem())
        return NULL;

    if(bEdit){
        VisionArcItemFitting *item = new VisionArcItemFitting(bEdit,length,color_enable,borderColor,selectedColor,brushColor);

        QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
        QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
        QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)),view,SLOT(slot_updatePath(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)));
        QObject::connect(item,SIGNAL(signalChanged(VisionItem*)),this,SIGNAL(signal_Changed(VisionItem*)));

        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setPointFs(sP,mP,fP);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }else{
        VisionArcItemFitting *item = new VisionArcItemFitting(bEdit,length,color_enable,borderColor,selectedColor,brushColor);

        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setPointFs(sP,mP,fP);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }
}

VisionCircleItemFitting *VisionGraph_::addCircleFitting(QRectF rf, bool bEdit, qreal length, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    if(!checkoutItem())
        return NULL;

    if(bEdit){
        VisionCircleItemFitting *item = new VisionCircleItemFitting(bEdit,length,color_enable,borderColor,selectedColor,brushColor);

        QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
        QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
        QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)),view,SLOT(slot_updatePath(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)));
        QObject::connect(item,SIGNAL(signalChanged(VisionItem*)),this,SIGNAL(signal_Changed(VisionItem*)));

        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setCircle(rf);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }else{
        VisionCircleItemFitting *item = new VisionCircleItemFitting(bEdit,length,color_enable,borderColor,selectedColor,brushColor);

        QObject::connect(item,&QObject::destroyed,[=](){
            m_lstItem.removeOne(item);
            m_curVisionItem = nullptr;

        });
        item->setCircle(rf);
        scene->addItem(item);
        m_curVisionItem = item;
        m_lstItem.push_back(item);
        emit signal_itemFinished(item);
        return item;
    }
}

VisionPolygonItemFitting *VisionGraph_::addPolygonFitting(QVector<QPointF> vecPointF, bool bClose, bool bEdit, qreal length, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    if(!checkoutItem())
        return NULL;

    VisionPolygonItemFitting *item = new VisionPolygonItemFitting(bClose,bEdit,length,color_enable,borderColor,selectedColor,brushColor);

    QObject::connect(item,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
    QObject::connect(item,SIGNAL(signal_painterInfo(ItemType,QPainterPath)),view,SLOT(slot_updateItem(ItemType,QPainterPath)));
    QObject::connect(item,SIGNAL(selectedChanged(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)),view,SLOT(slot_updatePath(bool,VisionItem*,ItemType,QRectF,QPointF,qreal)));
    QObject::connect(item,SIGNAL(signalChanged(VisionItem*)),this,SIGNAL(signal_Changed(VisionItem*)));

    QObject::connect(item,&QObject::destroyed,[=](){
        m_lstItem.removeOne(item);
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
    emit signal_itemFinished(item);
    return item;
}

VisionCoordinateItem *VisionGraph_::addCoordinate(QPointF p, qreal angle, qreal length, bool bEdit, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor)
{
    //绘制坐标系，目前的坐标系都是不可编辑的   调用clear是可以删除的控件
    VisionCoordinateItem* item = new VisionCoordinateItem(bEdit,color_enable,borderColor,selectedColor,brushColor);
    item->setPointF(p);
    item->setColor(borderColor);
    item->setAngle(angle);
    item->setCoordinateLength(length);
    scene->addItem(item);
    m_curVisionItem = item;
    m_lstItem.push_back(item);
    return item;
}

VisionTextItem *VisionGraph_::addText(VGRegion region, QString name)
{
    VisionTextItem* item = new VisionTextItem();
    item->setData(region,name);
    scene->addItem(item);
    return item;
}

VisionRegion *VisionGraph_::addRegion(VGRegion *region, QColor color)
{
    VisionRegion *item  = new VisionRegion();
    item->setRegionData(region,color);
    scene->addItem(item);
    m_lstItem.push_back(item);
    return item;
}

VisionRegion *VisionGraph_::addRegion(vector<VGRegionPair> vec_regionPair)
{
    VisionRegion *item  = new VisionRegion();
    item->setRegionData(vec_regionPair);
    scene->addItem(item);
    m_lstItem.push_back(item);
    return item;
}


int VisionGraph_::setBkImg(QImage image)
{
    if (image.isNull())
        return -1;
    if (m_bkPixmapItem == NULL)
    {
        m_bkPixmapItem = new QGraphicsPixmapItem();
        scene->addItem(m_bkPixmapItem);
    }
    m_bkPixmapItem->setPixmap(QPixmap::fromImage(image));
//    scene->addItem(m_bkPixmapItem);
//    this->adjustSize(m_bkPixmapItem->boundingRect().width(),m_bkPixmapItem->boundingRect().height());
    return 0;
}


void VisionGraph_::removeBkImg()
{
    if(m_bkPixmapItem == NULL){
//        m_bkPixmapItem = new QGraphicsPixmapItem();
//        scene->addItem(m_bkPixmapItem);
        return;
    }
    QPixmap pixmap;
    m_bkPixmapItem->setPixmap(pixmap);
}

void VisionGraph_::setToolButton_Direction(ToolButtonDirection direct){
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

        vBoxLayout->setSpacing(10);
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

        hBoxLayout->setSpacing(10);
        hBoxLayout->addWidget(label_size);
        hBoxLayout->addWidget(comboBox);

        tool_Widget->setMinimumHeight(45);
    }

    if(tool_infoWidget != NULL){
        tool_infoWidget->deleteLater();
        tool_infoWidget = NULL;
    }
    tool_infoWidget = new QToolBar;
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

    //由于布局改变了，故重新设置下
    //todo
//    slot_GraphTypeChanged(m_graphType);
}

void VisionGraph_::setViewInfo_Visible(bool bVisible)
{
    view->setViewInfo_Visible(bVisible);
}

QToolButton *VisionGraph_::getToolButton(ToolButtonType type)
{
    switch(type)
    {
    case ToolButtonType::ToolButtonSys_selected:
        return sys_selected_button;
    case ToolButtonType::ToolButtonSys_drag:
        return sys_drag_button;
    case ToolButtonType::ToolButtonSys_zoom:
        return sys_zoom_button;
    case ToolButtonType::ToolButtonSys_Fit:
        return sys_fit_button;
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
    case ToolButtonType::ToolButtonSys_circle:
        return sys_circle_button;
    case ToolButtonType::ToolButtonSys_Arc:
        return sys_arc_button;
    case ToolButtonType::ToolButtonSys_poly:
        return sys_poly_button;
    case ToolButtonType::ToolButtonSys_poly_elli:
        return sys_poly_elli_button;
    case ToolButtonType::ToolButtonSys_point:
        return sys_point_button;
    case ToolButtonType::ToolButtonSys_line:
        return sys_line_button;
    case ToolButtonType::ToolButtonSys_polyLine:
        return sys_polyLine_button;
    case ToolButtonType::ToolButtonSys_open_project:
        return sys_open_project_button;
    case ToolButtonType::ToolButtonSys_front:
        return sys_front_button;
    case ToolButtonType::ToolButtonSys_next:
        return sys_next_button;
    case ToolButtonType::ToolButtonSys_clear:
        return sys_clear_button;
    case ToolButtonType::ToolButtonSys_remove_item:
        return sys_remove_item_button;
    default:
        return NULL;
    }
}

bool VisionGraph_::removeToolButton(ToolButtonType type)
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
    case ToolButtonType::ToolButtonSys_Fit:
        toolButton = sys_fit_button;
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
        toolButton = sys_rect_button;
        break;
    case ToolButtonType::ToolButtonSys_ellipse:
        toolButton = sys_ellipse_button;
        break;
    case ToolButtonType::ToolButtonSys_circle:
        toolButton = sys_circle_button;
        break;
    case ToolButtonType::ToolButtonSys_Arc:
        toolButton = sys_arc_button;
        break;
    case ToolButtonType::ToolButtonSys_poly:
        toolButton = sys_poly_button;
        break;
    case ToolButtonType::ToolButtonSys_poly_elli:
        toolButton = sys_poly_elli_button;
        break;
    case ToolButtonType::ToolButtonSys_point:
        toolButton = sys_point_button;
        break;
    case ToolButtonType::ToolButtonSys_line:
        toolButton = sys_line_button;
        break;
    case ToolButtonType::ToolButtonSys_polyLine:
        toolButton = sys_polyLine_button;
        break;
    case ToolButtonType::ToolButtonSys_open_project:
        toolButton = sys_open_project_button;
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
    case ToolButtonType::ToolButtonSys_remove_item:
        toolButton = sys_remove_item_button;
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


void VisionGraph_::addToolButton(QToolButton *btn)
{
    btn->setToolButtonStyle(m_ToolStyle);
    btn->setIconSize(m_ToolIconSize);
    btn->setFixedSize(m_ToolBtnSize);
    m_lstAction.append(tool_Widget->insertWidget(m_insertAction,btn));
    m_lstToolBtn.append(btn);
}

void VisionGraph_::removeToolBarInfoWidget()
{
    tool_Widget->removeAction(infoWidget_Action);
}

void VisionGraph_::setViewRegion_Size(qreal w, qreal h)
{
    view->setViewRegion_Size(w,h);
    pSpinBox_w->setValue(w);
    pSpinBox_h->setValue(h);
}

qreal VisionGraph_::adjustSize(qreal w, qreal h)
{
    qreal q = view->adjustSize(w,h);
    pSpinBox_w->setValue(w);
    pSpinBox_h->setValue(h);
    comboBox->setEditText(QString::number((float)((int)(q*100))/100));
    return q;
}

void VisionGraph_::setViewRegion_Visible(bool bVisible)
{
    view->setViewRegion_Visible(bVisible);
}

void VisionGraph_::setViewRegion_Color(const QColor &color)
{
    view->setViewRegion_Color(color);
}

QImage VisionGraph_::getBkgImg()
{
    QImage image;
    if(m_bkPixmapItem != nullptr){
        image = m_bkPixmapItem->pixmap().toImage();
    }else{
        qDebug()<<"bkImg is null";
    }
    return image;
}

void VisionGraph_::saveBkgImg(QString path)
{
    //path==""调用fileDialog进行设置保存
    if(path == ""){
        slot_save_action();
    }else{

        if (m_bkPixmapItem == NULL) return;

        QString fileName = path;

        if(fileName == ""){
            qDebug()<<"save is failure";
            return;
        }

        qDebug()<<fileName;
        QPixmap map = m_bkPixmapItem->pixmap();
        if (!map.isNull())
        {
            QImage image(scene->width(), scene->height(),QImage::Format_ARGB32);
            QPainter painter(&image);
            painter.setRenderHint(QPainter::Antialiasing);
            scene->render(&painter);

            bool saveSuccess =  image.save(fileName,"BMP");
            Q_ASSERT(saveSuccess == true);
        }
    }
}

void VisionGraph_::removeItem(VisionItem *item)
{
    //item == nullptr 默认删除选中的
    if(item == nullptr){
        slot_removeItem_action();
    }else{
        //直接进行筛选，不考虑当前的
        if(m_lstItem.count() == 0)
            return;

        for(int i=0;i<m_lstItem.count();i++){
            if(m_lstItem[i] == item){
                m_lstItem.removeAt(i);
                break;
            }
        }
        scene->removeItem(item);

        if(item == m_curVisionItem){
            if(m_curVisionItem != nullptr){
//                m_curVisionItem->deleteLater();
                m_curVisionItem = nullptr;
            }
        }
    }
}

void VisionGraph_::setMousePaintSize(qreal qi)
{
    view->setPainterCursorR(qi/2);
    if(pSlider != nullptr){
        pSlider->setValue(qi);
    }
}

void VisionGraph_::setView_Zoom(qreal qZoom)
{
    view->zoom(qZoom);
    comboBox->setEditText(QString::number((float)((int)(qZoom*100))/100));
}

void VisionGraph_::setViewType(ViewType type)
{
    m_viewType = type;
}

QColor VisionGraph_::getPixel(qreal x, qreal y)
{
    return view->getPixel(x,y);
}

void VisionGraph_::setCoordinateVisible(bool bVisible)
{
    view->setCoordinateVisible(bVisible);
}

void VisionGraph_::slot_selected_action()
{
    view->setItemType(ItemType::No);
    m_itemType = ItemType::No;
//    label_Operation->setText(QStringLiteral("无状态"));
}

void VisionGraph_::slot_drag_action()
{
    view->setItemType(ItemType::Drag);
    m_itemType = ItemType::Drag;
//    label_Operation->setText(QStringLiteral("通过鼠标的拖动，拖动视图区域"));
}

void VisionGraph_::slot_zoom_action()
{
    view->viewRegion_OriginPos();
    //    label_Operation->setText(QStringLiteral("通过鼠标的滚轮，缩放视图区域"));
}

void VisionGraph_::slot_fit_action()
{
//    qDebug()<<"111111111111::"<<m_bkPixmapItem->boundingRect().width(),m_bkPixmapItem->boundingRect().height();
    if(!m_bkPixmapItem->pixmap().isNull()){
        this->adjustSize(m_bkPixmapItem->boundingRect().width(),m_bkPixmapItem->boundingRect().height());
    }else{
        qDebug()<<"m_bkPixmapItem is NULL";
        this->adjustSize(sceneWidget->width(),sceneWidget->height());
    }
//    qDebug()<<"222222222222"<<m_bkPixmapItem->boundingRect().width(),m_bkPixmapItem->boundingRect().height();
}

void VisionGraph_::slot_mousePainter_action()
{
    view->setItemType(ItemType::Paint_Point);
    m_itemType = ItemType::Paint_Point;
//    label_Operation->setText(QStringLiteral("点击绘制任意图形"));
}

void VisionGraph_::slot_mouseClear_action()
{
    view->setItemType(ItemType::Paint_NoPoint);
    m_itemType = ItemType::Paint_NoPoint;
//    label_Operation->setText(QStringLiteral("点击绘制任意图形"));
}

void VisionGraph_::slot_save_action()
{

    if (m_bkPixmapItem == NULL) return;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"/",tr("Images (*.png *.bmp *.jpg)"));
    if(fileName == ""){
        qDebug()<<"save is failure";
        return;
    }

    qDebug()<<fileName;
    QPixmap map = m_bkPixmapItem->pixmap();
    if (!map.isNull())
    {
        QImage image(scene->width(), scene->height(),QImage::Format_ARGB32);
        QPainter painter(&image);
        painter.setRenderHint(QPainter::Antialiasing);
        scene->render(&painter);

        bool saveSuccess =  image.save(fileName,"BMP");
        Q_ASSERT(saveSuccess == true);
    }
}

void VisionGraph_::slot_rect_action()
{
    view->setItemType(ItemType::Paint_Rect);
    m_itemType = ItemType::Paint_Rect;
//    label_Operation->setText(QStringLiteral("拖动到开始创建一个新区域 Rectangle"));

}

void VisionGraph_::slot_ellipse_action()
{
    view->setItemType(ItemType::Paint_EllipseItem);
    m_itemType = ItemType::Paint_EllipseItem;
//    label_Operation->setText(QStringLiteral("拖动到开始创建一个新区域 Ellipse"));
}

void VisionGraph_::slot_circle_action()
{
    view->setItemType(ItemType::Paint_CirCle);
    m_itemType = ItemType::Paint_CirCle;
}

void VisionGraph_::slot_arc_action()
{
    view->setItemType(ItemType::Paint_Arc);
    m_itemType = ItemType::Paint_Arc;
//    label_Operation->setText(QStringLiteral("拖动到开始创建一个新区域 Ellipse"));

}

void VisionGraph_::slot_poly_action()
{
    view->setItemType(ItemType::Paint_Poly);
    m_itemType = ItemType::Paint_Poly;
//    label_Operation->setText(QStringLiteral("拖动到开始创建一个新区域 path"));

}

void VisionGraph_::slot_poly_elli_action()
{
    view->setItemType(ItemType::Paint_Region);
    m_itemType = ItemType::Paint_Region;
//    label_Operation->setText(QStringLiteral("点击，创建任意的多边形"));
}

void VisionGraph_::slot_point_action()
{
    view->setItemType(ItemType::Paint_CrossPoint);
    m_itemType = ItemType::Paint_CrossPoint;
//    label_Operation->setText(QStringLiteral("点击，创建一个点"));
}

void VisionGraph_::slot_line_action()
{
    view->setItemType(ItemType::Paint_Line);
    m_itemType = ItemType::Paint_Line;
//    label_Operation->setText(QStringLiteral("点击，创建一个线段"));
}

void VisionGraph_::slot_polyLine_action()
{
    view->setItemType(ItemType::Paint_polyLine);
    m_itemType = ItemType::Paint_polyLine;
//    label_Operation->setText(QStringLiteral("点击，创建折线段"));
}

void VisionGraph_::slot_open_project()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/",tr("Images (*.png *.bmp *.jpg)"));

    qDebug()<<fileName;
    if(fileName != ""){
        m_bkPixmapItem->setPixmap(QPixmap(fileName));
        this->adjustSize(m_bkPixmapItem->boundingRect().width(),m_bkPixmapItem->boundingRect().height());
    }
}

void VisionGraph_::slot_front_action()
{
    view->back_region();
}

void VisionGraph_::slot_next_action()
{
    view->front_region();
}

void VisionGraph_::slot_clear_action()
{
    //清除当前的item
    view->clearPainter();

    if(m_curVisionItem != nullptr){
        m_curVisionItem->hide();
//        m_curVisionItem->deleteLater();
        m_curVisionItem = nullptr;
    }

    if(m_lstItem.count() > 0){
        for(int i=0;i<m_lstItem.count();i++){
            if(m_lstItem[i] != nullptr){
                scene->removeItem(m_lstItem[i]);
                m_lstItem[i]->deleteLater();
            }
            m_lstItem[i] = nullptr;
        }
        m_lstItem.clear();
    }

    //清除当前的item

//    scene->clear();
    //scene的部分item是不可以clear的，只需要clear掉绘制的item即可
    qDebug()<<scene->items().count();
}

void VisionGraph_::slot_removeItem_action()
{
    if(m_curVisionItem == nullptr)
        return;

    //直接进行筛选，不考虑当前的
    if(m_lstItem.count() == 0){
        m_curVisionItem = nullptr;
        return;
    }

    for(int i=0;i<m_lstItem.count();i++){
        if(m_lstItem[i] == m_curVisionItem){
            m_lstItem[i]->deleteLater();
            m_lstItem.removeAt(i);
            break;
        }
    }
    scene->removeItem(m_curVisionItem);  //不会delete
    //m_curVisionItem只是个指针，不需要delete
    //m_curVisionItem中的数据在m_lstItem中，前面已经释放
    m_curVisionItem = nullptr;
}

void VisionGraph_::slot_addItem(ItemType type, QRectF rf)
{
    if(m_graphType == GraphType::graphChain){
        //绘制链类型
        QList<QPointF> lstP;
        lstP.clear();
        if(type == ItemType::Paint_Rect){
            lstP.append({rf.topLeft(),rf.topRight(),rf.bottomRight(),rf.bottomLeft()});
            addChain(lstP,true,true,false,borderColor_Rect,selectedColor_Rect,brushColor_Rect);
        }else if(type == ItemType::Paint_EllipseItem || type == ItemType::Paint_CirCle){
            QPainterPath path;
            path.addEllipse(rf);
            lstP = path.toFillPolygon().toList();
            addChain(lstP,true,true,false,borderColor_Ellipse,selectedColor_Ellipse,brushColor_Ellipse);
        }
    }else if(m_graphType == GraphType::graphItem_Fitting){
        if(type == ItemType::Paint_CirCle){
            addCircleFitting(rf,true,0,false,borderColor_Circle,selectedColor_Circle,brushColor_Circle);
        }
    }else{
        if(type == ItemType::Paint_Rect){
            addRect(rf,0,true,true,false,borderColor_Rect,selectedColor_Rect,brushColor_Rect);
        }else if(type == ItemType::Paint_EllipseItem){
            addEllipse(rf,0,true,true,false,borderColor_Ellipse,selectedColor_Ellipse,brushColor_Ellipse);
        }else if(type == ItemType::Paint_CirCle){
            addCircle(rf,true,false,borderColor_Circle,selectedColor_Circle,brushColor_Circle);
        }
    }
}

void VisionGraph_::slot_addPoly(QVector<QPointF> vecPointF,ItemType type)
{
    if(m_graphType == GraphType::graphChain){
        if(type == ItemType::Paint_Poly){
            addChain(vecPointF.toList(),true,true,false,borderColor_Poly,selectedColor_Poly,brushColor_Poly);
        }else if(type == ItemType::Paint_polyLine){
            addChain(vecPointF.toList(),false,true,false,borderColor_PolyLine,selectedColor_PolyLine,brushColor_PolyLine);
        }else if(type == ItemType::Paint_Arc){
            //todo
            addArc(vecPointF[0],vecPointF[2],vecPointF[1],true,false,borderColor_Arc,selectedColor_Arc,brushColor_Arc);
        }
    }else if(m_graphType == GraphType::graphItem_Fitting){
        if(type == ItemType::Paint_Poly){
            addPolygonFitting(vecPointF,true,true,0,false,borderColor_Poly,selectedColor_Poly,brushColor_Poly);
        }else if(type == ItemType::Paint_polyLine){
            addPolygonFitting(vecPointF,false,true,0,false,borderColor_PolyLine,selectedColor_PolyLine,brushColor_PolyLine);
        }else if(type == ItemType::Paint_Arc){
            addArcFitting(vecPointF[0],vecPointF[2],vecPointF[1],true,0,false,borderColor_Arc,selectedColor_Arc,brushColor_Arc);
        }
    }else{
        if(type == ItemType::Paint_Poly){
            addPolygon(vecPointF,true,true,false,borderColor_Poly,selectedColor_Poly,brushColor_Poly);
        }else if(type == ItemType::Paint_polyLine){
            addPolygon(vecPointF,false,true,false,borderColor_PolyLine,selectedColor_PolyLine,brushColor_PolyLine);
        }else if(type == ItemType::Paint_Arc){
            addArc(vecPointF[0],vecPointF[2],vecPointF[1],true,false,borderColor_Arc,selectedColor_Arc,brushColor_Arc);
        }
    }
}

void VisionGraph_::slot_addPoint(QPointF pointF)
{
    addPoint(pointF,false,5,false,borderColor_Point,selectedColor_Point,brushColor_Point);
}

void VisionGraph_::slot_addLine(QLine line)
{
    if(m_graphType == GraphType::graphChain){
        addChain({line.p1(),line.p2()},false,true,false,borderColor_Line,selectedColor_Line,brushColor_Line);
    }else if(m_graphType == GraphType::graphItem_Fitting){
        addLineFitting(line,true,0,false,borderColor_Line,selectedColor_Line,brushColor_Line);
    }else{
        addLine(line,true,false,borderColor_Line,selectedColor_Line,brushColor_Line);
    }
}

void VisionGraph_::slot_mouseMove(QPointF pointF)
{
    m_mousePixmap->hide();
}

VisionRegion *itemRegion = NULL;
void VisionGraph_::slot_addRegion()
{
    this->clearPainter();
    XVRegion *xvRegion = view->getRegion();
    if(xvRegion->arrayPointRun.size() <= 0){
        return;
    }
    VGRegion *vgRegion = new VGRegion;

    vgRegion->frameHeight = xvRegion->frameHeight;
    vgRegion->frameWidth = xvRegion->frameWidth;
    vgRegion->optional = (VGOptionalType)(int)xvRegion->optional;


    for(int i=0;i<xvRegion->arrayPointRun.size();i++){
        VGPointRun pointRun;
        pointRun.length = xvRegion->arrayPointRun.at(i).length;
        pointRun.x = xvRegion->arrayPointRun.at(i).x;
        pointRun.y = xvRegion->arrayPointRun.at(i).y;
        vgRegion->arrayPointRun.push_back(pointRun);
    }
    if(itemRegion != NULL){
        delete itemRegion;
        itemRegion = NULL;
    }
    itemRegion  = new VisionRegion();
    itemRegion->setRegionData(vgRegion);
    scene->addItem(itemRegion);
//    m_lstItem.push_back(itemRegion);
    delete vgRegion;
//    delete xvRegion;
}

void VisionGraph_::slot_Press(VisionItem *item, bool bSelected,bool bIn,qreal x,qreal y)
{

    //修改，该函数的触发，改成有基类VisionItem进行触发，限制在点击item的时候触发

    //修改哪些item的zValue的值，需要根据点击的pos来定位在该pos的item有哪些

    //change zValue

    //点击item，如果该item是被选中的，则直接改为未选中，同时判断其底部是否有其他的item
    //如果有，则将该item的zValue值设为5，同时将该item的状态设置为选中状态

    //需要对基类添加的函数，设置选中和未选中的接口，获取选中状态的接口，获取坐标是否在item的有效区域内

    QList<VisionItem*> lstClickedItem;
    lstClickedItem.clear();
    for(int i=0;i<m_lstItem.count();i++){
        //点击了某一个item的无效区域，该item的z值是0，显示是in area，
        //clicked some item's uneffect area, and this item's z value is 0, this if think it is in area
        //but this item’s mousePressEvent() will think the click event is uneffect,and no deal with

        //此处判断修改，改为传输坐标给item，返回值为该坐标是否在该item内部---   true-in  false-out
        if(m_lstItem[i]->getPosInArea(x,y)){
//            qDebug()<<"in";
            lstClickedItem.push_back(m_lstItem[i]);
        }else{
//            qDebug()<<"out";
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
}

void VisionGraph_::slot_wheel(qreal delta)
{
    m_bWheel = true;
    m_zoom = delta;
    comboBox->setCurrentText(QString::number((float)((int)(m_zoom*100))/100));
//    g_scale = m_zoom;
}

void VisionGraph_::slot_SizeChanged(QString currentSize)
{
    if(m_bWheel){
        m_bWheel = false;
        return ;
    }
    QString str = currentSize;
    bool ok;
    float scale = str.toFloat(&ok);
    if(ok){
        m_zoom = scale;
        view->zoom(scale);
    }
//    g_scale = m_zoom;
//    qDebug()<<"textchange1111"<<g_scale;
}

void VisionGraph_::slot_SizeChanged(qreal w, qreal h)
{
    qDebug()<<"sceneWidget size is changed"<<w<<h;
    view->resize(sceneWidget->width(),sceneWidget->height());
    view->slotUpdateViewInfo_Pos();
    slot_fit_action();
}

void VisionGraph_::slot_valueChanged(int qR)
{
    m_mousePixmap->show();
    m_mousePixmap->setPixmap(QPixmap(iconPath+"cursor-size_Circle.png").scaled(qR,qR,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    qreal qx = view->sceneRect().x()+view->sceneRect().width()/2;
    qreal qy = view->sceneRect().y()+view->sceneRect().height()/2;
    m_mousePixmap->setPos(qx-m_mousePixmap->boundingRect().width()/2,qy-m_mousePixmap->boundingRect().height()/2);
    view->setPainterCursorR((qreal)qR/2);
}

void VisionGraph_::slot_SceneMouseMove(qreal x, qreal y)
{
    m_mousePixmap->hide();
}

void VisionGraph_::slot_actionTriggered(QAction *action)
{
    //region版本，发现存在item，在进行其他绘制操作的时候，会将存在的item自动转换成region
    if(action->text() == "rectangle" || action->text() == "ellipse" || action->text() == "poly" ||
            action->text() == "region" || action->text() == "mousePainter" || action->text() == "mouseClear"){

        if(m_lstItem.count() == 0)
            return;

        for(int i=0;i<m_lstItem.count();i++){
            if(m_lstItem[i] == m_curVisionItem){
                m_lstItem[i]->deleteLater();
                m_lstItem.removeAt(i);
                break;
            }
        }

        if(m_curVisionItem != nullptr){
            m_curVisionItem->setEdit(false);
            m_curVisionItem->setSelected(false);
            m_curVisionItem->scene()->update();
        }
    }
}

void VisionGraph_::slot_SpinBox_ViewRegionSize(int w)
{
    view->setViewRegion_Size(pSpinBox_w->value(),pSpinBox_h->value());
}

void VisionGraph_::slot_GraphTypeChanged(GraphType type)
{
    switch (type) {
    case GraphType::graphRegion:
        init_graphRegion();
        break;
    case GraphType::graphItem_self:
        init_graphItem_self();
        break;
    case GraphType::graphItem_unSelf:
        init_graphItem_unSelf();
        break;
    case GraphType::graphChain:
        init_graphChain();
        break;
    case GraphType::graphItem_Fitting:
        init_graphFitting();
        break;
    case GraphType::graph_Info:
        init_graph_info();
        break;
    case GraphType::graph_Path:
        init_graph_Item(graph_Path);
        break;
    case GraphType::graph_Location:
        init_graph_Item(graph_Location);
        break;
    case GraphType::graph_Rectangle:
        init_graph_Item(graph_Rectangle);
        break;
    case GraphType::graph_Arc:
        init_graph_Item(graph_Arc);
        break;
    case GraphType::graph_Circle:
        init_graph_Item(graph_Circle);
        break;
    default:
        break;
    }


    if(type == GraphType::graph_Info){
        setItemType(ItemType::Drag);
    }else{
        setItemType(ItemType::No);
    }
}

void VisionGraph_::slotItemFinished(VisionItem *item)
{
    item->setZValue(10);
}

void VisionGraph_::init_graph_info()
{
    m_lstAction.clear();
    tool_Widget->clear();
    tool_Widget->hide();
}

void VisionGraph_::init_graphRegion()
{
    m_lstAction.clear();
    tool_Widget->clear();
    tool_Widget->show();

//    m_lstAction.append(tool_Widget->addWidget(sys_open_project_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_save_button));
    m_lstAction.append(tool_Widget->addWidget(sys_front_button));
    m_lstAction.append(tool_Widget->addWidget(sys_next_button));
    m_lstAction.append(tool_Widget->addWidget(sys_clear_button));
    tool_Widget->addSeparator();

    m_lstAction.append(tool_Widget->addWidget(sys_selected_button));
    m_lstAction.append(tool_Widget->addWidget(sys_drag_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_zoom_button));
    m_lstAction.append(tool_Widget->addWidget(sys_fit_button));
    m_insertAction = tool_Widget->addSeparator();

    m_lstAction.append(tool_Widget->addWidget(sys_mouseClear_button));
    m_lstAction.append(tool_Widget->addWidget(sys_mousePainter_button));
    tool_Widget->addSeparator();

    m_lstAction.append(tool_Widget->addWidget(sys_rect_button));
    m_lstAction.append(tool_Widget->addWidget(sys_ellipse_button));
    m_lstAction.append(tool_Widget->addWidget(sys_circle_button));
    m_lstAction.append(tool_Widget->addWidget(sys_poly_button));
    m_lstAction.append(tool_Widget->addWidget(sys_poly_elli_button));
    m_insertAction = tool_Widget->addSeparator();

    tool_Widget->addWidget(label_mouseSizeText);
    tool_Widget->addWidget(label_slider);
    tool_Widget->addWidget(pSpinBox);
    tool_Widget->addSeparator();

    infoWidget_Action = tool_Widget->addWidget(tool_infoWidget);
}

void VisionGraph_::init_graphItem_self()
{
    m_lstAction.clear();
    tool_Widget->clear();
    tool_Widget->show();

//    m_lstAction.append(tool_Widget->addWidget(sys_open_project_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_save_button));
    m_lstAction.append(tool_Widget->addWidget(sys_clear_button));
    tool_Widget->addSeparator();

    m_lstAction.append(tool_Widget->addWidget(sys_selected_button));
    m_lstAction.append(tool_Widget->addWidget(sys_drag_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_zoom_button));
    m_lstAction.append(tool_Widget->addWidget(sys_fit_button));
    m_insertAction = tool_Widget->addSeparator();

    infoWidget_Action = tool_Widget->addWidget(tool_infoWidget);
}

void VisionGraph_::init_graphItem_unSelf()
{
    m_lstAction.clear();
    tool_Widget->clear();
    tool_Widget->show();

//    m_lstAction.append(tool_Widget->addWidget(sys_open_project_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_save_button));
    m_lstAction.append(tool_Widget->addWidget(sys_clear_button));
    m_lstAction.append(tool_Widget->addWidget(sys_remove_item_button));
    tool_Widget->addSeparator();

    m_lstAction.append(tool_Widget->addWidget(sys_selected_button));
    m_lstAction.append(tool_Widget->addWidget(sys_drag_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_zoom_button));
    m_lstAction.append(tool_Widget->addWidget(sys_fit_button));
    m_insertAction = tool_Widget->addSeparator();

    m_lstAction.append(tool_Widget->addWidget(sys_rect_button));
    m_lstAction.append(tool_Widget->addWidget(sys_ellipse_button));
    m_lstAction.append(tool_Widget->addWidget(sys_circle_button));
    m_lstAction.append(tool_Widget->addWidget(sys_arc_button));
    m_lstAction.append(tool_Widget->addWidget(sys_poly_button));
    m_lstAction.append(tool_Widget->addWidget(sys_polyLine_button));
    m_lstAction.append(tool_Widget->addWidget(sys_point_button));
    m_lstAction.append(tool_Widget->addWidget(sys_line_button));
    m_insertAction = tool_Widget->addSeparator();

    infoWidget_Action = tool_Widget->addWidget(tool_infoWidget);
}

void VisionGraph_::init_graphChain()
{
    m_lstAction.clear();
    tool_Widget->clear();
    tool_Widget->show();

//    m_lstAction.append(tool_Widget->addWidget(sys_open_project_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_save_button));
    m_lstAction.append(tool_Widget->addWidget(sys_clear_button));
    m_lstAction.append(tool_Widget->addWidget(sys_remove_item_button));
    tool_Widget->addSeparator();

    m_lstAction.append(tool_Widget->addWidget(sys_selected_button));
    m_lstAction.append(tool_Widget->addWidget(sys_drag_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_zoom_button));
    m_lstAction.append(tool_Widget->addWidget(sys_fit_button));
    m_insertAction = tool_Widget->addSeparator();

    m_lstAction.append(tool_Widget->addWidget(sys_rect_button));
    m_lstAction.append(tool_Widget->addWidget(sys_ellipse_button));
    m_lstAction.append(tool_Widget->addWidget(sys_circle_button));
    m_lstAction.append(tool_Widget->addWidget(sys_poly_button));
    m_lstAction.append(tool_Widget->addWidget(sys_polyLine_button));
    m_insertAction = tool_Widget->addSeparator();

    infoWidget_Action = tool_Widget->addWidget(tool_infoWidget);
}

void VisionGraph_::init_graphFitting()
{
    m_lstAction.clear();
    tool_Widget->clear();
    tool_Widget->show();

//    m_lstAction.append(tool_Widget->addWidget(sys_open_project_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_save_button));
    m_lstAction.append(tool_Widget->addWidget(sys_clear_button));
    m_lstAction.append(tool_Widget->addWidget(sys_remove_item_button));
    tool_Widget->addSeparator();

    m_lstAction.append(tool_Widget->addWidget(sys_selected_button));
    m_lstAction.append(tool_Widget->addWidget(sys_drag_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_zoom_button));
    m_lstAction.append(tool_Widget->addWidget(sys_fit_button));
    m_insertAction = tool_Widget->addSeparator();

    m_lstAction.append(tool_Widget->addWidget(sys_circle_button));
    m_lstAction.append(tool_Widget->addWidget(sys_arc_button));
    m_lstAction.append(tool_Widget->addWidget(sys_poly_button));
    m_lstAction.append(tool_Widget->addWidget(sys_polyLine_button));
    m_lstAction.append(tool_Widget->addWidget(sys_line_button));
    m_insertAction = tool_Widget->addSeparator();

    infoWidget_Action = tool_Widget->addWidget(tool_infoWidget);
}

void VisionGraph_::init_graph_Item(GraphType type)
{
    m_lstAction.clear();
    tool_Widget->clear();
    tool_Widget->show();

    m_lstAction.append(tool_Widget->addWidget(sys_clear_button));
    tool_Widget->addSeparator();

//    m_lstAction.append(tool_Widget->addWidget(sys_selected_button));
    m_lstAction.append(tool_Widget->addWidget(sys_drag_button));
//    m_lstAction.append(tool_Widget->addWidget(sys_zoom_button));
    m_lstAction.append(tool_Widget->addWidget(sys_fit_button));
    m_insertAction = tool_Widget->addSeparator();

    if(type == GraphType::graph_Path) {
        m_lstAction.append(tool_Widget->addWidget(sys_poly_button));
        m_lstAction.append(tool_Widget->addWidget(sys_polyLine_button));
    }else if(type == GraphType::graph_Location){
        m_lstAction.append(tool_Widget->addWidget(sys_open_project_button));
        m_lstAction.append(tool_Widget->addWidget(sys_point_button));
    }else if(type == GraphType::graph_Rectangle){
        m_lstAction.append(tool_Widget->addWidget(sys_rect_button));
    }else if(type == GraphType::graph_Arc){
        m_lstAction.append(tool_Widget->addWidget(sys_arc_button));
    }else if(type == GraphType::graph_Circle){
        m_lstAction.append(tool_Widget->addWidget(sys_circle_button));
    }
    m_insertAction = tool_Widget->addSeparator();

    infoWidget_Action = tool_Widget->addWidget(tool_infoWidget);
}

void VisionGraph_::paintEvent(QPaintEvent *event)
{
//    qDebug()<<view->matrix().m22()<<g_scale;
//    g_scale = view->matrix().m22();
    QWidget::paintEvent(event);
}

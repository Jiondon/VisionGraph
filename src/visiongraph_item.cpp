﻿#include "visiongraph_item.h"

#include <QDebug>
#include <QtMath>
#include <QFileDialog>
#include <QDateTime>
#include <QWidget>

VisionGraph_Item::VisionGraph_Item(ItemModel model, ToolButtonDirection toolButtonDirect, QWidget *parent) : QFrame(parent)
{
    mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);

    m_toolButtonDirection = toolButtonDirect;

    m_model = model;

    initScene();

    initLayout(toolButtonDirect);
}

void VisionGraph_Item::setSceneWidgetSize(QSize size)
{
    sceneWidget->resize(size);
}

void VisionGraph_Item::setSceneWidgetSize(qreal w, qreal h)
{
    sceneWidget->resize(w,h);
}


void VisionGraph_Item::initScene()
{
    sceneWidget = new VisionGraphWidget;
    sceneWidget->setMinimumSize(400,300);
    connect(sceneWidget,SIGNAL(signal_sizeChanged(qreal,qreal)),this,SLOT(slot_SizeChanged(qreal,qreal)));

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
//    view->setSceneRect(0,0,sceneWidget->width(),sceneWidget->height());

    m_bkPixmapItem = new QGraphicsPixmapItem();
    m_bkPixmapItem->setPixmap(QPixmap(":/bgk.bmp"));
    scene->addItem(m_bkPixmapItem);

    m_mousePixmap = new QGraphicsPixmapItem();
    m_mousePixmap->setPos(scene->width()/2-10,scene->height()/2-10);
    m_mousePixmap->setPixmap(QPixmap(iconPath+"cursor-size_Circle.png").scaled(10*2,10*2));
    scene->addItem(m_mousePixmap);
    m_mousePixmap->hide();


    //显示操作信息
//    label_Operation = new QLabel(this);
//    label_Operation->setText(QStringLiteral(""));
//    label_Operation->show();
//    label_Operation->setFixedWidth(400);

}


void VisionGraph_Item::initTool_operation()
{
    QAction* sys_open_project = new QAction(QIcon(iconPath+"open.png"),QStringLiteral("打开"));
    sys_open_project->setIconText(QStringLiteral("打开"));
    connect(sys_open_project,SIGNAL(triggered(bool)),this,SLOT(slot_open_project()));
    sys_open_project_button = new QToolButton;
    sys_open_project_button->setDefaultAction(sys_open_project);

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
    QAction* sys_remove_item = new QAction(QIcon(iconPath+"remove.png"),QStringLiteral("删除当前选中的item"));
    sys_remove_item->setIconText(QStringLiteral("删除"));
    connect(sys_remove_item,SIGNAL(triggered(bool)),this,SLOT(slot_removeItem_action()));
    sys_remove_item_button = new QToolButton;
    sys_remove_item_button->setDefaultAction(sys_remove_item);
    //调整鼠标的大小--针对鼠标擦除和鼠标绘制


    tool_Widget = new QToolBar;
    tool_Widget->setMinimumHeight(20);
    tool_Widget->setMovable(false);


    m_lstAction.append(tool_Widget->addWidget(sys_open_project_button));
    m_lstAction.append(tool_Widget->addWidget(sys_save_button));
    m_lstAction.append(tool_Widget->addWidget(sys_clear_button));
    m_lstAction.append(tool_Widget->addWidget(sys_remove_item_button));
    tool_Widget->addSeparator();

    m_lstToolBtn.append(sys_open_project_button);
    m_lstToolBtn.append(sys_save_button);
    m_lstToolBtn.append(sys_clear_button);
    m_lstToolBtn.append(sys_remove_item_button);


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

    QAction* sys_point_action = new QAction(QIcon(iconPath+"point.png"),QStringLiteral("绘制点"));
    sys_point_action->setIconText(QStringLiteral("点"));
    sys_point_action->setText("point");
    connect(sys_point_action,SIGNAL(triggered(bool)),this,SLOT(slot_point_action()));
    sys_point_button = new QToolButton;
    sys_point_button->setDefaultAction(sys_point_action);

    QAction* sys_line_action = new QAction(QIcon(iconPath+"line.png"),QStringLiteral("绘制直线"));
    sys_line_action->setIconText(QStringLiteral("直线"));
    sys_line_action->setText("line");
    connect(sys_line_action,SIGNAL(triggered(bool)),this,SLOT(slot_line_action()));
    sys_line_button = new QToolButton;
    sys_line_button->setDefaultAction(sys_line_action);

    QAction* sys_polyLine_action = new QAction(QIcon(iconPath+"polyline.png"),QStringLiteral("绘制折线"));
    sys_polyLine_action->setIconText(QStringLiteral("折线"));
    sys_polyLine_action->setText("polyLine");
    connect(sys_polyLine_action,SIGNAL(triggered(bool)),this,SLOT(slot_polyLine_action()));
    sys_polyLine_button = new QToolButton;
    sys_polyLine_button->setDefaultAction(sys_polyLine_action);

    //调整鼠标的大小--针对鼠标擦除和鼠标绘制



    m_lstAction.append(tool_Widget->addWidget(sys_selected_button));
    m_lstAction.append(tool_Widget->addWidget(sys_drag_button));
    m_lstAction.append(tool_Widget->addWidget(sys_zoom_button));
    m_insertAction = tool_Widget->addSeparator();


    m_lstToolBtn.append(sys_selected_button);
    m_lstToolBtn.append(sys_drag_button);
    m_lstToolBtn.append(sys_zoom_button);

    if(m_model == ItemModel::un_self){
        m_lstAction.append(tool_Widget->addWidget(sys_rect_button));
        m_lstAction.append(tool_Widget->addWidget(sys_ellipse_button));
        m_lstAction.append(tool_Widget->addWidget(sys_poly_button));
        m_lstAction.append(tool_Widget->addWidget(sys_point_button));
        m_lstAction.append(tool_Widget->addWidget(sys_line_button));
        m_insertAction = tool_Widget->addSeparator();


        m_lstToolBtn.append(sys_rect_button);
        m_lstToolBtn.append(sys_ellipse_button);
        m_lstToolBtn.append(sys_poly_button);
        m_lstToolBtn.append(sys_point_button);
        m_lstToolBtn.append(sys_line_button);

    }


    //显示区域的信息，view的大小，缩放比例，鼠标的信息
    infoWidget_Action = new QAction;
    infoWidget = new QWidget();


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

        vBoxLayout->addWidget(label_size);
        vBoxLayout->addWidget(comboBox);

        tool_Widget->setMinimumWidth(45);
    }else{
        QHBoxLayout* hBoxLayout = new QHBoxLayout;
        infoWidget->setLayout(hBoxLayout);

        hBoxLayout->addWidget(label_size);
        hBoxLayout->addWidget(comboBox);

        tool_Widget->setMinimumHeight(45);
    }
    infoWidget->show();

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

    for(int i=0;i<m_lstToolBtn.count();i++){
        m_lstToolBtn[i]->setToolButtonStyle(m_ToolStyle);
        m_lstToolBtn[i]->setIconSize(m_ToolIconSize);
        m_lstToolBtn[i]->setFixedSize(m_ToolBtnSize);
    }
}

void VisionGraph_Item::initToolBar()
{

}

void VisionGraph_Item::initLayout(ToolButtonDirection toolButtonDirect)
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



VisionRectItem *VisionGraph_Item::addRect(QRectF rf, bool bEdit)
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
        return item;
    }
    return NULL;
}

VisionEllipseItem *VisionGraph_Item::addEllipse(QRectF rf)
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
    return item;
}

VisionLineItem *VisionGraph_Item::addLine(QLine line)
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
    return item;
}

void VisionGraph_Item::addLines(QList<QLine> lstLine)
{

}

VisionPolygon *VisionGraph_Item::addPolygon(QVector<QPointF> vecPointF)
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
    return item;
}

VisionCrossPointItem* VisionGraph_Item::addPoint(QPointF pointF)
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
    return item;
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

void VisionGraph_Item::setToolButton_Direction(ToolButtonDirection direct){
    m_toolButtonDirection = direct;

    if(infoWidget != NULL){
        infoWidget->deleteLater();
        infoWidget = NULL;
    }
    infoWidget = new QWidget();

    tool_Widget->removeAction(infoWidget_Action);
    if(m_toolButtonDirection == ToolButtonDirection::leftDirection ||
            m_toolButtonDirection == ToolButtonDirection::rightDirection){

        QVBoxLayout* vBoxLayout = new QVBoxLayout;
        infoWidget->setLayout(vBoxLayout);

        vBoxLayout->addWidget(label_size);
        vBoxLayout->addWidget(comboBox);

        tool_Widget->setMinimumWidth(45);
    }else{

        QHBoxLayout* hBoxLayout = new QHBoxLayout;
        infoWidget->setLayout(hBoxLayout);

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

void VisionGraph_Item::setViewInfo_Visible(bool bVisible)
{
    view->setViewInfo_Visible(bVisible);
}

QToolButton *VisionGraph_Item::getToolButton(ToolButtonType type)
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

bool VisionGraph_Item::removeToolButton(ToolButtonType type)
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


void VisionGraph_Item::addToolButton(QToolButton *btn)
{
    btn->setToolButtonStyle(m_ToolStyle);
    btn->setIconSize(m_ToolIconSize);
    btn->setFixedSize(m_ToolBtnSize);
    m_lstAction.append(tool_Widget->insertWidget(m_insertAction,btn));
    m_lstToolBtn.append(btn);
}

void VisionGraph_Item::removeToolBarInfoWidget()
{
    tool_Widget->removeAction(infoWidget_Action);
}

void VisionGraph_Item::setViewRegion_Size(qreal w, qreal h)
{
    view->setViewRegion_Size(w,h);
}

void VisionGraph_Item::setViewRegion_Visible(bool bVisible)
{
    view->setViewRegion_Visible(bVisible);
}

void VisionGraph_Item::setViewRegion_Color(const QColor &color)
{
    view->setViewRegion_Color(color);
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

void VisionGraph_Item::slot_SizeChanged(qreal w, qreal h)
{
    qDebug()<<"sceneWidget size is changed"<<w<<h;
    view->resize(sceneWidget->width(),sceneWidget->height());
//    scene->setSceneRect(0,0,sceneWidget->width(),sceneWidget->height());
//    view->setScene(scene);
//    view->setSceneRect(0,0,sceneWidget->width(),sceneWidget->height());
    view->slotUpdateViewInfo_Pos();
}

﻿#include "visiongraph.h"
#include <QDebug>


VisionGraph::VisionGraph(GraphType type, QWidget *parent) : QWidget(parent)
{
    if(type == GraphType::graphRegion){
        m_graphWidget_Region = new VisionGraph_Region(this);
    }else if(type == GraphType::graphItem_self){
        m_graphWidget_Item = new VisionGraph_Item(ItemModel::self,this);
    }else if(type == GraphType::graphItem_unSelf){
        m_graphWidget_Item = new VisionGraph_Item(ItemModel::un_self,this);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
    m_type = type;
}

XVRegion VisionGraph::getRegion()
{
//    XVRegion xvRegin;
//    if(m_graphWidget_Region == nullptr)
//        xvRegin;
    return m_graphWidget_Region->getRegion();
}

void VisionGraph::setBkImg(QImage image)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setBkImg(image);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setBkImg(image);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setBkImg(image);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setToolButton_Painter(ToolButtonDirection direct)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setToolButton_Painter(direct);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setToolButton_Painter(direct);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setToolButton_Painter(direct);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::setToolButton_Operation(ToolButtonDirection direct)
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->setToolButton_Operation(direct);
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->setToolButton_Operation(direct);
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->setToolButton_Operation(direct);
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}

void VisionGraph::initLayout()
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->initLayout();
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->initLayout();
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->initLayout();
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}


void VisionGraph::show()
{
    if(m_type == GraphType::graphRegion){
        m_graphWidget_Region->show();
    }else if(m_type == GraphType::graphItem_self){
        m_graphWidget_Item->show();
    }else if(m_type == GraphType::graphItem_unSelf){
        m_graphWidget_Item->show();
    }else{
        qDebug()<<"VisionGraph is Error";
    }
}


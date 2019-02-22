#include "color.h"

QColor selectedColor = QColor(255,0,0);
QColor borderColor = QColor(0,0,0);
QColor brushColor = QColor(255,0,0,50);
QColor regionColor = QColor(255,0,0);  //暂时和brushColor合并

//暂时未用，
QColor viewMouseInfo_TextColor = QColor(255,255,255);
QColor viewMouseInfo_BackgroundColor = QColor(255,255,255);


QString iconPath = "./icon/";

QCursor viewCursor;

GraphType g_graphType = GraphType::graphItem_unSelf;

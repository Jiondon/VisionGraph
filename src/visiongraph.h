/****************************************************************************
** @brief       VisionGraph,绘制模块的widget
** @note        会生成一个widget来进行展示绘制模块，综合了region和item两种版本
** @author      xiaodongLi
** @date        create:2018-10-24
** @example
****************************************************************************/

#ifndef VISIONGRAPH_H
#define VISIONGRAPH_H

#include <QWidget>
#include "visiongraph_global.h"

#include "visiongraph_region.h"
#include "visiongraph_item.h"


/**
 * @brief       枚举VisionGraph的几种版本，
 * @note        graphRegion --- region版本（绘制item后，item失焦后，会通过算法生成区域，此过程不可逆）,需要用户交互（绘制需要用户进行操作）
 * @note        graphItem_self --- item版本（绘制item后，在整个过程中都是可调节的）,不要用户交互，主要是代码中直接调用放开的api来进行绘制
 * @note        graphItem_unSelf --- item版本，需要用户交互（绘制需要用户进行操作）
 */
enum GraphType{
    graphRegion,
    graphItem_self,
    graphItem_unSelf
};

class VISIONGRAPHSHARED_EXPORT VisionGraph : public QWidget
{
    Q_OBJECT
public:
    VisionGraph(GraphType type,QWidget *parent = 0);

    /**
     * @brief       获取当前绘制在view的区域  region版本
     * @param       XVRegion
     */
    XVRegion getRegion();

    /**
     * @brief       获取当前的VisionGraph，区分版本
     * @param       在需要使用VisionGraph的api的时候，通过该函数获取VisionGraph，进行调用
     */
    VisionGraph_Item* getVisionGraph_Item(){
        return m_graphWidget_Item;
    }

    /**
     * @brief       获取当前的VisionGraph，区分版本
     * @param       在需要使用VisionGraph的api的时候，通过该函数获取VisionGraph，进行调用
     */
    VisionGraph_Region* getVisionGraph_Region(){
        return m_graphWidget_Region;
    }

    /**
     * @brief       设置VisionGraph的背景，区分版本
     */
    void setBkImg(QImage image);


    /**
     * @brief       设置toolButton(painter)的布局
     * @param
     */
    void setToolButton_Painter(ToolButtonDirection direct);

    /**
     * @brief       设置toolButton(operation)的布局
     * @param
     */
    void setToolButton_Operation(ToolButtonDirection direct);

    /**
     * @brief      布局设置完成后，进行初始化
     * @param
     */
    void initLayout();

    void show();

protected:

private:
    GraphType m_type;

private:
    VisionGraph_Region *m_graphWidget_Region = nullptr;
    VisionGraph_Item *m_graphWidget_Item = nullptr;

};

#endif // VISIONGRAPH_H

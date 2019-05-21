/****************************************************************************
** @brief       自定义Region
** @note        区域控件，多条线组成一部分区域
** @author      xiaodongLi
** @date        create:2018-09-28
** @example
****************************************************************************/


#ifndef VISIONREGION_H
#define VISIONREGION_H

#include <QObject>
#include "../control/visionitem.h"
#include "../control/color.h"

class VisionRegion : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionRegion(VisionItem *parent = 0);

signals:

public slots:
};

#endif // VISIONREGION_H

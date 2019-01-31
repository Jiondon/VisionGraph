#ifndef VISIONCIRCLE_H
#define VISIONCIRCLE_H

#include <QObject>
#include "../control/visionitem.h"

class VisionCircle : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionCircle(VisionItem *parent = 0);

signals:

public slots:
};

#endif // VISIONCIRCLE_H

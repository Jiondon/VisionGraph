#ifndef VISIONLINEITEMFITTING_H
#define VISIONLINEITEMFITTING_H

#include <QObject>
#include "../control/visionitem.h"

class VisionLineItemFitting : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionLineItemFitting(bool bEdit = true,QColor color = QColor(255,0,0),VisionItem *parent = 0);


    void setLength(qreal r);

signals:

private:


public slots:
};

#endif // VISIONLINEITEMFITTING_H

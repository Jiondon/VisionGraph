#include "visionregion.h"

VisionRegion::VisionRegion(VisionItem *parent) : VisionItem(parent)
{

}

void VisionRegion::setRegionData(VGRegion region, QColor color)
{
    vector<VGPointRun> vec_point;
    vec_point = region.arrayPointRun;

    VGPointRun pointRun;
    QLineF lineF;
    m_vecLines.clear();
    for(int i=0;i<vec_point.size();i++){
        pointRun = vec_point.at(i);
        lineF.setPoints((QPointF(pointRun.x,pointRun.y)),
                        (QPointF(pointRun.x+pointRun.length,pointRun.y)));
        m_vecLines.append(lineF);
    }
    m_w = region.frameWidth;
    m_h = region.frameHeight;

    m_regionColor = color;
    this->update();
}

void VisionRegion::setRegionData(vector<VGRegionPair> vec_regionPair)
{
    m_vecRegionPair = vec_regionPair;
    this->update();
}

void VisionRegion::addRegionData(VGRegion region, QColor color)
{
    VGRegionPair pair;
    pair.color = color;
    pair.region = region;
    pair.value = m_vecRegionPair.size();
    m_vecRegionPair.push_back(pair);
    this->update();
}

void VisionRegion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setPen(QPen(m_regionColor,0));  //区域采用填充的颜色，原因自己想
    QVector<QLineF> vecLines;
    if(m_vecLines.size() > 0){
        for(int i=0;i<m_vecLines.size();i++){
    //        qDebug()<<this->mapFromScene(m_vecLines.at(i).p1());
            QLineF lineF = QLineF(this->mapFromScene(m_vecLines.at(i).p1()),this->mapFromScene(m_vecLines.at(i).p2()));
            vecLines.append(lineF);
            painter->drawLine(lineF);
        }
        painter->drawLines(vecLines);
    }


    vector<VGPointRun> vec_point;
    if(m_vecRegionPair.size() > 0){
        for(int i=0;i<m_vecRegionPair.size();i++){
            vec_point.clear();
            vec_point = m_vecRegionPair.at(i).region.arrayPointRun;
            painter->setPen(QPen(m_vecRegionPair.at(i).color,0));
            VGPointRun pointRun;
            for(int i=0;i<vec_point.size();i++){
                pointRun = vec_point.at(i);
                painter->drawLine(this->mapFromScene(QPointF(pointRun.x,pointRun.y).toPoint()),
                                 this->mapFromScene(QPointF(pointRun.x+pointRun.length,pointRun.y).toPoint()));
            }
        }
    }
}

QRectF VisionRegion::boundingRect() const
{
    return QRectF(0,0,m_w,m_h);
}


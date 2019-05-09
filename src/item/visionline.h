/****************************************************************************
** @brief       基于VisionItem类封装的直线--大数量直线的控件
** @note        该类主要是用于绘制大数量的直线的控件，只作为显示，主要是为了解决大数量直线单独绘制的耗时问题
** @author      xiaodongLi
** @date        create:2019-02-20
** @example     /as VisionPoint
****************************************************************************/

#ifndef VISIONLINE_H
#define VISIONLINE_H

#include <QObject>
#include <QPainter>
#include "../control/visionitem.h"

class VISIONGRAPHSHARED_EXPORT VisionLine : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionLine(bool color_enable = false,QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160),
                        VisionItem *parent = 0);

    void setLine(QLineF lineF);
    void setLines(QList<QLineF> lstLineF);


    /**
     * @brief       获取每个顶点
     * @param       point vec
     */
    QVector<QPointF> getPoints();

    bool getPosInArea(qreal x,qreal y);

    vector<VGLine2D> getData(){
        vector<VGLine2D> vec_vgLine;
        vec_vgLine.clear();
        if(m_style == SINGLE){
            VGLine2D line2D;
//            line2D.optional = VG_ENABLE;
            line2D.a = m_lineF.p2().y() - m_lineF.p1().y();
            line2D.b = m_lineF.p1().x() - m_lineF.p2().x();
            line2D.c = m_lineF.p2().x()*m_lineF.p1().y() - m_lineF.p1().x()*m_lineF.p2().y();
            vec_vgLine.push_back(line2D);
            return vec_vgLine;
        }else{
            for(int i=0;i<m_lstLineF.count();i++){
                VGLine2D line2D;
//                line2D.optional = VG_ENABLE;
                line2D.a = m_lstLineF.at(i).p2().y() - m_lstLineF.at(i).p1().y();
                line2D.b = m_lstLineF.at(i).p1().x() - m_lstLineF.at(i).p2().x();
                line2D.c = m_lstLineF.at(i).p2().x()*m_lstLineF.at(i).p1().y() - m_lstLineF.at(i).p1().x()*m_lstLineF.at(i).p2().y();
                vec_vgLine.push_back(line2D);
            }
            return vec_vgLine;
        }
    }

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    enum Style{
        SINGLE,
        MULTI
    };

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void signalChanged(VisionItem* item);

private:
    QLineF m_lineF;
    QList<QLineF> m_lstLineF;

    Style m_style = SINGLE;

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

public slots:
};

#endif // VISIONLINE_H

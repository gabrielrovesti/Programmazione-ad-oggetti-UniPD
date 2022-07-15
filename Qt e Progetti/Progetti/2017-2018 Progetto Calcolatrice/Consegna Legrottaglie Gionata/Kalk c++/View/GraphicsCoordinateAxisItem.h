#ifndef GRAPHICSCOORDINATEAXISITEM_H
#define GRAPHICSCOORDINATEAXISITEM_H

#include <QGraphicsItem>

class GraphicsCoordinateAxisItem : public QGraphicsItem
{
public:
    GraphicsCoordinateAxisItem();
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

private:
    QRectF m_boundingRect;
};

#endif // GRAPHICSCOORDINATEAXISITEM_H

#include "GraphicsCoordinateAxisItem.h"
#include <QPainter>

GraphicsCoordinateAxisItem::GraphicsCoordinateAxisItem()
{
    m_boundingRect.setRect(-5000, -5000, 10000, 10000);
}

QRectF GraphicsCoordinateAxisItem::boundingRect() const
{
    return m_boundingRect;
}

void GraphicsCoordinateAxisItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(Qt::red);
    painter->setPen(pen);
    painter->drawLine(m_boundingRect.x(), m_boundingRect.center().y(), m_boundingRect.right(), m_boundingRect.center().y());
    painter->drawLine(m_boundingRect.center().x(), m_boundingRect.top(), m_boundingRect.center().x(), m_boundingRect.bottom());

    //    Info assi (ogni 5pt)
        painter->setFont(QFont("Arial", 3));
        painter->drawText(QPoint(-3,-1), "0");
        painter->setFont(QFont("Arial", 2));
        for(int i=-5000; i<5000; i+=10) // X
        {
                if(i!=0){
                    painter->drawText(QPoint(-8,i+1.5), QString::number(i));
                    painter->drawLine(i,-1, i,1);
                    painter->drawText(QPoint(i-2,-2), QString::number(i));
                    painter->drawLine(-1,i, 1,i);
                }
        }
}

#ifndef GRAPHMODULE_H
#define GRAPHMODULE_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include "Model/Point.h"

class GraphModule : public QGraphicsView {
private:
Q_OBJECT
    QGraphicsScene *graphicsScene;
    QGraphicsRectItem *xRect;
    QGraphicsRectItem *yRect;
    QGraphicsPolygonItem *polygonItem;
    QList<QGraphicsEllipseItem *> pointItems;
    QList<QGraphicsLineItem *> lineItems;
    QList<QGraphicsSimpleTextItem *> textItems;
    double resize;

public:
    explicit GraphModule(QWidget * = nullptr, int = 300, int = 300);

    void setGraph(const QList<Point> &);

    void addLine(const Point &, const Point &, const QPen & = QPen(QColor("#85b7c4"), 1.5, Qt::PenStyle::SolidLine), double = 0.3);

    void addLine(const Point &, const Point &, const QString &, const QPen & = QPen(QColor("#85b7c4"), 1.5, Qt::PenStyle::SolidLine), double = 0.3);

    void addPoint(const Point &, char, const QPen & = QPen(QColor("#85b7c4"), 1.5, Qt::PenStyle::SolidLine), const QBrush & = QBrush(QColor("#85b7c4"), Qt::BrushStyle::SolidPattern));

    void addPoint(const Point &, char, const QString &, const QPen & = QPen(QColor("#85b7c4"), 1.5, Qt::PenStyle::SolidLine), const QBrush & = QBrush(QColor("#85b7c4"), Qt::BrushStyle::SolidPattern));

    void addChar(const Point &, char);

    void clearGraph();
};


#endif

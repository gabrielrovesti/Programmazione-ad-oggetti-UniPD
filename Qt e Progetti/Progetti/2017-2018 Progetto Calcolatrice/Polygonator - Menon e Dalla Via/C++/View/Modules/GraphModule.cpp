#include "GraphModule.h"

GraphModule::GraphModule(QWidget *parent, int width, int height) : QGraphicsView(parent) {
    setFixedSize(width, height);
    setBackgroundRole(QPalette::NoRole);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setStyleSheet("border: 0px;");

    graphicsScene = new QGraphicsScene(this);
    xRect = nullptr;
    yRect = nullptr;
    polygonItem = nullptr;
    resize = 1.0;

    setScene(graphicsScene);

    //Setting up x axis
    xRect = graphicsScene->addRect(-125, 0, 250, 0);
    xRect->setPen(QPen(QColor("#c1bec6"), 1.5, Qt::PenStyle::SolidLine));
    xRect->setBrush(Qt::BrushStyle::NoBrush);
    for(int i=-125; i<125; i+=5) {
        addLine(Point(i, -1.9), Point(i, 1.9), QPen(QColor("#c1bec6"), 1.05, Qt::PenStyle::SolidLine), 0.5);
        lineItems.takeLast(); //We don't want to remove the line on graph cleanup
    }

    //Setting up y axis
    yRect = graphicsScene->addRect(0, -125, 0, 250);
    yRect->setPen(QPen(QColor("#c1bec6"), 1.5, Qt::PenStyle::SolidLine));
    yRect->setBrush(Qt::BrushStyle::NoBrush);
    yRect->setTransform(QTransform::fromScale(1, -1));
    for(int i=-125; i<125; i+=5) {
        addLine(Point(-1.9, i), Point(1.9, i), QPen(QColor("#c1bec6"), 1.05, Qt::PenStyle::SolidLine), 0.5);
        lineItems.takeLast(); //We don't want to remove the line on graph cleanup
    }
}

void GraphModule::setGraph(const QList<Point> &points) {
    QVector<QPointF> pointVector;

    char letter = 'A';
    double max=-100;

    for(Point point : points) {
        if(fabs(point.getX()) > max) max = fabs(point.getX());
        if(fabs(point.getY()) > max) max = fabs(point.getY());
    }

    if (max > 0 && max <= 50) {
        resize = 100/max;
    }

    for(Point point : points) {
        pointVector.push_back(QPointF(point.getX()*resize, point.getY()*resize));

        addPoint(point, letter,
                 QString::fromStdString(string("") + letter + "(" + QString::number(point.getX(), 'f', 2).toStdString() + "," + QString::number(point.getY(), 'f', 2).toStdString() + ")")
        );

        letter++;
    }

    graphicsScene->setSceneRect(QRectF(-125, -125, graphicsScene->sceneRect().width(), graphicsScene->sceneRect().height()));

    polygonItem = graphicsScene->addPolygon(QPolygonF(pointVector));
    polygonItem->setPen(QPen(QColor("#85b7c4"), 3, Qt::PenStyle::SolidLine));
    polygonItem->setOpacity(0.5);
    polygonItem->setBrush(Qt::BrushStyle::NoBrush);
    polygonItem->setTransform(QTransform::fromScale(1, -1));
}

void GraphModule::addLine(const Point &a, const Point &b, const QPen &qPen, double opacity) {
    QGraphicsLineItem *lineItem = graphicsScene->addLine(a.getX()*resize, a.getY()*resize, b.getX()*resize, b.getY()*resize);

    lineItem->setPen(qPen);
    lineItem->setOpacity(opacity);
    lineItem->setTransform(QTransform::fromScale(1, -1));

    lineItems.push_back(lineItem);
}

void GraphModule::addLine(const Point &a, const Point &b, const QString &toolTip, const QPen &qPen, double opacity) {
    addLine(a, b, qPen, opacity);
    lineItems.last()->setToolTip(toolTip);
}

void GraphModule::addPoint(const Point &point, char letter, const QPen &pen, const QBrush &brush) {
    QGraphicsEllipseItem *pointItem = graphicsScene->addEllipse(point.getX()*resize-2.5, point.getY()*resize-2.5, 5, 5);

    pointItem->setPen(pen);
    pointItem->setBrush(brush);
    pointItem->setTransform(QTransform::fromScale(1, -1));

    pointItems.push_back(pointItem);

    addChar(point, letter);
}

void GraphModule::addPoint(const Point &point, char letter, const QString &toolTip, const QPen &pen, const QBrush &brush) {
    addPoint(point, letter, pen, brush);
    pointItems.last()->setToolTip(toolTip);
}

void GraphModule::addChar(const Point &point, char letter) {
    QGraphicsSimpleTextItem *textItem = graphicsScene->addSimpleText(QString::fromStdString(string("") + letter));

    textItem->setPos(point.getX()*resize+2, -point.getY()*resize-2);

    textItems.push_back(textItem);
}

void GraphModule::clearGraph() {
    if(polygonItem) {
        graphicsScene->removeItem(polygonItem);
        delete polygonItem;
        polygonItem = nullptr;

        while(!pointItems.isEmpty()) {
            QGraphicsEllipseItem *pointItem = pointItems.takeFirst();
            graphicsScene->removeItem(pointItem);
            delete pointItem;
        }

        while(!lineItems.isEmpty()) {
            QGraphicsLineItem *lineItem = lineItems.takeFirst();
            graphicsScene->removeItem(lineItem);
            delete lineItem;
        }

        while(!textItems.isEmpty()) {
            QGraphicsSimpleTextItem *textItem = textItems.takeFirst();
            graphicsScene->removeItem(textItem);
            delete textItem;
        }
    }
}

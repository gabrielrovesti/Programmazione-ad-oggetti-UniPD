#include "Rectangle.h"

Rectangle::Rectangle(const list<Point> &vertices) : Quadrilateral(vertices), Parallelogram(vertices) {}

bool Rectangle::canBeCreatedWith(const Polygon &polygon) {
    if (!Parallelogram::canBeCreatedWith(polygon)) return false;

    for (auto it = polygon.getVertices().begin(); it != polygon.getVertices().end(); it++) {
        Point p = it == polygon.getVertices().begin() ? *prev(polygon.getVertices().end()) : *prev(it);
        Point n = it == prev(polygon.getVertices().end()) ? *polygon.getVertices().begin() : *next(it);

        if (fabs(Line::getAngleDegrees(p, *it, n) - 90) > 0.0001) return false;
    }

    return true;
}

double Rectangle::getHeight() const {
    return Line::getDistance(*prev(getVertices().end()), *getVertices().begin());
}

double Rectangle::getPerimeter() const {
    return (getBase() + getHeight()) * 2;
}

string Rectangle::getName() const {
    return "Rectangle";
}

#include "Kite.h"

Kite::Kite(const list<Point> &vertices) : Quadrilateral(vertices) {}

bool Kite::canBeCreatedWith(const Polygon &polygon) {
    if (!Quadrilateral::canBeCreatedWith(polygon) || polygon.isConcave()) return false;

    int adjacent = 0;
    for (auto it = polygon.getVertices().begin(); it != polygon.getVertices().end(); it++) {
        Point p = it == polygon.getVertices().begin() ? *prev(polygon.getVertices().end()) : *prev(it);
        Point n = it == prev(polygon.getVertices().end()) ? *polygon.getVertices().begin() : *next(it);

        if (Line(p, *it) == Line(*it, n)) adjacent++;
    }
    return adjacent >= 2;
}

double Kite::getArea() const {
    list<Line> d = getDiagonals();
    return d.begin()->getDistance() * next(d.begin())->getDistance() / 2;
}

double Kite::getPerimeter() const {
    double a = Line::getDistance(*getVertices().begin(), *next(getVertices().begin()));
    double b = Line::getDistance(*getVertices().begin(), *prev(getVertices().end()));
    if (fabs(a - b) < 0.0001) b = Line::getDistance(*next(getVertices().begin()), *next(next(getVertices().begin())));
    return (a + b) * 2;
}

string Kite::getName() const {
    return "Kite";
}

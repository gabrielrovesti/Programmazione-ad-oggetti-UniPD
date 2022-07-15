#include "Parallelogram.h"

Parallelogram::Parallelogram(const list<Point> &vertices) : Quadrilateral(vertices) {}

bool Parallelogram::canBeCreatedWith(const Polygon &polygon) {
    if (!Quadrilateral::canBeCreatedWith(polygon) || polygon.isConcave()) return false;

    Point first = *polygon.getVertices().begin(),
            second = *next(polygon.getVertices().begin()),
            third = *next(next(polygon.getVertices().begin())),
            fourth = *prev(polygon.getVertices().end());

    return Line(first, second) == Line(third, fourth) && Line(second, third) == Line(fourth, first);
}

double Parallelogram::getHeight() const {
    if( (*getVertices().begin()).getY() >= (*next(next(getVertices().begin()))).getY() ) {
        return Line::getDistance(*next(getVertices().begin()), *next(next(getVertices().begin())),
                                 *getVertices().begin());
    }
    return Line::getDistance(*getVertices().begin(), *next(getVertices().begin()), *prev(getVertices().end()));
}

double Parallelogram::getArea() const {
    return getBase() * getHeight();
}

double Parallelogram::getPerimeter() const {
    double perimeter = getBase() + Line::getDistance(*prev(getVertices().end()), *getVertices().begin());
    return perimeter * 2;
}

string Parallelogram::getName() const {
    return "Parallelogram";
}
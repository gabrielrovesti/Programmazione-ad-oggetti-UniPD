#include "Triangle.h"

Triangle::Triangle(const list<Point> &vertices) : Polygon(vertices) {}

bool Triangle::canBeCreatedWith(const Polygon &polygon) {
    return polygon.getVertices().size() == 3;
}

double Triangle::getApothemConstant() const {
    return 0.289;
}

list<Line> Triangle::getDiagonals() const {
    throw Exception("A triangle does not have diagonals");
}

double Triangle::getHeight() const {
    if( (*getVertices().begin()).getY() >= (*next(next(getVertices().begin()))).getY() ) {
        return Line::getDistance(*next(getVertices().begin()), *next(next(getVertices().begin())), *getVertices().begin());
    }

    return Line::getDistance(*getVertices().begin(), *next(getVertices().begin()), *prev(getVertices().end()));
}

double Triangle::getArea() const {
    return getBase() * getHeight() / 2;
}

list<Line> Triangle::getMedians() const {
    list<Line> medians;

    for (Point vertex : getVertices()) {
        medians.push_back(getMedian(vertex));
    }

    return medians;
}

Line Triangle::getMedian(const Point &p) const {
    Point a = *getVertices().begin() == p ? *next(getVertices().begin()) : *getVertices().begin();
    Point b = *prev(getVertices().end()) == p ? *next(getVertices().begin()) : *prev(getVertices().end());

    return {Line::getMidPoint(a, b), p};
}

list<Line> Triangle::getBisectors() const {
    list<Line> bisectors;

    for (Point vertex : getVertices()) {
        bisectors.push_back(getBisector(vertex));
    }

    return bisectors;
}

Line Triangle::getBisector(const Point &p) const {
    Point a = *getVertices().begin() == p ? *next(getVertices().begin()) : *getVertices().begin();
    Point b = *prev(getVertices().end()) == p ? *next(getVertices().begin()) : *prev(getVertices().end());

    double ap = Line::getDistance(a, p);
    double bp = Line::getDistance(b, p);

    double x = (ap * b.getX() + bp * a.getX()) / (ap + bp);
    double y = (ap * b.getY() + bp * a.getY()) / (ap + bp);

    return {{x, y}, p};
}

string Triangle::getName() const {
    return "Triangle";
}
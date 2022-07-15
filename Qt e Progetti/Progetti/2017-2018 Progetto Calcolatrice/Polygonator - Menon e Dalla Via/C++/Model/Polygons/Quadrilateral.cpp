#include "Quadrilateral.h"

Quadrilateral::Quadrilateral(const list<Point> &vertices) : Polygon(vertices) {}

bool Quadrilateral::canBeCreatedWith(const Polygon &polygon) {
    return polygon.getVertices().size() == 4;
}

string Quadrilateral::getName() const {
    return "Quadrilateral";
}

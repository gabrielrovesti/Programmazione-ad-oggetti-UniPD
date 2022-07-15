#include "Rhombus.h"

Rhombus::Rhombus(const list<Point> &vertices) : Quadrilateral(vertices), Parallelogram(vertices), Kite(vertices) {}

bool Rhombus::canBeCreatedWith(const Polygon &polygon) {
    return Parallelogram::canBeCreatedWith(polygon) && Kite::canBeCreatedWith(polygon);
}

double Rhombus::getArea() const {
    return Kite::getArea();
}

double Rhombus::getPerimeter() const {
    return getBase() * 4;
}

string Rhombus::getName() const {
    return "Rhombus";
}

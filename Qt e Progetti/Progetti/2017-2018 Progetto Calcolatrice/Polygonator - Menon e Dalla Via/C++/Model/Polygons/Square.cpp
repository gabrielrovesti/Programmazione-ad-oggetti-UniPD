#include "Square.h"

Square::Square(const list<Point> &vertices) : Quadrilateral(vertices), Parallelogram(vertices), Rectangle(vertices),
                                              Rhombus(vertices) {}

bool Square::canBeCreatedWith(const Polygon &polygon) {
    return Rectangle::canBeCreatedWith(polygon) && Rhombus::canBeCreatedWith(polygon);
}

double Square::getApothemConstant() const {
    return 0.5;
}

double Square::getArea() const {
    return pow(getBase(), 2);
}

double Square::getPerimeter() const {
    return Rhombus::getPerimeter();
}

string Square::getName() const {
    return "Square";
}
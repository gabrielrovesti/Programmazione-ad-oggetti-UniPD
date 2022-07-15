#include "Pentagon.h"

Pentagon::Pentagon(const list<Point> &vertices) : Polygon(vertices) {}

bool Pentagon::canBeCreatedWith(const Polygon &polygon) {
    return polygon.getVertices().size() == 5;
}

double Pentagon::getApothemConstant() const {
    return isRegular() ? 0.688 : Polygon::getApothemConstant();
}

string Pentagon::getName() const {
    return "Pentagon";
}
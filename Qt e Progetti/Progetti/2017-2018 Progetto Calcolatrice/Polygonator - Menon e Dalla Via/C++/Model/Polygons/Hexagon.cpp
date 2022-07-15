#include "Hexagon.h"

Hexagon::Hexagon(const list<Point> &vertices) : Polygon(vertices) {}

bool Hexagon::canBeCreatedWith(const Polygon &polygon) {
    return polygon.getVertices().size() == 6;
}

double Hexagon::getApothemConstant() const {
    return isRegular() ? 0.866 : Polygon::getApothemConstant();
}

string Hexagon::getName() const {
    return "Hexagon";
}
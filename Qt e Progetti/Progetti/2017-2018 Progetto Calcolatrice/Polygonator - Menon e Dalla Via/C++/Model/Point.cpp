#include "Point.h"

Point::Point(double x, double y) : x(x), y(y) {}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

string Point::getEquation() const {
    char sx[10], sy[10];
    sprintf(sx, "%.2f", fabs(x));
    sprintf(sy, "%.2f", fabs(y));
    return string("y ") + (y>=0 ? "- " : "+ ") + sy + " = m(x " + (x>=0 ? "- " : "+ ") + sx + ")";
}

bool Point::operator==(const Point &p) const {
    return x == p.x && y == p.y;
}

bool Point::operator!=(const Point &p) const {
    return !(*this == p);
}

bool Point::operator<(const Point &p) const {
    return x < p.x || (x == p.x && y < p.y);
}

bool Point::operator>(const Point &p) const {
    return x > p.x || (x == p.x && y > p.y);
}

bool Point::operator<=(const Point &p) const {
    return *this == p || *this < p;
}

bool Point::operator>=(const Point &p) const {
    return *this == p || *this > p;
}

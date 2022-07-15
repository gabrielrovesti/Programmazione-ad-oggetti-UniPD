#include "Line.h"

Line::Line(const Point &a, const Point &b) : a(a), b(b) {
    if (a == b) {
        throw Exception("Cannot generate a line with two equal points");
    }
}

Point Line::getA() const {
    return a;
}

Point Line::getB() const {
    return b;
}

double Line::getXAt(double y) const {
    return ((y - a.getY()) / (b.getY() - a.getY()) * (b.getX() - a.getX())) + a.getX();
}

double Line::getYAt(double x) const {
    return ((x - a.getX()) / (b.getX() - a.getX()) * (b.getY() - a.getY())) + a.getY();
}

bool Line::belongs(const Point &p) const {
    return belongs(a, b, p);
}

bool Line::belongs(const Point &a, const Point &b, const Point &p) {
    return getDistance(a, b, p) == 0;
}

double Line::getDistance() const {
    return getDistance(a, b);
}

double Line::getDistance(const Point &a, const Point &b) {
    return sqrt(pow(b.getX() - a.getX(), 2) + pow(b.getY() - a.getY(), 2));
}

double Line::getDistance(const Point &p) const {
    return getDistance(a, b, p);
}

double Line::getDistance(const Point &a, const Point &b, const Point &p) {
    if (a.getX() == b.getX()) {
        return fabs(p.getX() - a.getX());
    }

    if (a.getY() == b.getY()) {
        return fabs(p.getY() - a.getY());
    }

    double m = getAngularCoefficient(a, b);
    double q = -m * a.getX() + a.getY();

    return fabs(p.getY() - m * p.getX() - q) / sqrt(1 + pow(m, 2));
}

Point Line::getMidPoint() const {
    return getMidPoint(a, b);
}

Point Line::getMidPoint(const Point &a, const Point &b) {
    return {(a.getX() + b.getX()) / 2, (a.getY() + b.getY()) / 2};
}

double Line::getAngularCoefficient() const {
    return getAngularCoefficient(a, b);
}

double Line::getAngularCoefficient(const Point &a, const Point &b) {
    if (a.getX() == b.getX()) {
        throw Exception("The line is parallel to the y axis");
    }

    return (b.getY() - a.getY()) / (b.getX() - a.getX());
}

string Line::getEquation() const {
    char s1[10], s2[10];

    if (a.getX() == b.getX()) {
        sprintf(s1, "%.2f", a.getX());
        return string("x = ") + s1;
    }

    if (a.getY() == b.getY()) {
        sprintf(s1, "%.2f", a.getY());
        return string("y = ") + s1;
    }

    double m = getAngularCoefficient();
    double q = -m * a.getX() + a.getY();

    sprintf(s1, "%.2f", m);
    sprintf(s2, "%.2f", q);

    return string("y = ") + s1 + "x" + (q >= 0 ? "+" : "") + s2;
}

double Line::getAngleDegrees(const Line &l) const {
    if (a != l.a && a != l.b && b != l.a && b != l.b) {
        throw Exception("No points in common between the two lines");
    }

    Point middle = a != l.a && a != l.b ? b : a;
    Point first = a != middle ? a : b;
    Point last = l.a != middle ? l.a : l.b;

    return getAngleDegrees(first, middle, last);
}

double Line::getAngleDegrees(const Point &first, const Point &middle, const Point &last) {
    return acos((pow(getDistance(first, middle), 2) + pow(getDistance(last, middle), 2) -
                 pow(getDistance(first, last), 2)) / (2 * getDistance(middle, first) * getDistance(middle, last))) *
           180 / M_PI;
}

bool Line::operator==(const Line &l) const {
    return fabs(getDistance() - l.getDistance()) < 0.0001;
}

bool Line::operator!=(const Line &l) const {
    return getDistance() != l.getDistance();
}

bool Line::operator<(const Line &l) const {
    return getDistance() < l.getDistance();
}

bool Line::operator<=(const Line &l) const {
    return getDistance() <= l.getDistance();
}

bool Line::operator>(const Line &l) const {
    return getDistance() > l.getDistance();
}

bool Line::operator>=(const Line &l) const {
    return getDistance() >= l.getDistance();
}

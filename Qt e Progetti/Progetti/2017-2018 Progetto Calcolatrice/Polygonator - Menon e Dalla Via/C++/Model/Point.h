#ifndef POINT_H
#define POINT_H

#include <string>
#include <cmath>
#include "Exception.h"

using std::string;
using std::to_string;

class Point {
private:
    double x, y;

public:
    Point(double, double);

    double getX() const;

    double getY() const;

    //Returns the point-slope equation of a straight line
    string getEquation() const;

    bool operator==(const Point &) const;

    bool operator!=(const Point &) const;

    bool operator<(const Point &) const;

    bool operator>(const Point &) const;

    bool operator<=(const Point &) const;

    bool operator>=(const Point &) const;
};


#endif

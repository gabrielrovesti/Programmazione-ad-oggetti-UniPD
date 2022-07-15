#ifndef LINE_H
#define LINE_H

#define _USE_MATH_DEFINES

#include <math.h>
#include "Point.h"

class Line {
private:
    const Point a, b;

public:
    Line(const Point &, const Point &);

    Point getA() const;

    Point getB() const;

    //Returns the corresponding X value of the line, given the Y value
    double getXAt(double) const;

    //Returns the corresponding Y value of the line, given the X value
    double getYAt(double) const;

    //Returns whether a Point is on the straight line or not
    bool belongs(const Point &) const;

    static bool belongs(const Point &, const Point &, const Point &);

    //Returns the distance between the points a and b
    double getDistance() const;

    static double getDistance(const Point &, const Point &);

    //Returns the length (in absolute value) of the projection of a point on the line
    double getDistance(const Point &) const;

    static double getDistance(const Point &, const Point &, const Point &);

    //Returns the mid point of the line
    Point getMidPoint() const;

    static Point getMidPoint(const Point &, const Point &);

    //Returns the angular coefficient of the line
    double getAngularCoefficient() const;

    static double getAngularCoefficient(const Point &, const Point &);

    //Returns the equation of the straight line
    string getEquation() const;

    //Returns the degrees of the angle formed by two intersecting lines
    double getAngleDegrees(const Line &) const;

    static double getAngleDegrees(const Point &, const Point &, const Point &);

    bool operator==(const Line &) const;

    bool operator!=(const Line &) const;

    bool operator<(const Line &) const;

    bool operator<=(const Line &) const;

    bool operator>(const Line &) const;

    bool operator>=(const Line &) const;
};


#endif

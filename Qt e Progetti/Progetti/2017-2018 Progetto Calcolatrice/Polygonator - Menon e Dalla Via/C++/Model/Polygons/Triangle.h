#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Polygon.h"

using Polygonator::Polygon;

class Triangle : public Polygon {
public:
    explicit Triangle(const list<Point> &);

    //Returns whether a generic polygon is a triangle or not
    static bool canBeCreatedWith(const Polygon &);

    //Returns the apothemConstant when the polygon is regular (ratio apothem/side)
    double getApothemConstant() const;

    //Returns the list of diagonals of the polygon
    list<Line> getDiagonals() const;

    //Returns the height of the calculated base of the triangle
    double getHeight() const;

    //Returns the area of a triangle
    double getArea() const;

    //Returns the list of all the medians of a triangle
    list<Line> getMedians() const;

    //Returns the median between the given point and the opposite line
    Line getMedian(const Point &) const;

    //Returns the list of all the bisectors of the triangle
    list<Line> getBisectors() const;

    //Returns the bisector of the given vertex
    Line getBisector(const Point &) const;

    //Returns the name of the polygon
    string getName() const;
};


#endif

#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

#include "Polygon.h"

using Polygonator::Polygon;

class Quadrilateral : public Polygon {
public:
    explicit Quadrilateral(const list<Point> &);

    //Returns whether a generic polygon is a quadrilateral or not
    static bool canBeCreatedWith(const Polygon &);

    //Returns the name of the polygon
    string getName() const;
};


#endif

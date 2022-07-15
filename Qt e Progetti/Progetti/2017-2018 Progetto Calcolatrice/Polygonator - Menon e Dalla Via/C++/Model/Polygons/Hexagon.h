#ifndef HEXAGON_H
#define HEXAGON_H

#include "Polygon.h"

using Polygonator::Polygon;

class Hexagon : public Polygon {
public:
    explicit Hexagon(const list<Point> &);

    //Returns whether a generic polygon is an hexagon or not
    static bool canBeCreatedWith(const Polygon &);

    //Returns the apothemConstant when the polygon is regular (ratio apothem/side)
    double getApothemConstant() const;

    //Returns the name of the polygon
    string getName() const;
};


#endif

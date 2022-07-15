#ifndef PENTAGON_H
#define PENTAGON_H

#include "Polygon.h"

using Polygonator::Polygon;

class Pentagon : public Polygon {
public:
    explicit Pentagon(const list<Point> &);

    //Returns whether a generic polygon is a pentagon or not
    static bool canBeCreatedWith(const Polygon &);

    //Returns the apothemConstant when the polygon is regular (ratio apothem/side)
    double getApothemConstant() const;

    //Returns the name of the polygon
    string getName() const;
};


#endif

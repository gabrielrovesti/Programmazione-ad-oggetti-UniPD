#ifndef POLYGONFACTORY_H
#define POLYGONFACTORY_H

#include <functional>
#include "Model/Polygons/Triangle.h"
#include "Model/Polygons/Square.h"
#include "Model/Polygons/Pentagon.h"
#include "Model/Polygons/Hexagon.h"

using Polygonator::Polygon;

class PolygonFactory {
private:
    //Checks, through the template, if the given polygon is compatible the figure T, and returns it
    template<class T>
    static T *checkPolygon(const Polygon &);

public:
    //Returns a polygon (or a type compatible with it) made upon the given list of points
    static Polygon *makePolygon(const list<Point> &);

    virtual ~PolygonFactory() = 0;
};


#endif
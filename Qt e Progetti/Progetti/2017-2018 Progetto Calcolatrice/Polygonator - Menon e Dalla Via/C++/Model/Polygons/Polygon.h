#ifndef POLYGON_H
#define POLYGON_H

#include <list>
#include <algorithm>
#include "Model/Line.h"

using std::list;

namespace Polygonator {
    class Polygon {
    private:
        list<Point> vertices;

        bool concave;
        bool regular;

        //Returns a list of points ordered to form a polygon
        list<Point> orderVertices(const list<Point> &) const;

        /* Returns whether the given list and the instance's vertices represent the same Polygon
         * (Their Points must be equals and in the same order, even if in different positions)
         */
        bool isEquals(list<Point>) const;

    public:
        explicit Polygon(const list<Point> &);
        virtual ~Polygon() = default;

        //Returns the list of vertices of the polygon
        const list<Point> &getVertices() const;

        //Returns whether the polygon is equilateral and equiangular
        bool isRegular() const;

        //Returns whether the polygon is concave or convex
        bool isConcave() const;

        //Returns the apothem constant when the polygon is regular (ratio apothem/side)
        virtual double getApothemConstant() const;

        //Returns the interior sum of the angles of the polygon
        int getInteriorAnglesSum() const;

        //Returns the list of diagonals of the polygon
        virtual list<Line> getDiagonals() const;

        //Returns the apothem when the polygon is regular
        double getApothem() const;

        //Returns the base of a convex polygon
        virtual double getBase() const;

        //Returns the height of a polygon (not available for irregular polygon)
        virtual double getHeight() const;

        /*Returns the area of the polygon
         *(This is an initial implementation that allows to calculate the area on a generic polygon;
         *it can be overridden to make it more efficient)
         */
        virtual double getArea() const;

        /*Returns the perimeter of the polygon
        *(This is an initial implementation that allows to calculate the perimeter on a generic polygon;
        *it can be overridden to make it more efficient)
        */
        virtual double getPerimeter() const;

        //Returns the name of the polygon
        virtual string getName() const;

        bool operator==(const Polygon &) const;

        bool operator!=(const Polygon &) const;
    };
}


#endif

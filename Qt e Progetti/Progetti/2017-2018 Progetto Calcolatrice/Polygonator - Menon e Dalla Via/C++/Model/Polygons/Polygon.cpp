#include "Polygon.h"

using Polygonator::Polygon;

Polygon::Polygon(const list<Point> &vertices) : vertices(vertices) {
    if (vertices.size() < 3) {
        throw Exception("Polygon with " + to_string(vertices.size()) + " points does not exist");
    }

    list<Point> duplicates = vertices;
    duplicates.sort();
    duplicates.unique();
    if (duplicates.size() != vertices.size()) {
        throw Exception("Duplicated points found");
    }

    list<Point> ordered = orderVertices(vertices);

    regular = true;
    double angleSum = 0;
    double regAngle= getInteriorAnglesSum()/ordered.size();
    double sidesLength=0;
    for (auto it = ordered.begin(); it != ordered.end(); it++) {
        Point a = it == ordered.begin() ? *prev(ordered.end()) : *prev(it);
        Point b = it == prev(ordered.end()) ? *ordered.begin() : *next(it);

        if (Line::belongs(a, b, *it)) {
            throw Exception("Points must be vertex");
        }

        if(sidesLength == 0) {
            sidesLength = Line::getDistance(*it, b);
        } else if(regular && fabs(Line::getDistance(*it, b) - sidesLength) > 0.0001) {
            regular = false;
        }

        double angle = Line::getAngleDegrees(a, *it, b);
        angleSum += angle;

        if(regular && fabs(angle-regAngle) > 0.0001) {
            regular = false;
        }
    }

    //assuming the user can input a number with max 3 decimals, the error cannot exceed 0.0001
    if (fabs(angleSum - getInteriorAnglesSum()) < 0.0001) {
        this->vertices = ordered;
        concave = false;
    } else {
        concave = true;
    }
}

const list<Point> &Polygon::getVertices() const {
    return vertices;
}

bool Polygonator::Polygon::isRegular() const {
    return regular;
}

bool Polygon::isConcave() const {
    return concave;
}

double Polygonator::Polygon::getApothemConstant() const {
    throw Exception("Apothem constant only available for regular polygons");
}

list<Point> Polygon::orderVertices(const list<Point> &vertices) const {
    Point min = *min_element(vertices.begin(), vertices.end());
    Point max = *max_element(vertices.begin(), vertices.end());

    Line line = Line(min, max);
    list<Point> above, below;

    for (Point vertex : vertices) {
        if (line.getYAt(vertex.getX()) > vertex.getY() || vertex == min) {
            below.push_back(vertex);
        } else {
            above.push_back(vertex);
        }
    }

    below.sort();
    above.sort();
    above.reverse();

    below.insert(below.end(), above.begin(), above.end());
    return below;
}

bool Polygon::isEquals(list<Point> vertices) const {
    list<Point>::const_iterator cit1, cit2;

    for (int i = 0; i < vertices.size(); i++) {
        for (cit1 = vertices.begin(), cit2 = this->vertices.begin();
             cit1 != vertices.end() || cit2 != this->vertices.end(); cit1++, cit2++) {
            if (*cit1 != *cit2) {
                break;
            }
        }

        if (cit1 == vertices.end() && cit2 == this->vertices.end()) {
            return true;
        }

        vertices.push_back(*vertices.begin());
        vertices.pop_front();
    }

    return false;
}

int Polygon::getInteriorAnglesSum() const {
    return 180 * (vertices.size() - 2);
}

list<Line> Polygon::getDiagonals() const {
    list<Line> diagonals;

    for (auto cit = vertices.begin(); cit != --prev(vertices.end()); cit++) {
        for (auto cit1 = ++next(cit); cit1 != vertices.end(); cit1++) {
            if (cit == vertices.begin() && cit1 == prev(vertices.end())) {
                break;
            }

            diagonals.emplace_back(*cit, *cit1);
        }
    }

    return diagonals;
}

double Polygonator::Polygon::getApothem() const {
    return getApothemConstant() * getBase();
}

double Polygon::getBase() const {
    if (isConcave()) {
        throw Exception("Cannot calculate the base of a concave polygon");
    }

    if( (*getVertices().begin()).getY() >= (*next(next(getVertices().begin()))).getY() ) {
        return Line::getDistance(*next(getVertices().begin()), *next(next(getVertices().begin())));
    }

    return Line::getDistance(*getVertices().begin(), *next(getVertices().begin()));
}

double Polygon::getHeight() const {
    if(!isRegular() || isConcave()) {
        throw Exception("Cannot calculate the height of an irregular polygon");
    }

    auto cit=getVertices().begin();
    for(int i=0; i<getVertices().size()/2+2; i++, cit++) {}

    if((*getVertices().begin()).getY() >= (*next(next(getVertices().begin()))).getY()) {
        return Line::getDistance(*next(getVertices().begin()), *next(next(getVertices().begin())), *next(cit));
    }

    return Line::getDistance(*getVertices().begin(), *next(getVertices().begin()), *cit);
}

double Polygon::getArea() const {
    if(isRegular()) {
        return getPerimeter() * getApothem() / 2;
    }

    double area = prev(vertices.end())->getX() * vertices.begin()->getY() -
                  vertices.begin()->getX() * prev(vertices.end())->getY();

    for (auto cit = vertices.begin(); cit != prev(vertices.end()); cit++) {
        area += cit->getX() * next(cit)->getY() - next(cit)->getX() * cit->getY();
    }

    return fabs(area / 2);
}

double Polygon::getPerimeter() const {
    if(isRegular()) {
        return getBase() * vertices.size();
    }

    double perimeter = Line::getDistance(*(vertices.begin()), *prev(vertices.end()));

    for (auto cit = vertices.begin(); cit != prev(vertices.end()); cit++) {
        perimeter += Line::getDistance(*cit, *next(cit));
    }

    return perimeter;
}

string Polygon::getName() const {
    return "Irregular Polygon";
}

bool Polygon::operator==(const Polygon &p) const {
    return isEquals(p.vertices);
}

bool Polygon::operator!=(const Polygon &p) const {
    return !(*this == p);
}
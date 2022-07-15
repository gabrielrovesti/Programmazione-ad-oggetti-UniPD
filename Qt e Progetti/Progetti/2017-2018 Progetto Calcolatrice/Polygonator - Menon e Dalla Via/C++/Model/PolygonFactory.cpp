#include "PolygonFactory.h"

template<class T>
T *PolygonFactory::checkPolygon(const Polygon &polygon) {
    if (T::canBeCreatedWith(polygon)) {
        return new T(polygon.getVertices());
    }

    return nullptr;
}

Polygon *PolygonFactory::makePolygon(const list<Point> &vertices) {
    Polygon polygon = Polygon(vertices);
    list<std::function<Polygon *(const Polygon &)>> functionList;

    functionList.emplace_back(checkPolygon<Triangle>);
    functionList.emplace_back(checkPolygon<Square>);
    functionList.emplace_back(checkPolygon<Rhombus>);
    functionList.emplace_back(checkPolygon<Rectangle>);
    functionList.emplace_back(checkPolygon<Kite>);
    functionList.emplace_back(checkPolygon<Parallelogram>);
    functionList.emplace_back(checkPolygon<Quadrilateral>);
    functionList.emplace_back(checkPolygon<Pentagon>);
    functionList.emplace_back(checkPolygon<Hexagon>);

    for (const auto &function : functionList) {
        Polygon *p = function(polygon);

        if (p) {
            return p;
        }
    }

    return new Polygon(vertices);
}
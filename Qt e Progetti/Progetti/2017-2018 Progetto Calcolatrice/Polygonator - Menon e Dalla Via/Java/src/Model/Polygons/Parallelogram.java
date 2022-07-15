package Model.Polygons;

import Model.Line;
import Model.Point;

import java.util.List;

public class Parallelogram extends Quadrilateral {
    public Parallelogram(final List<Point> vertices) throws Exception {
        super(vertices);
    }

    /**
     * Returns whether a list of points is a parallelogram or not
     */
    public static boolean canBeCreatedWith(final Polygon polygon) throws Exception {
        if (!Quadrilateral.canBeCreatedWith(polygon) || polygon.isConcave()) return false;
        Line first = new Line(polygon.getVertices().get(0), polygon.getVertices().get(1)),
                second = new Line(polygon.getVertices().get(1), polygon.getVertices().get(2)),
                third = new Line(polygon.getVertices().get(2), polygon.getVertices().get(3)),
                fourth = new Line(polygon.getVertices().get(3), polygon.getVertices().get(0));

        return first.equals(third) && second.equals(fourth);
    }

    @Override
    public double getHeight() throws Exception {
        if(getVertices().get(0).getY() >= getVertices().get(1).getY()) {
            return Line.getDistance(getVertices().get(1), getVertices().get(2), getVertices().get(0));
        }

        return Line.getDistance(getVertices().get(0), getVertices().get(1), getVertices().get(3));
    }

    @Override
    public double getArea() throws Exception {
        return getBase() * getHeight();
    }

    @Override
    public double getPerimeter() throws Exception {
        return (getBase() + Line.getDistance(vertices.get(3), vertices.get(0))) * 2;
    }

    @Override
    public String toString() {
        return "Parallelogram";
    }
}

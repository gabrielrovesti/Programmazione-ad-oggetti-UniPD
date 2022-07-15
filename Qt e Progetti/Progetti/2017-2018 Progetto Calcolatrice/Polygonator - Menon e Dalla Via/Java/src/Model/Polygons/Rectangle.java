package Model.Polygons;

import Model.Line;
import Model.Point;

import java.util.List;

public class Rectangle extends Parallelogram {
    public Rectangle(final List<Point> vertices) throws Exception {
        super(vertices);
    }

    /**
     * Returns whether a polygon is a rectangle or not
     */
    public static boolean canBeCreatedWith(final Polygon polygon) throws Exception {
        if (!Parallelogram.canBeCreatedWith(polygon)) return false;

        for (int i = 0; i < polygon.getVertices().size(); i++) {
            Point p = i == 0 ? polygon.getVertices().get(polygon.getVertices().size() - 1) : polygon.getVertices().get(i - 1);
            Point n = i == polygon.getVertices().size() - 1 ? polygon.getVertices().get(0) : polygon.getVertices().get(i + 1);
            Point a = polygon.getVertices().get(i);

            if (Math.abs(Line.getAngleDegrees(p, a, n) - 90) > 0.0001) return false;
        }

        return true;
    }

    @Override
    public double getHeight() {
        return Line.getDistance(vertices.get(0), vertices.get(vertices.size() - 1));
    }

    @Override
    public double getPerimeter() throws Exception {
        return (getBase() + getHeight()) * 2;
    }

    @Override
    public String toString() {
        return "Rectangle";
    }
}

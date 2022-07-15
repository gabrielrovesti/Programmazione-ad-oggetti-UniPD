package Model.Polygons;

import Model.Line;
import Model.Point;

import java.util.List;

public class Kite extends Quadrilateral {
    public Kite(final List<Point> vertices) throws Exception {
        super(vertices);
    }

    /**
     * Returns whether a list of points is a kite or not
     */
    public static boolean canBeCreatedWith(final Polygon polygon) throws Exception {
        if (!Quadrilateral.canBeCreatedWith(polygon) || polygon.isConcave()) return false;

        int adjacent = 0;

        for (int i = 0; i < polygon.getVertices().size(); i++) {
            Point p = i == 0 ? polygon.getVertices().get(polygon.getVertices().size() - 1) : polygon.getVertices().get(i - 1);
            Point n = i == polygon.getVertices().size() - 1 ? polygon.getVertices().get(0) : polygon.getVertices().get(i + 1);
            Point a = polygon.getVertices().get(i);

            if (new Line(p, a).equals(new Line(a, n))) adjacent++;
        }

        return adjacent >= 2;
    }

    @Override
    public double getArea() throws Exception {
        List<Line> d = getDiagonals();
        return d.get(0).getDistance() * d.get(1).getDistance() / 2;
    }

    @Override
    public double getPerimeter() throws Exception {
        double a = Line.getDistance(vertices.get(0), vertices.get(1));
        double b = Line.getDistance(vertices.get(3), vertices.get(0));
        if (Math.abs(a - b) < 0.0001) b = Line.getDistance(vertices.get(1), vertices.get(2));
        return (a + b) * 2;
    }

    @Override
    public String toString() {
        return "Kite";
    }
}

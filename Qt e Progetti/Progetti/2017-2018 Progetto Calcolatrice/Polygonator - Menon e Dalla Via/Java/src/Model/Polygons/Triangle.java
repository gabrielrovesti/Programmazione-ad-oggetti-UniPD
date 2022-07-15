package Model.Polygons;

import Model.Line;
import Model.Point;

import java.util.ArrayList;
import java.util.List;

public class Triangle extends Polygon {
    public Triangle(final List<Point> vertices) throws Exception {
        super(vertices);
    }

    /**
     * Returns whether a list of points can make a triangle or not
     */
    public static boolean canBeCreatedWith(final Polygon polygon) {
        return polygon.getVertices().size() == 3;
    }

    @Override
    public double getApothemConstant() {
        return 0.289;
    }

    @Override
    public List<Line> getDiagonals() throws Exception {
        throw new Exception("A triangle does not have diagonals");
    }

    /**
     * Returns the height of the calculated base of the triangle
     */
    @Override
    public double getHeight() throws Exception {
        if(getVertices().get(0).getY() >= getVertices().get(1).getY()) {
            return Line.getDistance(vertices.get(1), vertices.get(2), vertices.get(0));
        }

        return Line.getDistance(vertices.get(0), vertices.get(1), vertices.get(2));
    }

    /**
     * Returns the area of a triangle
     */
    @Override
    public double getArea() throws Exception {
        return getBase() * getHeight() / 2;
    }

    /**
     * Returns the list of all the medians of a triangle
     */
    public List<Line> getMedians() throws Exception {
        List<Line> medians = new ArrayList<>();

        for (Point vertex : vertices) {
            medians.add(getMedian(vertex));
        }

        return medians;
    }

    /**
     * Returns the median between the given point and the opposite line
     */
    public Line getMedian(final Point p) throws Exception {
        Point a = p.equals(vertices.get(0)) ? vertices.get(1) : vertices.get(0);
        Point b = p.equals(vertices.get(2)) ? vertices.get(1) : vertices.get(2);

        return new Line(Line.getMidPoint(a, b), p);
    }

    /**
     * Returns the list of all the bisectors of the triangle
     */
    public List<Line> getBisectors() throws Exception {
        List<Line> bisectors = new ArrayList<>();

        for (Point vertex : vertices) {
            bisectors.add(getBisector(vertex));
        }

        return bisectors;
    }

    /**
     * Returns the bisector of the given vertex
     */
    public Line getBisector(final Point p) throws Exception {
        Point a = p.equals(vertices.get(0)) ? vertices.get(1) : vertices.get(0);
        Point b = p.equals(vertices.get(2)) ? vertices.get(1) : vertices.get(2);

        double ap = Line.getDistance(a, p);
        double bp = Line.getDistance(b, p);

        double x = (ap * b.getX() + bp * a.getX()) / (ap + bp);
        double y = (ap * b.getY() + bp * a.getY()) / (ap + bp);

        return new Line(new Point(x, y), p);
    }

    @Override
    public String toString() {
        return "Triangle";
    }
}

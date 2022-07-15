package Model.Polygons;

import Model.Point;

import java.util.List;

public class Square extends Rectangle {
    public Square(final List<Point> vertices) throws Exception {
        super(vertices);
    }

    /**
     * Returns whether a polygon is a square or not
     */
    public static boolean canBeCreatedWith(final Polygon polygon) throws Exception {
        return Rectangle.canBeCreatedWith(polygon) && Rhombus.canBeCreatedWith(polygon);
    }

    @Override
    public double getApothemConstant() {
        return 0.5;
    }

    @Override
    public double getArea() throws Exception {
        return Math.pow(getBase(), 2);
    }

    @Override
    public double getPerimeter() throws Exception{
        return getBase() * 4;
    }

    @Override
    public String toString() {
        return "Square";
    }
}

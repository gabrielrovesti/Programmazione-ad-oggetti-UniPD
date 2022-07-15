package Model.Polygons;

import Model.Point;

import java.util.List;

public class Rhombus extends Kite {
    public Rhombus(final List<Point> vertices) throws Exception {
        super(vertices);
    }

    /**
     * Returns whether a polygon is a rhombus or not
     */
    public static boolean canBeCreatedWith(final Polygon polygon) throws Exception {
        return Parallelogram.canBeCreatedWith(polygon) && Kite.canBeCreatedWith(polygon);
    }

    @Override
    public double getPerimeter() throws Exception {
        return getBase() * 4;
    }

    @Override
    public String toString() {
        return "Rhombus";
    }
}

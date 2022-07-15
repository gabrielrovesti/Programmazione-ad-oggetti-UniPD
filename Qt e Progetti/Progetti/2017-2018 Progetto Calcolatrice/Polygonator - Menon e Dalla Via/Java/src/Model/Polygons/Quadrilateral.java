package Model.Polygons;

import Model.Line;
import Model.Point;

import java.util.List;

public class Quadrilateral extends Polygon {
    public Quadrilateral(final List<Point> vertices) throws Exception {
        super(vertices);
    }

    /**
     * Returns whether a list of points can make a quadrilateral or not
     */
    public static boolean canBeCreatedWith(final Polygon polygon) throws Exception {
        return polygon.getVertices().size() == 4;
    }

    @Override
    public String toString() {
        return "Quadrilateral";
    }
}

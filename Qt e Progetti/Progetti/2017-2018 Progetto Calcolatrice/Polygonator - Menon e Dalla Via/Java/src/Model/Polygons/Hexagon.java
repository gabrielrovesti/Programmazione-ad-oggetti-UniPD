package Model.Polygons;

import Model.Line;
import Model.Point;

import java.util.List;

public class Hexagon extends Polygon {
    public Hexagon(final List<Point> vertices) throws Exception {
        super(vertices);
    }

    /**
     * Returns whether a list of points can make an hexagon or not
     */
    public static boolean canBeCreatedWith(final Polygon polygon) {
        return polygon.getVertices().size() == 6;
    }

    @Override
    public double getApothemConstant() throws Exception {
        return isRegular() ? 0.866 : super.getApothemConstant();
    }

    @Override
    public String toString() {
        return "Hexagon";
    }
}

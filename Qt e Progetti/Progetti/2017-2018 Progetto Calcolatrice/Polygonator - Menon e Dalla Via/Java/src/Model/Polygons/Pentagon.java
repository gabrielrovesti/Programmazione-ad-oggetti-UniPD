package Model.Polygons;

import Model.Line;
import Model.Point;

import java.util.List;

public class Pentagon extends Polygon{
    public Pentagon(final List<Point> vertices) throws Exception {
        super(vertices);
    }

    /**
     * Returns whether a list of points can make a pentagon or not
     */
    public static boolean canBeCreatedWith(final Polygon polygon) {
        return polygon.getVertices().size() == 5;
    }

    @Override
    public double getApothemConstant() throws Exception {
        return isRegular() ? 0.688 : super.getApothemConstant();
    }

    @Override
    public String toString() {
        return "Pentagon";
    }
}

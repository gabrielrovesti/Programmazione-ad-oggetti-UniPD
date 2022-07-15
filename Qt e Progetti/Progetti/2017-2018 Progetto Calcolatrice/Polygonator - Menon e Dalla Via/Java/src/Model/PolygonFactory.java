package Model;

import Model.Polygons.*;

import java.util.Arrays;
import java.util.List;

public abstract class PolygonFactory {

    private static <T extends Polygon> T checkPolygon(final Polygon polygon, Class<T> clazz) throws Exception {
        if ((boolean)clazz.getDeclaredMethod("canBeCreatedWith", Polygon.class).invoke(clazz, polygon)) {
            return clazz.getDeclaredConstructor(List.class).newInstance(polygon.getVertices());
        }

        return null;
    }

    public static Polygon makePolygon(List<Point> vertices) throws Exception {
        Polygon polygon = new Polygon(vertices);

        List<Class<? extends Polygon>> list = Arrays.asList(
                Triangle.class, Square.class, Rhombus.class,
                Rectangle.class, Kite.class, Parallelogram.class, Quadrilateral.class,
                Pentagon.class, Hexagon.class
        );

        for (Class<? extends Polygon> clazz : list) {
            Polygon obj = checkPolygon(polygon, clazz);

            if (obj != null) {
                return obj;
            }
        }
        return polygon;
    }
}

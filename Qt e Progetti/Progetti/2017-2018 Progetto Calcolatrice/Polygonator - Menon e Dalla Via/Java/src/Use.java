import Model.Line;
import Model.Point;
import Model.PolygonFactory;
import Model.Polygons.Parallelogram;
import Model.Polygons.Polygon;
import Model.Polygons.Triangle;

import java.util.Arrays;
import java.util.List;

public class Use {

    private static void make(List<Point> vertices) {
        try {
            Polygon polygon = PolygonFactory.makePolygon(vertices);

            System.out.println("\n---------------------------------------");
            System.out.println("POLYGON TYPE: " + polygon.toString());
            System.out.println("AREA: " + String.format("%.2f", polygon.getArea()));
            System.out.println("PERIMETER: " + String.format("%.2f", polygon.getPerimeter()));

            if(!polygon.isConcave()) {
                System.out.println("BASE: " + polygon.getBase());

                if(polygon.isRegular() || polygon instanceof Triangle || polygon instanceof Parallelogram) {
                    System.out.println("HEIGHT: " + polygon.getHeight());
                }
            }

            if (polygon instanceof Triangle) {
                int bisectorCount = 1;
                for (Line line : ((Triangle) polygon).getBisectors()) {
                    System.out.println("BISECTOR " + bisectorCount + ": " + String.format("%.2f", line.getDistance()));
                    bisectorCount++;
                }

                int medianCount = 1;
                for (Line line : ((Triangle) polygon).getMedians()) {
                    System.out.println("MEDIAN " + medianCount + ": " + String.format("%.2f", line.getDistance()));
                    medianCount++;
                }
            } else {
                int diagonalCount = 1;
                for (Line line : polygon.getDiagonals()) {
                    System.out.println("DIAGONAL " + diagonalCount + ": " + String.format("%.2f", line.getDistance()));
                    diagonalCount++;
                }
            }
            System.out.println("---------------------------------------\n");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        make(Arrays.asList(
                new Point(30, 10),
                new Point(50, 50),
                new Point(-10, 10)
        ));

        make(Arrays.asList(
                new Point(0, 0),
                new Point(20, 0),
                new Point(10, 20),
                new Point(30, 10),
                new Point(-10, 10)
        ));
    }

}

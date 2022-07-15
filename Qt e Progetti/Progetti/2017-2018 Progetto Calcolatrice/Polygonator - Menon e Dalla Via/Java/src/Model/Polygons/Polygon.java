package Model.Polygons;

import Model.Line;
import Model.Point;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Polygon {
    protected List<Point> vertices;
    private boolean concave;
    private boolean regular;

    public Polygon(final List<Point> vertices) throws Exception {
        if (vertices.size() < 3) {
            throw new Exception("Polygon with " + vertices.size() + " points does not exist");
        }

        this.vertices = vertices;

        for (Point vertex : vertices) {
            for (int i = vertices.indexOf(vertex) + 1; i < vertices.size(); i++) {
                if (vertex.equals(vertices.get(i))) throw new Exception("Duplicated points found");
            }
        }

        List<Point> ordered = orderVertices(vertices);

        regular=true;
        double angleSum = 0;
        double regAngle = getInteriorAnglesSum() / ordered.size();
        double sidesLength = 0;
        for (int i = 0; i < ordered.size(); i++) {
            Point p = i == 0 ? ordered.get(ordered.size() - 1) : ordered.get(i - 1);
            Point n = i == ordered.size() - 1 ? ordered.get(0) : ordered.get(i + 1);
            Point a = ordered.get(i);

            if (Line.belongs(p, n, a)) {
                throw new Exception("Points must be vertex");
            }

            if(sidesLength == 0) {
                sidesLength = Line.getDistance(a, n);
            } else if(regular && Math.abs(Line.getDistance(a, n) - sidesLength) > 0.0001) {
                regular = false;
            }

            double angle = Line.getAngleDegrees(p, a, n);
            angleSum += angle;

            if(regular && Math.abs(angle - regAngle) > 0.0001) {
                regular = false;
            }
        }

        if (Math.abs(angleSum - getInteriorAnglesSum()) < 0.0001) {
            this.vertices = ordered;
            concave = false;
        } else {
            concave = true;
        }
    }

    public List<Point> getVertices() {
        return Collections.unmodifiableList(vertices);
    }

    /**
     * Returns whether the polygon is equilateral and equiangular
     */
    public final boolean isRegular() {
        return regular;
    }

    /**
     * Returns whether the polygon is concave or convex
     */
    public final boolean isConcave() {
        return concave;
    }

    /**
     * Returns the apothem constant (ratio apothem/side) when the polygon is regular
     */
    public double getApothemConstant() throws Exception{
        throw new Exception("Apothem constant only available for regular polygons");
    }

    /**
     * Returns a list of points ordered to form a polygon
     */
    private List<Point> orderVertices(final List<Point> vertices) throws Exception {
        Point min = Collections.min(vertices, (p1, p2) -> p1.smaller(p2) ? -1 : (p1.equals(p2) ? 0 : 1));
        Point max = Collections.max(vertices, (p1, p2) -> p1.smaller(p2) ? -1 : (p1.equals(p2) ? 0 : 1));

        Line line = new Line(min, max);
        List<Point> above = new ArrayList<>();
        List<Point> below = new ArrayList<>();

        for (Point vertex : vertices) {
            if (line.getYAt(vertex.getX()) > vertex.getY() || vertex.equals(min)) {
                below.add(vertex);
            } else {
                above.add(vertex);
            }
        }

        below.sort((p1, p2) -> p1.smaller(p2) ? -1 : (p1.equals(p2) ? 0 : 1));
        above.sort((p1, p2) -> p1.smaller(p2) ? -1 : (p1.equals(p2) ? 0 : 1));
        Collections.reverse(above);
        below.addAll(above);

        return below;
    }

    /**
     * Returns whether the given list and the instance's vertices represent the same Polygon
     * (Their Points must be equals and in the same order, even if in different position)
     */
    private boolean isEquals(List<Point> vertices) {
        Point p1 = null, p2 = null;

        for (int i = 0; i < vertices.size(); i++) {
            for (int j = 0; j < vertices.size() || j < this.vertices.size(); j++) {
                p1 = vertices.get(j);
                p2 = this.vertices.get(j);

                if (!p1.equals(p2)) {
                    break;
                }
            }

            if (p1 == vertices.get(vertices.size() - 1) && p2 == this.vertices.get(this.vertices.size() - 1)) {
                return true;
            }

            vertices.remove(p1);
            vertices.add(p1);
        }

        return false;
    }

    /**
     * Returns the interior sum of the angles of the polygon
     */
    public final int getInteriorAnglesSum() {
        return 180 * (vertices.size() - 2);
    }

    /**
     * Returns the list of diagonals of the polygon
     */
    public List<Line> getDiagonals() throws Exception {
        List<Line> diagonals = new ArrayList<>();

        for (Point vertex : vertices.subList(0, vertices.size() - 1)) {
            for (Point vertex1 : vertices.subList(vertices.indexOf(vertex) + 2, vertices.size())) {
                if (vertex == vertices.get(0) && vertex1 == vertices.get(vertices.size() - 1)) {
                    break;
                }

                diagonals.add(new Line(vertex, vertex1));
            }
        }

        return diagonals;
    }

    /**
     * Returns the apothem when the polygon is regular
     */
    public final double getApothem() throws Exception {
        return getApothemConstant() * getBase();
    }

    /**
     * Returns the base of a polygon (not available for concave polygon)
     */
    public double getBase() throws Exception {
        if (isConcave()) {
            throw new Exception("Cannot calculate the base of a concave polygon");
        }

        if(getVertices().get(0).getY() >= getVertices().get(1).getY()) {
            return Line.getDistance(getVertices().get(1), getVertices().get(2));
        }
        return Line.getDistance(vertices.get(0), vertices.get(1));
    }

    /**
     * Returns the height of a polygon (not available for irregular polygon)
     */
    public double getHeight() throws Exception {
        if (!isRegular() || isConcave()) {
            throw new Exception("Cannot calculate the height of an irregular polygon");
        }

        int height = getVertices().size()/2+2;
        if(getVertices().get(0).getY() >= getVertices().get(1).getY()) {
            return Line.getDistance(getVertices().get(1), getVertices().get(2), getVertices().get(height+1));
        }

        return  Line.getDistance(getVertices().get(0), getVertices().get(1), getVertices().get(height));
    }

    public double getArea() throws Exception {
        if(isRegular()) {
            return getApothem() * getPerimeter() / 2;
        }

        double area = (vertices.get(vertices.size() - 1).getX() * vertices.get(0).getY()) -
                (vertices.get(0).getX() * vertices.get(vertices.size() - 1).getY());

        for (int i = 0; i < vertices.size() - 1; i++) {
            area += vertices.get(i).getX() * vertices.get(i + 1).getY() - vertices.get(i + 1).getX() * vertices.get(i).getY();
        }

        return Math.abs(area / 2);
    }

    public double getPerimeter() throws Exception {
        if(isRegular()) {
            return getBase() * vertices.size();
        }

        double perimeter = Line.getDistance(vertices.get(0), vertices.get(vertices.size() - 1));

        for (int i = 0; i < vertices.size() - 1; i++) {
            perimeter += Line.getDistance(vertices.get(i), vertices.get(i + 1));
        }

        return perimeter;
    }

    public static boolean canBeCreatedWith(final Polygon polygon) throws Exception {
        return true;
    }

    @Override
    public String toString() {
        return "Irregular Polygon";
    }
}

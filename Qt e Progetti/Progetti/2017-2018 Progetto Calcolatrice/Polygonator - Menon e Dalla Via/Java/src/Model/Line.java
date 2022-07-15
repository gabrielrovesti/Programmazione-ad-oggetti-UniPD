package Model;

public class Line {
    private Point a, b;

    public Line(Point a, Point b) throws Exception {
        if (a.equals(b)) throw new Exception("Cannot generate a line with two equal points");
        this.a = new Point(a.getX(), a.getY());
        this.b = new Point(b.getX(), b.getY());
    }

    public Point getA() {
        return a;
    }

    public Point getB() {
        return b;
    }

    /**
     * Returns the corresponding X value of the line, given the Y value
     */
    public double getXAt(double y) {
        return ((y - a.getY()) / (b.getY() - a.getY()) * (b.getX() - a.getX())) + a.getX();
    }

    /**
     * Returns the corresponding Y value of the line, given the X value
     */
    public double getYAt(double x) {
        return ((x - a.getX()) / (b.getX() - a.getX()) * (b.getY() - a.getY())) + a.getY();
    }

    /**
     * Returns whether a Point is on the straight line or not
     */
    public boolean belongs(final Point p) throws Exception {
        return belongs(a, b, p);
    }

    public static boolean belongs(final Point a, final Point b, final Point p) throws Exception {
        return getDistance(a, b, p) == 0;
    }

    /**
     * Returns the distance between the points a and b
     */
    public double getDistance() {
        return getDistance(a, b);
    }

    public static double getDistance(final Point a, final Point b) {
        return Math.sqrt(Math.pow(b.getX() - a.getX(), 2) + Math.pow(b.getY() - a.getY(), 2));
    }

    /**
     * Returns the length (in absolute value) of the projection of a point on the line
     */
    public double getDistance(final Point p) throws Exception {
        return getDistance(a, b, p);
    }

    public static double getDistance(final Point a, final Point b, final Point p) throws Exception {
        if (a.getX() == b.getX()) {
            return Math.abs(p.getX() - a.getX());
        }

        if (a.getY() == b.getY()) {
            return Math.abs(p.getY() - a.getY());
        }

        double m = getAngularCoefficient(a, b);
        double q = -m * a.getX() + a.getY();

        return Math.abs(p.getY() - m * p.getX() - q) / Math.sqrt(1 + Math.pow(m, 2));
    }

    /**
     * Returns the mid point of the line
     */
    public Point getMidPoint() {
        return getMidPoint(a, b);
    }

    public static Point getMidPoint(final Point a, final Point b) {
        return new Point((a.getX() + b.getX()) / 2, (a.getY() + b.getY()) / 2);
    }

    /**
     * Returns the angular coefficient of the line
     */
    public double getAngularCoefficient() throws Exception {
        return getAngularCoefficient(a, b);
    }

    public static double getAngularCoefficient(final Point a, final Point b) throws Exception {
        if (a.getX() == b.getX()) {
            throw new Exception("The line is parallel to the y axis");
        }

        return (b.getY() - a.getY()) / (b.getX() - a.getX());
    }

    /**
     * Returns the equation of the straight line
     */
    public String getEquation() throws Exception {
        if (a.getX() == b.getX()) {
            return "x = " + String.format("%.2f", a.getX());
        }

        if (a.getY() == b.getY()) {
            return "y = " + String.format("%.2f", a.getY());
        }

        double m = getAngularCoefficient();
        double q = -m * a.getX() + a.getY();

        return "y = " + String.format("%.2f", m) + "x" + (q >= 0 ? "+" : "-") + String.format("%.2f", q);
    }

    /**
     * Returns the degrees of the angle formed by two intersecting lines
     */
    public double getAngleDegrees(final Line l) throws Exception {
        if (!a.equals(l.a) && !a.equals(l.b) && !b.equals(l.a) && !b.equals(l.b)) {
            throw new Exception("No points in common between the two lines");
        }

        Point middle = !a.equals(l.a) && !a.equals(l.b) ? b : a;
        Point first = !a.equals(middle) ? a : b;
        Point last = l.a.equals(middle) ? l.a : l.b;

        return getAngleDegrees(first, middle, last);
    }

    public static double getAngleDegrees(final Point first, final Point middle, final Point last) {
        return Math.acos((Math.pow(getDistance(first, middle), 2) + Math.pow(getDistance(last, middle), 2) -
                Math.pow(getDistance(first, last), 2)) / (2 * getDistance(middle, first) * getDistance(middle, last))) *
                180 / Math.PI;
    }

    public boolean equals(final Line l) {
        return Math.abs(getDistance() - l.getDistance()) < 0.0001;
    }

    @Override
    public String toString() {
        return "Line";
    }
}

package Model;

public class Point {
    private double x, y;

    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    /**
     * Returns the point-slope equation of a straight line
     */
    public String getEquation() {
        return "y " + (y >= 0 ? "- " : "+ ") + String.format("%.2f", y) + " = m(x " + (x >= 0 ? "- " : "+ ") + String.format("%.2f", y) + ")";
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Point) {
            Point p = (Point) obj;

            return x == p.getX() && y == p.getY();
        }

        return false;
    }

    public boolean smaller(Point p) {
        return x < p.getX() || (x == p.getX() && y < p.getY());
    }

    public boolean greater(Point p) {
        return x > p.getX() || (x == p.getX() && y > p.getY());
    }

    @Override
    public String toString() {
        return "(" + String.format("%.2f", x) + "," + String.format("%.2f", y) + ")";
    }
}

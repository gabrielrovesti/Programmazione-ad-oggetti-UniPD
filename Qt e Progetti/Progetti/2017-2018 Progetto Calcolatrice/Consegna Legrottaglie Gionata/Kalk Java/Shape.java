
public abstract class Shape {
	private static int n_shape=0;
	protected int id=0;
	
	public Shape() {
		this.id=++Shape.n_shape;
	}
	public Shape(Shape s) {
		this.id=++Shape.n_shape;
	}
	public int get_id() {
		return this.id;
	}
	@Override public abstract String toString();
	public abstract String get_nomeClasse();
	public abstract double get_perimetro();
	public abstract double get_area();
	@Override public abstract Shape clone();

}

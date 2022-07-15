
public final class Vertice extends Punto {

	public Vertice(double a,double b) {
		super(a,b);
	}
	public Vertice() {
		super(0,0);
	}
	public Vertice(Vertice v) {
		super(v);
	}
	@Override public String toString() {
		return "(V," + this.get_X() + "," + this.get_Y() + ")";
	}
	@Override
	public Vertice clone(){
		return new Vertice(this);
	}
	// Calcola l'angolo del vertice B
	public static double get_Angolo(final Vertice a, final Vertice b, final Vertice c){
		
	    Punto ab = new Punto( b.get_X() - a.get_X(), b.get_Y() - a.get_Y() );
	    Punto cb = new Punto( b.get_X() - c.get_X(), b.get_Y() - c.get_Y() );

	    double dot = (ab.get_X() * cb.get_X() + ab.get_Y() * cb.get_Y() );
	    double cross = (ab.get_X() * cb.get_Y() - ab.get_Y() * cb.get_X());

	    double alpha = Math.atan2(cross, dot);
	    return (alpha * 180 / Math.PI);
	}
}

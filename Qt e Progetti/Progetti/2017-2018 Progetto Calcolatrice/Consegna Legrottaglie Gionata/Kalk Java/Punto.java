
public class Punto {
	private double x, y;
	
	public Punto(double a, double b){		
		this.x=a;;
		this.y=b;
	}
	
	protected Punto(Punto p){
		this.x=p.x;
		this.y=p.y;
	}
	
	public double get_X() {
		return x;
	}
	public double get_Y() {
		return y;
	}

	public static double distanza(final Punto p1, final Punto p2){
		double dX = ((p1.get_X()-p2.get_X())*(p1.get_X()-p2.get_X()));
	    double dY = ((p1.get_Y()-p2.get_Y())*(p1.get_Y()-p2.get_Y()));
	    return Math.sqrt( dX + dY );
	}
	
	public boolean minore(Punto p) {
		if(this.y != p.y)
			return y < p.y;
		return x < p.x;
	}
	
	@Override public String toString() {
		return "(" + this.x + "," + this.y + ")";
	}
	
	
	@Override public boolean equals(Object obj) {
		if(!(obj instanceof Punto)) 
			return false;
		
		if(this == obj) 
			return true;
		Punto p = (Punto)obj;
		return p.x==x && p.y==y;
	}
	@Override
	public Punto clone(){
		return new Punto(this);
	}

}

public class Cerchio extends Shape
{
	private Vertice origine;
	private double raggio;
	public Cerchio(Vertice v, double d){
		if(d>0) {
			origine=v;
			raggio=d;
		}
		else
			throw new IllegalArgumentException("Impossibile creare un cerchio con raggio regativo");
	}
	public Cerchio(Cerchio c) {
		origine=c.origine.clone();
		raggio=c.raggio;
	}
	public double get_raggio() {
		return raggio;
	}
	public Vertice get_origine() {
		return origine;
	}
	public void set_origine(Vertice v) {
		origine=v;
	}
	public double get_perimetro() {
		return 2 * Math.PI * raggio;
	}
	public double get_area() {
		return Math.PI * raggio * raggio;
	}
    public String get_nomeClasse() {
    	return "Cerchio";
    }
    public String toString() {
    	return "Cerchio, origine: "+origine+" raggio: "+raggio;
    }
    public Cerchio somma (Cerchio c) {
    	return new Cerchio(origine,raggio+c.raggio);
    }
    public Cerchio moltiplicazione (Cerchio c) {
    	return new Cerchio(origine,raggio*c.raggio);
    }
    public Cerchio sottrazione (Cerchio c) {
    	if((raggio - c.raggio)>0)
    		return new Cerchio(origine,raggio-c.raggio);
    	else
    		throw new IllegalArgumentException("Impossibile creare un cerchio con raggio regativo");
    }
    public Cerchio divisione (Cerchio c) {
    	return new Cerchio(origine,raggio/c.raggio);
    }
	@Override public boolean equals(Object obj) {
		if(!(obj instanceof Cerchio)) 
			return false;
		if(this == obj) 
			return true;
		Cerchio c = (Cerchio)obj;
		return raggio == c.raggio && origine.equals(c.origine);
	}
	@Override
	public Cerchio clone(){
		return new Cerchio(this);
	}

}



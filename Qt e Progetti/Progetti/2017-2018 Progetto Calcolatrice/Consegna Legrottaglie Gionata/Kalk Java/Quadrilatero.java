import java.util.Vector;
public class Quadrilatero extends PoligonoConvesso {
	protected double lati[]={0,0,0,0};
	protected int nLati=4;
	
	private void set_lati(Vector<Vertice> v) {
		  int x=0,y=1;
		  while(x<v.size()){
		      if(y==v.size())y=0;
		      lati[x] = Math.sqrt((Math.pow((v.get(y).get_X()-v.get(x).get_X()),2)+Math.pow(v.get(y).get_Y()-v.get(x).get_Y(),2)));
		      x++; y++;
		    }
	}
	public Quadrilatero(Vector<Vertice> V,boolean b) {
		super(V,4,"Quadrilatero",b);
		this.set_lati(V);
	}

	public Quadrilatero(Vector<Vertice> V) {
		super(V,4,"Quadrilatero");
	}

	Quadrilatero(Quadrilatero T){
		super(T);
		this.set_lati(T.Lista);
		}

	@Override
	public String toString() {
		  String s ="Quadrilatero: ";

		  for (Vertice i : this.Lista) {
	            
	            s+= i.toString();
		  }
		  return s;
	}

	@Override
	public String get_nomeClasse() {
		return "Quadrilatero";
	}

	@Override
	public double get_perimetro() {
		return lati[0]+lati[1]+lati[2]+lati[3];
	}

	@Override
	public double get_area() {
		  double A,C;
		  A = Vertice.get_Angolo(this.Lista.get(0),this.Lista.get(3),this.Lista.get(1));
		  C = Vertice.get_Angolo(this.Lista.get(2),this.Lista.get(1),this.Lista.get(3));
		  return ((lati[3]*lati[0])/2)* Math.sin(A* (Math.PI / 180.0)) + ((lati[1]*lati[2])/2)*Math.sin(C* (Math.PI / 180.0));
	}
	@Override
	public double get_lato(int i) {
		return this.lati[i];
	}
	@Override
	public int get_nLati() {
		return this.nLati;
	}
	@Override
	public Quadrilatero clone() {
		return new Quadrilatero(this);
	}

}

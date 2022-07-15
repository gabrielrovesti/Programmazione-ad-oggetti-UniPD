import java.util.Vector;
public class Triangolo extends PoligonoConvesso {
	protected double lati[]={0,0,0};
	protected int nLati=3;
	
	private void set_lati(Vector<Vertice> v) {
		  int x=0,y=1;
		  while(x<v.size()){
		      if(y==v.size())y=0;
		      lati[x] = Math.sqrt((Math.pow((v.get(y).get_X()-v.get(x).get_X()),2)+Math.pow(v.get(y).get_Y()-v.get(x).get_Y(),2)));
		      x++; y++;
		    }
	}
	public Triangolo(Vector<Vertice> V,boolean b) {
		super(V,3,"Triangolo",b);
		this.set_lati(V);
	}

	public Triangolo(Vector<Vertice> V) {
		super(V,3,"Triangolo");
	}

	Triangolo(Triangolo T){
		super(T);
		this.set_lati(T.Lista);
		}

	@Override
	public String toString() {
		  String s ="Triangolo: ";

		  for (Vertice i : this.Lista) {
	            s+= i.toString();
		  }
		  return s;
	}

	@Override
	public String get_nomeClasse() {
		return "Triangolo";
	}

	@Override
	public double get_perimetro() {
		return lati[0]+lati[1]+lati[2];
	}

	@Override
	public double get_area() {
		  double p = this.get_perimetro()/2;
		  double x =p*(p-lati[0])*(p-lati[1])*(p-lati[2]);
		  return Math.sqrt(x);
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
	public Triangolo clone() {
		return new Triangolo(this);
	}

}

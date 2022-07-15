import java.util.Vector;
public class Esadecagono extends PoligonoConvesso {
	protected double lati[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	protected int nLati=16;
	
	private void set_lati(Vector<Vertice> v) {
		  int x=0,y=1;
		  while(x<v.size()){
		      if(y==v.size())y=0;
		      lati[x] = Math.sqrt((Math.pow((v.get(y).get_X()-v.get(x).get_X()),2)+Math.pow(v.get(y).get_Y()-v.get(x).get_Y(),2)));
		      x++; y++;
		    }
	}
	public Esadecagono(Vector<Vertice> V,boolean b) {
		super(V,16,"Esadecagono",b);
		this.set_lati(V);
	}

	public Esadecagono(Vector<Vertice> V) {
		super(V,16,"Esadecagono");
	}

	Esadecagono(Esadecagono T){
		super(T);
		this.set_lati(T.Lista);
		}

	@Override
	public String toString() {
		  String s ="Esadecagono: ";

		  for (Vertice i : this.Lista) {
	            s+= i.toString();
		  }
		  return s;
	}

	@Override
	public String get_nomeClasse() {
		return "Esadecagono";
	}

	@Override
	public double get_perimetro() {
		double p=0;
		for(double n: this.lati) {
			p+=n;
		}
		return p;
	}

	@Override
	public double get_area() {
		  int a=0,b=1, c=2;
		  double area=0;
		  while(c < this.Lista.size()){
			  Vector<Vertice> temp= new Vector<Vertice>();
			  temp.add(Lista.get(a));
			  temp.add(Lista.get(b));
			  temp.add(Lista.get(c));
			  Triangolo t=new Triangolo(temp);
		      area+= t.get_area();
		      c++;b++;
		    }
		  return area;
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
	public Esadecagono clone() {
		return new Esadecagono(this);
	}
}
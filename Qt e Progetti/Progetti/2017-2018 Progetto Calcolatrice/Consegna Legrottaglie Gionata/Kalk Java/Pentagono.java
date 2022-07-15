import java.util.Vector;
public class Pentagono extends PoligonoConvesso {
	protected double lati[]={0,0,0,0,0};
	protected int nLati=5;
	
	private void set_lati(Vector<Vertice> v) {
		  int x=0,y=1;
		  while(x<v.size()){
		      if(y==v.size())y=0;
		      lati[x] = Math.sqrt((Math.pow((v.get(y).get_X()-v.get(x).get_X()),2)+Math.pow(v.get(y).get_Y()-v.get(x).get_Y(),2)));
		      x++; y++;
		    }
	}
	public Pentagono(Vector<Vertice> V,boolean b) {
		super(V,5,"Pentagono",b);
		this.set_lati(V);
	}

	public Pentagono(Vector<Vertice> V) {
		super(V,5,"Pentagono");
	}

	Pentagono(Pentagono T){
		super(T);
		this.set_lati(T.Lista);
		}

	@Override
	public String toString() {
		  String s ="Pentagono: ";

		  for (Vertice i : this.Lista) {
	            s+= i.toString();
		  }
		  return s;
	}

	@Override
	public String get_nomeClasse() {
		return "Pentagono";
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
	public Pentagono clone() {
		return new Pentagono(this);
	}

}

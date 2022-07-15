import java.util.Vector;

public final class Calcolatrice {
	public static void main(String[] args) {
		Vertice a= new Vertice(0,0);
		Vertice b= new Vertice(0,100);
		Vertice c= new Vertice(100,0);
		Vertice d= new Vertice(100,100);
		Vector<Vertice> V= new Vector<Vertice>();
		V.add(a);
		V.add(b);
		V.add(c);
		V.add(d);
		try {
			PoligonoConvesso p= PoligonoConvesso.crea_poligono(V);
			System.out.println(p.toString());
			p=p.aggiungi_vertice(new Vertice(20,110));
			System.out.println(p.toString());
			p=p.aggiungi_vertice(new Vertice(30,110));

			System.out.println(p.toString());
			p=p.aggiungi_vertice(new Vertice(20,100));
			System.out.println(p.toString());
			p=p.aggiungi_vertice(new Vertice(40,108));
			System.out.println(p.toString());
			p=p.rimuovi_vertice(a);
			System.out.println(p.toString());
				Shape cerchio = new Cerchio(new Vertice(0,0),10);
			System.out.println(cerchio.toString());


			

		}
		catch(Exception e) {
			System.out.println(e.getMessage());
		}

	}

}

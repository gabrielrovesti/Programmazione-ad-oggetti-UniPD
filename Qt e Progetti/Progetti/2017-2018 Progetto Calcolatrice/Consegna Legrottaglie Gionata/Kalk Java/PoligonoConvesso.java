import java.util.Collections;
import java.util.Vector;
public abstract class PoligonoConvesso extends Poligono {
	
	protected Vector<Vertice> Lista;
	
	public abstract double get_lato(int i);
	public abstract int get_nLati();
	
	public PoligonoConvesso(PoligonoConvesso p) {
		super();
		this.Lista= new Vector<Vertice>(p.Lista);
	}
	public PoligonoConvesso(Vector<Vertice>V, int x, String name){
		super();
		this.Lista= new Vector<Vertice>(V);

		  this.Lista = grahamScan(this.Lista);
		  if(Lista.size() == x){
		      Lista = V;
		    }else{
		     // reduce_n_shape();
		    	throw new IllegalArgumentException("Impossibile creare un "+ name +" utilizzando questi vertici");
		    }
		}
	
	protected PoligonoConvesso(Vector<Vertice>V, int x, String name,boolean check){
		super();
		this.Lista=new Vector<Vertice>(V);

	}
	public PoligonoConvesso aggiungi_vertice(Vertice v) {
		Vector<Vertice> p= new Vector<Vertice>(this.Lista);
		p.add(v);
		return PoligonoConvesso.crea_poligono(p);
	}
	
	public PoligonoConvesso rimuovi_vertice(Vertice v) {
		boolean found;
		found= false;
		Vector<Vertice> p= new Vector<Vertice>(this.Lista);

		int i=0;
		for(;i<p.size() && !found;++i) {
			if(p.get(i).equals(v)) {
				found=true;
			}		
		}
		if(found) {
			p.remove(i-1);
		}
		else {
			throw new IllegalArgumentException("Vertice non trovato");
		}
		return PoligonoConvesso.crea_poligono(p);
	}
		
	  private static void rimuovi_doppioni(Vector<Vertice> V){
		  for(int i=0;i<V.size();i++){
		      for(int j=i+1; j<V.size();j++){
		          if(V.get(i).equals(V.get(j))) {
		        	  V.remove(j); j--;
		          }
		        }
		    }
	  }
	  
	  public static double ccw(Vertice a, Vertice b, Vertice c) {
		    double area = (b.get_X() - a.get_X()) * (c.get_Y() - a.get_Y()) - (b.get_Y() - a.get_Y()) * (c.get_X() - a.get_X());
		    if (area > 0)
		        return -1;
		    else if (area < 0)
		        return 1;
		    return 0;	  }
	  
	  public static double sqrDist(Vertice a, Vertice b) {
		    double dx = a.get_X() - b.get_X(), dy = a.get_Y() - b.get_Y();
		    return dx * dx + dy * dy;
	  }

	  private static boolean checkVector(Vector<Vertice> Points) {
		  double somma=0;
		  int b=0;
		  for(int itb=0; itb < Points.size();itb++){
		      int a,c;
		      if(b==0) {a=Points.size()-1; c=b+1;}
		      else if(b==Points.size()-1){c=0; a=b-1;}
		      else {a=b-1; c=b+1;}
		      double angolo=  Math.abs(Vertice.get_Angolo(Points.get(b),Points.get(a),Points.get(c)));
		      if(angolo == 180) {
		          Points.remove(itb);
		          angolo=0;
		        }else{
		          b++;
		        }
		      if(angolo > 180) return false;
		      somma+= angolo;
		      if(somma > (180*(Points.size()-2)) || somma==0) return false;

		    }
		    return true;
	  }
	  

	  public static Vertice pivot;
	  private static Vector<Vertice> grahamScan(Vector<Vertice> Points)    {
		  
		    rimuovi_doppioni(Points);
		    Vector<Vertice> hull= new Vector<Vertice>();
		    int N= Points.size();

		    // find the Vertice having the least y coordinate (pivot),
		    // ties are broken in favor of lower x coordinate
		    int leastY = 0;
		    for (int i = 1; i < N; i++)
		        if (Points.get(i).minore(Points.get(leastY)))
		            leastY = i;

		    // swap the pivot with the first vertice
		    Vertice temp = Points.get(0);
		    Points.set(0, Points.get(leastY));
		    Points.set(leastY, temp);
		    if (N < 3 )
		    	throw new IllegalArgumentException("Vertici non validi per la creazione di un Poligono.");
		    Vertice p = Points.get(0);

		    for(int i=1; i<Points.size()-1;++i) {
			    for(int j=i+1; j<Points.size();++j) {
			    	double order= PoligonoConvesso.ccw(p, Points.get(j) , Points.get(i));
				    if (order == 0) {
				        if (PoligonoConvesso.sqrDist(p, Points.get(j) ) < PoligonoConvesso.sqrDist(p, Points.get(i) )) {
				          	Vertice a = Points.get(j);
				        	Points.set(j, Points.get(i));
				        	Points.set(i, a);
				        }
				    }	    
				    if (order == -1) 
				    {
				    	Vertice a = Points.get(j);
			        	Points.set(j, Points.get(i));
			        	Points.set(i, a);
				    }
			    }	    
		    }
		    
		    hull.insertElementAt(Points.get(0), 0);
		    hull.insertElementAt(Points.get(1), 1);
		    hull.insertElementAt(Points.get(2), 2);

		    for (int i = 3; i < N; i++) {
		        Vertice top = hull.remove(hull.size()-1);
		        while (ccw(hull.get(hull.size()-1), top, Points.get(i)) != -1)   {
		            top = hull.remove(hull.size()-1);
		        }
		        hull.add(top);
		        hull.add(Points.get(i).clone());
		    }
		    Collections.reverse(hull);
		    if (!checkVector(hull))
		    	throw new IllegalArgumentException("Vertici non validi per la creazione di un Poligono.");
		    return hull;
		}
	  public static PoligonoConvesso crea_poligono(Vector<Vertice> V){
		  // ricevo un vettore di vertici, elimino eventuali vertici inutili, e se 3 <= N <= 20 costruisco un poligono

		   V =grahamScan(V);
		    if(V.size()>20) 
		    	throw new IllegalArgumentException("Nel modello non e' incluso un poligono di queste dimensioni.");

		   switch (V.size()) {
		     case 3:
		       return new Triangolo(V,true);   
		     case 4:
		       return new Quadrilatero(V,true);
		     case 5:
		       return new Pentagono(V,true);
		     case 6:
		       return new Esagono(V,true);
		     case 7:
		       return new Ettagono(V,true);
		     case 8:
		       return new Ottagono(V,true);
		     case 9:
		       return new Ennagono(V,true);
		     case 10:
		       return new Decagono(V,true);
		     case 11:
		       return new Endecagono(V,true);
		     case 12:
		       return new Dodecagono(V,true);
		     case 13:
		       return new Tridecagono(V,true);
		     case 14:
		       return new Tetradecagono(V,true);
		     case 15:
		       return new Pentadecagono(V,true);
		     case 16:
		       return new Esadecagono(V,true);
		     case 17:
		       return new Eptadecagono(V,true);
		     case 18:
		       return new Ottadecagono(V,true);
		     case 19:
		       return new Ennadecagono(V,true);
		     case 20:
		       return new Icosagono(V,true);

		     default:
			    	throw new IllegalArgumentException("Impossibile creare un poligono di questa dimensione.");
		     }
		}
}




public class Sequenza {
	private Object[] a; // array di Object
	private int next = 0; // indice dell’array per il prossimo inserimento
	
	public class IteratoreI implements Iteratore
    {
		
		private int current = 0;
		
		public IteratoreI()
		{
			current = 0;
		}
		
		public boolean end()
		{
			return a[current] == null;
		}
		
		public Object current()
		{
			return a[current];
		}
		
		public void next()
		{
			current++;
		}
	}
	
	public Sequenza(int dim)
	{ 
		a = new Object[dim];
	}
	
	public void add(Object x) 
	{ 
		if(next < a.length)
		{
			a[next] = x;
			next++;
		} 
	}
}
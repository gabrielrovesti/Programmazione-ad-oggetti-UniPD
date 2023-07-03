import java.lang.*;

public class Esercizio
{
	public static int numero(Sequenza s)
	{
		if(s == null) throw new SequenzaNulla("Sequenza Nulla");
		int string_count = 0;
		Sequenza.IteratoreI it = s.new IteratoreI();
		while(!it.end())
		{
			if(it.current() instanceof String)
				string_count++;
			it.next();
		}
		return string_count;
	}
  
	public static void main(String args[]){
		Sequenza s = new Sequenza(5); 
		String str = new String("pippo");
		s.add(new Integer(0)); s.add(str); 
		s.add(new Integer(0)); s.add(str);
		System.out.println(Esercizio.numero(s));

		Sequenza s1 = new Sequenza(8); 
		String str1 = new String("pippo");
		s1.add(new Integer(0));
		s1.add(str1);
		s1.add(new Integer(0));
		s1.add(new String("test"));
		s1.add(new Double(3.14));
		s1.add(new String("test1"));
		System.out.println(Esercizio.numero(s1));
	}
	
}
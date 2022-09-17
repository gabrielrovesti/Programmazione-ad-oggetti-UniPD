public class Test
{
	public static void main(String args[])
	{	
		Orario o = null;
		Orario o1 = null;
		DataOra d = null;
		DataOra d1 = null;
		try{
			o = new Orario(20,0);
			o1 = new Orario(19,0);
			d = new DataOra(20,9,2012);
			d1 = new DataOra(20,7,2015);
		}catch (Ecc e)
		{
			System.out.println(e.getReason());
		}
		
		DataOra.stampa(o);
		System.out.println("Sera? " + o.sera());
		System.out.println("Minore? " + o1.minore(o));
		System.out.println("Equals? " + (o.Equals(o1)));
		System.out.println("----------------------");
		System.out.println("1215? " + (d.agosto1215()));
		System.out.println("Minore? " + (d.minore(d1)));
		d1.setOre(20);
		System.out.println("Sera? " + (d1.sera()));
		DataOra.stampa(d1);
	}
}
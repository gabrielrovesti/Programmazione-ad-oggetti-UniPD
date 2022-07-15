public class DataOra extends Orario
{
	private int giorno;
	private int mese;
	private int anno;
	
	public DataOra()
	{
		super();
		giorno = mese = 1;
		anno = 2004;
	}
	
	public DataOra(int g, int m, int a) throws Ecc
	{
		super(12,0);
		if(g < 0 || m < 0 || a < 0) throw new Ecc("data");
		giorno = g;
		mese = m;
		anno = a;
	}
	
	public boolean agosto1215()
	{
		try
		{
			Orario o = new Orario(Ore(), Minuti(), Secondi());
			int current_time = orarioToSec(o);
			int a = 12 * 3600;
			int b = 15 * 3600;
			return mese == 8 && current_time >= a && current_time <= b;
		}catch (Ecc e)
		{
			System.out.println(e.getReason());
		}
		return false;
	}
	
	public boolean sera()
	{
		return super.sera() && (mese == 7 || mese == 8);		
	}
	
	public boolean minore(DataOra r)
	{
		if(anno < r.anno) return true;
		if(anno == r.anno)
		{
			if(mese < r.mese) return true;
			if(mese == r.mese){
				if(giorno < r.giorno) return true;
			}
		}
		return false;
	}
	
	public static void stampa(Orario r)
	{
		if(r instanceof DataOra){
			DataOra d = (DataOra)r;
			System.out.println(d.giorno + "/" + d.mese + "/" +  d.anno + " " + d.Ore() + ":" + d.Minuti() + ":" + d.Secondi());
		}
		else
			System.out.println(r.Ore() + ":" + r.Minuti() + ":" + r.Secondi());
	}
}

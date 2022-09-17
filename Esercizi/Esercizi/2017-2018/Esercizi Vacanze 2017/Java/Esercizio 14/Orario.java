public class Orario
{
	private int ore;
	private int minuti;
	private int secondi;
	
	public Orario()
	{
		ore = minuti = secondi = 0;
	}
	
	public Orario(int h, int m) throws Ecc
	{
		if(h < 0 || m < 0) throw new Ecc("orario");
		ore = h;
		minuti = m;
		secondi = 0;
	}
	
	public Orario(int h, int m, int s) throws Ecc
	{
		this(h,m);
		if(s < 0) throw new Ecc("orario");
		secondi = s;
	}
	
	public int Ore()
	{
		return ore;
	}
	
	public void setOre(int n)
	{
		ore = n;
	}
	
	public int Minuti()
	{
		return minuti;
	}
	
	public void setMinuti(int n)
	{
		minuti = n;
	}
	
	public int Secondi()
	{
		return secondi;
	}
	
	public void setSecondi(int n)
	{
		secondi = n;
	}
	
	public int orarioToSec(Orario o)
	{
		return o.ore * 3600 + o.minuti * 60 + o.secondi;
	}
	
	public boolean minore(Orario r)
	{
		return orarioToSec(this) <= orarioToSec((Orario)r);
	}
	
	public boolean sera()
	{
		int a = 19 * 3600;
		int b = 23 * 3600 + 59 * 60 + 59;
		return orarioToSec(this) >= a && orarioToSec(this) <= b;
	}
	
	public boolean Equals(Object r)
	{
		if(r != null && r.getClass() == getClass())
			return orarioToSec(this) == orarioToSec((Orario)r);
		return false;
	}
}
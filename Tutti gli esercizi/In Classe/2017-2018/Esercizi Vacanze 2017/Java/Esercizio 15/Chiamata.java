public class CreditoEsaurito extends Exception
{
	public String getReason()
	{
		return "Credito esaurito!";
	}
}

public class Chiamata
{
	private String numero_chiamato;
	private int durata_sec;
	private double costo_chiamata;
	
	public Chiamata(String n, int d)
	{
		numero_chiamato = n;
		durata_sec = n;
	}
	
	public double costo_chiamata()
	{
		return cost_chiamata;
	}
	
	public int durata_sec()
	{
		return durata_sec;
	}
	
	public String numero_chiamato()
	{
		return numero_chiamato;
	}
	
	public void printInfo()
	{
		System.out.println("Numero chiamato: " + numero_chiamato + " per: " + durata_sec + 
		" secondi " + "al costo di " + costo_chiamata);
	}
}

public abstract class AbbonamentoR
{
	private double creditoResiduo;
	
	public abstract int costo(Chiamata c)
	{
		return c.costo_chiamata();
	}
	
	public double disponibile()
	{
		return creditoResiduo;
	}
	
	public double addebita(Chiamata c) throws CreditoEsaurito
	{
		if(c.cost_chiamata() > creditoResiduo){
			creditoResiduo = 0;
			throw new CreditoEsaurito();
		}else{
			creditoResiduo -= c.costo_chiamata();
		}
		return c.cost_chiamata();
	}
}

public Flat extends AbbonamentoR
{
	
	public double costo(Chiamata c)
	{
		return 10 * c.durata_sec() / 60; 
	}
}

public EvenOdd extends AbbonamentoR
{
	
	public double costo(Chiamata c)
	{
		if(Integer.ParseInt(c.numero_chiamato()) % 2 == 0)
			return 15 * c.durata_sec() / 60;
		else
			return 5 * c.durata_sec() / 60;
	}
}
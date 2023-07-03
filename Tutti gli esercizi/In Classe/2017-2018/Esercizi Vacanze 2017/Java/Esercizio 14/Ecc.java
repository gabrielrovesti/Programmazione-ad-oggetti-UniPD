class Ecc extends Exception
{
	String reason;
	
	public Ecc(String s)
	{
		if(s.equals("orario"))
			reason = "orario";
		else if(s.equals("data"))
			reason = "data";
	}
	
	public String getReason()
	{
		return reason;
	}
}
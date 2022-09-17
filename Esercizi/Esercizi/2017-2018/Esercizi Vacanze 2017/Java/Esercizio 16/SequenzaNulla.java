class SequenzaNulla extends RuntimeException
{
	String reason;
	
	public SequenzaNulla(String s)
	{
		reason = "Sequenza nulla";
	}
	
	public String getReason()
	{
		return reason;
	}
}
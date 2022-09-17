public class Controllata extends Exception {}
public class NonControllata extends RunTimeException {}

public class C {
    // esercizio 11
    public static Object Fun(Collection c) throws Controllata {
	  if(c == null) throw new Controllata();
	  int i = c.size();
	  if(c instanceof Vector && i>2) return ((List)c).get(1);
	  if(c instanceof LinkedList && i>0) return ((LinkedList)c).removeFirst();
	  throw new NonControllata();
    }
    
    // esercizio 10
    public static void Fun(AbstractButton ab) {
	  if(ab instanceof JButton)
	      if(ab instanceof BasicArrowButton) 
		  ((BasicArrowButton)ab).setDirection(SwingConstants.NORTH);
	      else ab.setText("pippo");
    }
}
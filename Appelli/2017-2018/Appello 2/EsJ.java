interface X { public void f(); }
	
interface Y { public char g(); }

interface Z extends X { public void h(); }

class A implements Y, Z {
	public void f() { System.out.print("A.f() "); }
	public char g() { System.out.print("A.g() "); return 'A'; }
	public void h() { System.out.print("A.h() "); }
	public void m() { System.out.print("A.m() "); }
}

class B implements X {
	public void f() { System.out.print("B.f() "); }
}

class C extends B implements Y {
	public void f() { System.out.print("C.f() "); }
	public char g() { System.out.print("C.g() "); return 'C'; }
}

class D extends A {
	public char g() { System.out.print("D.g() "); return 'D'; }
	public void h() { System.out.print("D.h() "); }
}



public class EsJ{
	
	public static void main(String args[]) {		
	
		//X x = new Z(); x.f(); // NON COMPILA

		//Z z = new A(); z.f(); z.m(); // NON COMPILA

		//Y y = new C(); X x = (B)y; x.f(); y.g(); // C.f() C.g()

		//Y y = new A(); A a = new D(); a.h(); X x = (D)a; a.g(); y = a; y.g(); // D.h() D.g() D.g()

		//Z z = new A(); Y y = (D)z; y.g(); // ERRORE RUNTIME

		//B b = new C(); b.f(); A a = (A)b; a.f(); // NON COMPILA

		//Z z = new D(); ((A)z).h(); Y y = z; y.g(); // NON COMPILA

		//Y y = new D(); ((Z)y).h(); X x = (A)y; x.f(); // D.h() A.f()

		//X x = new B(); Y y = new C(); C c1 = (C)x; C c2 = (C)y; c1.g(); c2.g(); // ERRORE RUNTIME;

		//Y y = new D(); ((A)y).m(); ((D)y).m();	 // A.m() A.m()
		System.out.println();
	}
}

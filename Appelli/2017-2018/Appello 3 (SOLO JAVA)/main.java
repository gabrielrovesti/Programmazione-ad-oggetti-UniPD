
package main2;

class A {
	public void print(String s) {System.out.print(s+" ");}
	public void m1() {print("A.m1"); m2();}
	public void m2() {print("A.m2");}
	
}
class B extends A {
	public void m2() {print("B.m2");}
	public void m3() {print("B.m3");}
}
class C extends A {
	public void m1() {print("C.m1");}
	public void m2() {print("C.m2"); m1();}
}
class D extends C {
	public void m1() {super.m1(); print("D.m1");}
	public void m3() {print("D.m3");}
}	


public class main {
	public static void main(String[] args) {
		A ref1 =new B(); A ref2=new D(); B ref3=new B();
		C ref4=new C(); C ref5= new D(); Object ref6 = new C();	
		
		/*************SOLUZIONI IN BASSO************/
		ref1.m1();
		System.out.println();
		ref2.m1();
		System.out.println();
		ref4.m1();
		System.out.println();
		ref5.m1();
		System.out.println();
		ref6.m1();
		System.out.println();
		ref1.m2();
		System.out.println();
		ref2.m2();
		System.out.println();
		ref3.m2();
		System.out.println();
		ref4.m2();
		System.out.println();
		ref6.m2();
		System.out.println();
		ref3.m3();
		System.out.println();
		ref5.m3();
		System.out.println();
		((B)ref1).m3();
		System.out.println();
		((D)ref4).m3();
		System.out.println();
		((D)ref5).m3();
		System.out.println();
		((B)ref2).m3();
		System.out.println();
		((C)ref2).m2();
		System.out.println();
		((D)ref6).m2();
		/*************SOLUZIONI IN BASSO************/
	}
	
}
/*
SOLUZIONI:
1) Am1 Bm2
2) Cm1 Dm1
3) Cm1
4) Cm1 Dm1
5) NON COMPILA
6) Bm2
7) Cm2 Cm1 Dm1
8) Bm2
9) Cm2 Cm1
10) NON COMPILA	
11) Bm3
12) NON COMPILA	
13) Bm3
14) ECCEZIONE
15) Dm3
16) ECCEZIONE
17)	Cm2 Cm1 Dm1
18) ECCEZIONE






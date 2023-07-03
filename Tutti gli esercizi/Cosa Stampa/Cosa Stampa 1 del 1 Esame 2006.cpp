#include <iostream>
using namespace std;

class A { 
	public: A() {cout << "A ";} 
};

class B: virtual public A { 
	public: B() {cout << "B ";} 
};

class C: virtual public A { 
	public: C(): A() {cout << "C ";} 
};

class D: virtual public B, virtual public C { 
	public: D(): C(), B() {cout << "D ";} 
};

/****************************************
 1
 
 class E: public D { 
 public: E(): B() {cout << "E ";}
 }; 
 
 class F: virtual public E {
 public: F() {cout << "F ";}
 };
 
 
 A B C D E F

 *****************************************/
 
/****************************************
 2
 
 class E: public D { 
 public: E(): B() {cout << "E ";}
 }; 
 
 class F: public E {
 public: F() {cout << "F ";}
 };
 
 
 A B C D E F

/*****************************************/

/****************************************
 3

 
 class F: public B, virtual public C {
 public: F() {cout << "F ";}
 };
 
 A C B F

/*****************************************/

/****************************************
 4
 
 class E: public B { 
 public: E() {cout << "E ";}
 }; 
 
 class F: public E, virtual public C {
 public: F() {cout << "F ";}
 };

 A C B E F 
 
/*****************************************/


/****************************************
 5
 
 class E: virtual public B { 
 public: E() {cout << "E ";}
 }; 
 
 class F: public E, virtual public C {
 public: F() {cout << "F ";}
 };

 A B C D E F

/*****************************************/



/****************************************
 6
 
 class E: public B { 
 public: E() {cout << "E ";}
 }; 
 
 class F: virtual public E, virtual public C {
 public: F() {cout << "F ";}
 };

 A B E C F
 
 /*****************************************/

int main(){

	F f;
	return 0;

}


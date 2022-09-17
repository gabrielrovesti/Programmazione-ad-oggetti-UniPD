#include <iostream>
using namespace std;

template<class T1, class T2=Z>
class C
{
public:
	T1 x; //x->int
	T2 *p //p= Z*
};


template<class T1, class T2>
void fun (C<T1, T2> *q)
{
	++(q->p);
	
	if (TRUE==FALSE) cout<< ++(q->x)
		else cout << q->p;
	
	(q->x)++;
	
	if (*(q->p)==(q->x)) { *(q->p)=(q->x); }
	
	T1* PTR = &(q->x);
	T2 t2 = q->x;
}


class Z
{
	int operator++()
	int operator++(int)
	bool operator== (const Z&)
	Z(int K=0) {};

}


int main () 
{
	C<Z> C1;
	fun (&C1);
	C<int> C2;
	fun (&C2);
}

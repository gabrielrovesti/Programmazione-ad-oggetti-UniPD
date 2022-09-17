#include <cmath>
#include "polynomial.h"
using namespace std;
Polynomial::SmartP::SmartP (Polynomial::Monomial* p = 0): 
	pointer(p)
{
	if (pointer) 
		pointer->references++;
}
Polynomial::SmartP::SmartP (const Polynomial::SmartP& p): 
	pointer(p.pointer) 
{ 
	if (pointer) 
		pointer->references++;
}
Polynomial::SmartP& Polynomial::SmartP::operator=(const Polynomial::SmartP& p){
	if (this != &p){
		Monomial* m = pointer;
		pointer = p.pointer;
		if (pointer)
			pointer->references++;
		if (m) {
			m->references--;
			if (m->references == 0 ) 
				delete m;
		}
	}
	return *this;
}
Polynomial::Monomial& Polynomial::SmartP::operator*() const { 
	return const_cast<Monomial&>(*pointer); 
}
Polynomial::Monomial* Polynomial::SmartP::operator->() const { 
	return const_cast<Monomial*>(pointer); 
}
bool Polynomial::SmartP::operator==(const Polynomial::SmartP& p) const { 
	return pointer == p.pointer; 
}
bool Polynomial::SmartP::operator!=(const Polynomial::SmartP& p) const { 
	return pointer != p.pointer; 
}
Polynomial::SmartP::~SmartP(){ 
	if (pointer){
		pointer->references--;
		if (pointer->references==0) 
			delete pointer; 
	}
}

Polynomial::Monomial::Monomial (number c = 0, number e = 0, const SmartP& p = 0): 
	coefficient(c), exponent(e), next(p), references(0) {}

Polynomial::Polynomial () : first(0){}
Polynomial::Polynomial (number c) : first(0) {
	first = new Monomial(c,0);
}
Polynomial::Polynomial (number c, number e) : first(0) {
	first = new Monomial(c,e);
}

Polynomial::Polynomial (const Polynomial& p) : first(0) {
	SmartP children, parent = p.first;
	while(parent!=0){
		if (children==0)
			children = first = new Monomial(parent->coefficient, parent->exponent);
		else
			children = children->next = new Monomial(parent->coefficient, parent->exponent);
		parent = parent->next;
	}
}

void Polynomial::longDivision(const Polynomial&  p1, const Polynomial& p2, bool remainder=false){
	Polynomial p1c(p1), extra;
	SmartP one = p1c.first, two = p2.first, three = first;
	while(one!=0 && one->exponent >= two->exponent){
		number c = one->coefficient / two->coefficient, 
			e = one->exponent - two->exponent;
		if (three==0)
			three = first = new Monomial(c, e);
		else
			three = three->next = new Monomial(c, e);
		number delta = one->coefficient-c*two->coefficient;
		if (delta!=0){
			Polynomial deltaP(delta, one->exponent);
			extra = extra + deltaP;
			p1c = p1c - (Polynomial(c,e)*p2)-deltaP;
		}else{
			p1c = p1c - (Polynomial(c,e)*p2);
		}
		one = p1c.first;
	}
	if (remainder)
		*this = p1c + extra;
}

Polynomial Polynomial::operator^(const number e) const {
	Polynomial result(1);
	for (int i=0; i<e; i++)
		result = result*(*this);
	return result;
}

Polynomial operator*(const Polynomial& p1, const Polynomial& p2) {
	Polynomial result;
	Polynomial::SmartP one = p1.first;
	while (one!=0){
		Polynomial::SmartP two = p2.first;
		while (two!=0){
			Polynomial::SmartP three = result.first, prev;
			number c = one->coefficient * two->coefficient,
			e = one->exponent + two->exponent;
			if (three==0 || three->exponent < e){
				three = result.first = new Polynomial::Monomial(c, e);
			}else{
				if (c!=0){
					while (three!=0 && three->exponent > e){
						prev = three;
						three = three->next;
					}			
					if (three!=0 && three->exponent==e)
						three->coefficient += c;
					else
						prev->next = new Polynomial::Monomial(c, e, 0);
				}
			}
			two = two->next;
		}
		one = one->next;
	}
	return result;
}
Polynomial operator/(const Polynomial& p1, const Polynomial& p2) {
	Polynomial result;
	result.longDivision(p1, p2);
	return result;
}
Polynomial operator%(const Polynomial& p1, const Polynomial& p2) {
	Polynomial result;
	result.longDivision(p1, p2, true);
	return result;
}

Polynomial operator+(const Polynomial& p1, const Polynomial& p2) {
	Polynomial result;
	number c = 0, e = 0;
	Polynomial::SmartP one = p1.first, two = p2.first, three = result.first;
	while (one!=0 || two!=0){
		if (one!=0 && two!=0){
			if (one->exponent > two->exponent) {
				c = one->coefficient, e = one->exponent;
				one = one->next;
			} else if (one->exponent == two->exponent) {
				c = one->coefficient+two->coefficient, e = one->exponent;
				one = one->next;
				two = two->next;
			} else {
				c = two->coefficient, e = two->exponent;
				two = two->next;
			}
		} else if (one==0){
			c = two->coefficient, e = two->exponent;
			two = two->next;
		}else if (two==0){
			c = one->coefficient, e = one->exponent;
			one = one->next;
		}
		if (c!=0){
			if (three==0)
				three = result.first = new Polynomial::Monomial(c, e);
			else
				three = three->next = new Polynomial::Monomial(c, e);
		}
	}
	return result;
}
Polynomial operator-(const Polynomial& p1, const Polynomial& p2){
	Polynomial result = p1 + (-p2);
	return result;
}

Polynomial Polynomial::operator-() const {
	Polynomial result(*this);
	SmartP aux = result.first;
	while(aux!=0){
		aux->coefficient = -aux->coefficient;
		aux = aux->next;
	}
	return result;
}

number Polynomial::operator()(const number n) const {
	SmartP aux = first;
	number result = 0;
	while (aux!=0){
		result += aux->coefficient * pow(n, aux->exponent);
		aux = aux->next;
	}
	return result;
}

bool operator==(const Polynomial& p1, const Polynomial& p2){
	Polynomial::SmartP one = p1.first, two = p2.first;
	while (one!=0){
		if (two==0){
			return false;
		}else{
			if (one->coefficient != two->coefficient || one->exponent != two->exponent )
				return false;
		}
		one = one->next;
		two = two->next;
	}
	return true;
}

bool operator!=(const Polynomial& p1, const Polynomial& p2){
	return !operator==(p1, p2);
}

ostream& operator<<(ostream& os, const Polynomial& p){
	Polynomial::SmartP aux = p.first;
	if (aux == 0)
		os << 0;
	while(aux!=0){
		if ((aux!=p.first || aux->coefficient<0 ) && aux->coefficient!=0)
			os << ((aux->coefficient>=0) ? " + " : " - ");
		if ((abs(aux->coefficient)!=1 || aux->exponent==0) && 
			(aux->coefficient!=0 || aux==p.first) )
			os << abs(aux->coefficient);
		if (aux->coefficient!=0 && aux->exponent!=0){
			os << "x";
			if (aux->exponent!=1)
				os << "^" << aux->exponent;
		}
		aux = aux->next;
	}
	return os;
}


int main(){
	
	Polynomial X(1,1);
	cout << "X = " << X << "\n";
	Polynomial Z(3,4);
	cout << "Z = " << Z << "\n";
	Polynomial T(X);
	cout << "T = " << T << "\n";
	T = Z;
	cout << "T = " << T << "\n";
	cout << "X = " << X << "\n";
	
	Polynomial Q = 3*X + 2*X*X - X*X*X + 7*(X^4);
	cout << "Q = " << Q << "\n";
	Polynomial P = 2*(X^2);
	cout << "P = " << P << "\n";
	
	cout << "Q*Q = " << Q*Q << "\n";
	cout << "Q/P = " << Q/P << "\n";
	cout << "Q%P = " << Q%P << "\n";
	cout << "Q^3 = " << (Q^3) << "\n"; // wrong result in the book: Q^4
	
	cout << "Q(3) = " << Q(3) << "\n"; 
 	if (P == 2*(X^2)) cout << "P(3) = " << P(3) << "\n"; // parentheses needed: * before == before ^
	if (P != Q) cout << Q(P(3)) << "\n"; 
	
}
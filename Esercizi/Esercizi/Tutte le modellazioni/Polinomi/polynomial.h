#include <iostream>
using namespace std;

typedef int number;

class Polynomial {
	private:
		class Monomial;
		class SmartP{
			public:
				Monomial* pointer;
				SmartP (Monomial*);
				SmartP (const SmartP&);
				SmartP& operator=(const SmartP&);
				Monomial& operator*() const;
				Monomial* operator->() const;
				bool operator==(const SmartP&) const;
				bool operator!=(const SmartP&) const;
				~SmartP();
		};
		class Monomial {
			public:
				int references;
				number coefficient, exponent;
				SmartP next;
				Monomial (number, number, const SmartP&);
		};
		SmartP first;
		
		void longDivision(const Polynomial&, const Polynomial&, bool);
			
	public:
		Polynomial ();
		Polynomial (number);
		Polynomial (number, number);
		Polynomial (const Polynomial&);
		Polynomial operator^(number) const;
		friend Polynomial operator*(const Polynomial&, const Polynomial&);
		friend Polynomial operator/(const Polynomial&, const Polynomial&);
		friend Polynomial operator%(const Polynomial&, const Polynomial&);
		friend Polynomial operator+(const Polynomial&, const Polynomial&);
		friend Polynomial operator-(const Polynomial&, const Polynomial&);
		Polynomial operator-() const;
		friend bool operator==(const Polynomial&, const Polynomial&);
		friend bool operator!=(const Polynomial&, const Polynomial&);
		number operator()(const number) const;
		friend ostream& operator<<(ostream&, const Polynomial&);
};
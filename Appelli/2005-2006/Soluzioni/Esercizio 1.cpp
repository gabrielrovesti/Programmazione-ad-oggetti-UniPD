#include <iostream>
#include <vector>
using namespace std;

template <class T, int size> class C;

template <class T, int size>
ostream& operator<<(ostream& os, const C<T, size>& c); 

template <class T=string, int size=1>
class C{
	friend ostream& operator<< <T,size>(ostream& , const C<T, size>&);
private:

	class Multinfo{
	public:
		T info;
		int m; //molteplicità
		Multinfo(const T& i= T(), int k = 1): info(i), m(k) {if(m<1) m=0;}
	};
	
	Multinfo* array;

public:
	C(const T& t=T(),int s=1): array(new Multinfo[size](t,s)){}
	
	C(const C& x) : array(new Multinfo[size]){
		for(int i=0; i<size; ++i) array[i] = x.array;
	}
	
	~C() {delete[] array;}
	
	C& operator=(const C& x){
		if (this != &x) {
			// delete[] array; // non serve avendo la ridefinizione del distruttore
			for (int i=0; i<size; ++i) {
				array[i] = x.array[i];
			}
			return *this;
		}
	}
	
	T* operator[](int k) const {
		return (k>=0 && k<size)? &(array[k].info) : 0;
	}
	
	int occorrenze(const T& t) const {
		int sum=0;
		for(int i=0; i<size; ++i)
			if (array[i].info == t) sum+=array[i].mult;
		return sum;
	}
	
};

template <class T, int size>
ostream& operator<<(ostream& os, const C<T, size>& c) {
	for (int i=0; i<size; ++i) {
		os << " Valore: " << c.array[i].info << " Molteplicità: " << c.array[i].mult;
	}
	return os;
}
	



int main(){

	return 0;

}
	
		
				
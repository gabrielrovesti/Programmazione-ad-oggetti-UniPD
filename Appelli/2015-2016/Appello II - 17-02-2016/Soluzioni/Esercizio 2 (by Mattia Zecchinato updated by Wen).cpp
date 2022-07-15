#include <iostream>

using namespace std;

class Empty{
public:
	Empty();
};

template <class T>
class Array{
	friend ostream& operator<<(ostream& os,const Array<T>&);	
private:
	
	T* x;
	int size;
	int capacity;
	
	static T* copia(T* j, int y, int z){
		T* a = new T[z];
		for (int i=0; i<y; i++)
			a[i]=j[i];
		return a;
	}
public:
	Array(int k=0, const T& t = T()): x(0), size(k), capacity(k*2){
		if (k) {
			x=new T[k*2];
			for(int i=0; i<size; i++)
				x[i]=t;
		}
	}
	
	Array(const Array& a): x(copia(a.x,a.size,a.capacity)), size(a.size), capacity(a.capacity) {}
	
	~Array() {delete [] x;}
	
	Array& operator=(const Array& a){
		if (this != &a) {
			delete [] x;
			x=copia(a.x,a.size,a.capacity);
			size = a.size;
			capacity = a.capacity;
		}
		return *this;
	}
	
	void pushBack(const T& t){
		if (size==capacity) {
			T* b=copia(x, size, capacity*2);
			delete[] x;
			x=b;// assegna i puntatori;
			capacity=capacity*2;
			x[size]=t;
			size++;
		}
		else {
			x[size]=t;
			size++;
		}
	}
	// edit, a x viene assegnato il puntatore restituito dalla funzione, ma non e' stato fatta la pulizia dello heap. 
	
	T popBack(){
		if (!size) {
			throw Empty();
		}
		else {
			T a=x[size-1];
			delete x[size-1];
			// non e' molto corretto, poiche se il tipo T non e' un puntatore non compila.
			size--;
			return a;
		}
	}
	/*
	bool operator==(const Array& a) const {
		if (size != a.size) {
			return false;
		}
		for (int i=0; i<size; i++) {
			return false;
		}
		return true;
		// per definizione due cose sono uguali se sono uguali in tutto per tutto, quindi bisogna confrontare anche i contenuti del buffer. 
	}*/
	bool operator==(const Array& t)const {
		bool uguale=true;
		if(size!= t.size || capacity!=t.capacity) uguale=false;
		for( int i=0; i<size&& uguale; i++){
			if(buffer[i]!=a.buffer[i])
				uguale=false;
		}
		return uguale;
	}
	
};

template<class T>
ostream& operator<<(ostream& os, const Array<T>& a){
	for (int i=0; i<a.size; i++) {
		os << (a.x)[i] << " ";
	}
	return os;
}

int main(){
}





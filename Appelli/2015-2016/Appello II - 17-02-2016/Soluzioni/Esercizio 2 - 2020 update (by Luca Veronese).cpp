/*
La presente versione è stata condivisa poiché secondo l'autore le precedenti soluzioni caricate su MEGA
 contenevano alcune criticità (alcune funzioni producevano un risultato diverso da quanto atteso da un contenitore della STL).
Il codice all'interno del main() non era richiesto dalla consegna,
 è stato aggiunto per rendere illustrare il comportamento di alcune funzioni.
Il seguente codice non è mai stato presentato ad un esame
 né è mai stato corretto dal professore, perciò potrebbe non essere esente da errori.


Autore: Luca Veronese
Gentilmente revisionato da Egon Galvani
*/

#include<iostream>

template<class T>
class Array;

template<class T>
std::ostream& operator<<(std::ostream&, const Array<T>&);

template<class T>
class Array {
friend std::ostream& operator<< <>(std::ostream&, const Array<T>&);
private:
	unsigned int size;
	unsigned int capacity;
	T* arr; //INV: arr==nullptr sse size==capacity==0
	
	/*PRE p1 è un array possibilmente vuoto, p2 conterrà l'array da ritornare,
	s è la dimensione di p2, c è la capacità di p2, s<=c
	(N.B. quando la funzione è invocata da costr. di copia o assegnazione s==c,
	quando invocata da push_back s<c)*/
	static T* copy(T* p1, unsigned int s, unsigned int c) {
		if (c>0) {
			T* p2 = new int[c];
			for (int i=0; i<s; ++i) {
				p2[i]=p1[i];
			}
			return p2;
		} //else if (c==0)
		return nullptr; //perché arr==nullptr sse size==capacity==0
	}
	/*POST ritorna un array == p1 (che P1 sia vuoto o meno). 
	N.B. due array sono uguali se size e tutti gli oggetti sono uguali,
	non necessariamente capacity, si veda più in basso operator== */
public:
	//Array() non necessario, invocazione senza parametri gestita da funzione sottostante 
	Array(int k=0, const T& t=T())
	 : size(k>0 ? k : 0), capacity(size), arr(k>0 ? new int[size] : nullptr) {
		 //arr==nullptr sse size==capacity==0. 
		 //(N.B dopo costruzione/costr di copia /assegnazione size==capacity,
		 //la capacity può essere raddoppiata solo dopo un inserimento se necessario)
		for (int i =0; i < k; ++i) {
			arr[i] = t;
		}
	}
	
	Array(const Array& p): 
		size(p.size), capacity(p.size), arr(copy(p.arr, p.size, p.size)) {}
		
	Array& operator=(const Array& p) {
		if (this != &p) {
			delete[] arr;
			capacity = size = p.size;
			arr = copy(p.arr, p.size, p.size); 
			//equivalente a arr = copy(p, size, capacity);
		}
		return *this;
	}
	
	~Array() {
		delete[] arr;
	}
	
	void pushBack(const T& t) {
		if (size == capacity) {
			if (capacity > 0) {
			    capacity *= 2;
			}
			else {
			    capacity = 1;
			}
			//(N.B. solo in questo caso si invoca copy con capacity > size !)
			T* new_arr = copy(arr, size, capacity);
			delete[] arr;
			arr = new_arr;
		}
		++size;
		arr[size-1] = t;
	}
	
	T popBack() {
		if (!size) {
			return T();
			//SBAGLIATO. La consegna richiederbbe un'eccezione, 
			//ma l'argomento non è stato affrontato nel corso dell'aa 2019-20
		}
		else {
			/*
			--size;
			return arr[size];
			funziona egregiamente ma è abominevole*/
			T temp = arr[size-1];
			--size;
			return temp;
		}
	}
	
	bool operator==(const Array<T>& a) {
		//array di tipi diversi non possono essere confrontati
		//due array possono essere uguali se le capacity sono diverse (!)
		if (size != a.size) {
			return false;
		}
		for (int i = 0; i < size; ++i) {
			if (arr[i] != a.arr[i]) {
				return false;
			}
		}
		return true;
	}
};

template<class T>
std::ostream& operator<<(std::ostream& os, const Array<T>& a) {
	for (int i=0; i<a.size; ++i) {
		os << a.arr[i] << ' ';
	}
	return os;
}

int main() {
	Array<int> a(7,1), b(5), c(b), d, e(d), f;
	f=d;
	d=b;
	std::cout << a << std::endl;
	//1 1 1 1 1 1 1
	std::cout << d << std::endl;
	//0 0 0 0 0
	d.pushBack(3);
	std::cout << d << std::endl;
	//0 0 0 0 0 3
	std::cout << d.popBack() << std::endl;
	//3
	std::cout << d << std::endl;
	//0 0 0 0 0
	if (!(a == b) && b == c) {
		std::cout << "l'uguaglianza funziona" << std::endl;
	}
	//l'uguaglianza funziona
	e.pushBack(3);
	e.popBack();
	std::cout << e <<"uno " << (e==f) <<" due " << std::endl;
	//uno 1 due
	return 0;
}

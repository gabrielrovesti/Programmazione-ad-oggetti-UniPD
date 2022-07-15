#include <iostream>
using namespace std;


class Empty{};	//classe da lanciare quando ho un'eccezione

template<class T = int> 
class Stack{
	private:
	class Nodo{
		Nodo* precc;
		Nodo* succ;
		T info;
	
	};

	Nodo* last;

	public:
	Stack() : last(0) {}
	
	Stack(Nodo* l=0) : last(l) {}
	
	Stack(int k, const T& t)  {
		if(k>1){ 
		last = new Nodo(0 , 0, t);
			k--;
			while (k != 0) {
				Nodo* temp = last;
				last = new Nodo(temp, 0, t);
				k--;
			}
		}
	}
	
	bool isEmpty() const {
		return !last;
	}
	
	T pop(){
		if (isEmpty()) throw Empty();
		else {
			Nodo* temp = last;
			last = last->precc;
			T rit = temp->info;
			delete temp;
			return rit;
		}
	}
	
	T* top() const{
		if (isEmpty()) return 0;
		else {
			Nodo* temp = last;
			while (temp->precc != 0) {
				temp = temp->precc;
			}
			return temp;
		}
	}
	
	
	class iterator{
	public:
		Nodo* it;
		bool operator==(iterator i) const{
			return (it == i.it);
		}
		
		bool operator!=(iterator i) const{
			return (it != i.it);
		}
		
		iterator* operator[](int i) {
			if (i>0) {
				while (i>0) {
					it = it->precc;
					i--;
				}
			}
			return *this;
		}
		
		ostream& operator<<(ostream& os){
			os << it->info;
			return os;
		}
	};

};

main(){

}
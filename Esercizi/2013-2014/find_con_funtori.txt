#include <iostream>
#include <typeinfo>
using namespace std; 

template <class T>
class Container { 
  T a;
 public:
 Container(T x): a(x) {}
  // find con T::operator==
  bool find(const T& x) {
    return a == x; 
  }
  // find con uguaglianza specificata dal funtore equal
  template<class Functor>
  bool find(const T& x, Functor equal) {
    return equal(a,x);
  }
};

class LibraryItem {
 public:
  bool b; 
  int i;
  LibraryItem(bool x=0,int y=0): b(x), i(y) {}
  virtual ~LibraryItem() {} 
 
  virtual bool operator==(const LibraryItem& x) const {
    return b==x.b && i == x.i;
  } 
};

class Book: public LibraryItem {
 public:  
  double d;
  Book(bool x=0,int y=0, double z=0): LibraryItem(x,y), d(z) {}
  virtual bool operator==(const LibraryItem& x) const {
    const Book* p = dynamic_cast<const Book*>(&x);
    return  p && this->LibraryItem::operator==(x) && d==p->d;
  }
};

class Journal: public LibraryItem {
 public:
  char c;
  Journal(bool x=0,int y=0, char z=0): LibraryItem(x,y), c(z) {}
  virtual bool operator==(const LibraryItem& x) const {
    const Journal* p = dynamic_cast<const Journal*>(&x);
    return  p && this->LibraryItem::operator==(x) && c==p->c;
  }
};

// Classe di puntatori smart "polimorfi"
class SmartLibraryItem {
public:
  LibraryItem* ptr;
  SmartLibraryItem(LibraryItem* p=0): ptr(p) {}
  // operator== polimorfo
  bool operator==(const SmartLibraryItem& s) const {
    return ptr->operator==(*(s.ptr)); 
  }
  // classe annidata di funtori di uguaglianza
  class Funct {
  public:
    int field;
    Funct(int x=0): field(x) {}
    bool operator() (const SmartLibraryItem& x, const SmartLibraryItem& y) const {
      switch(field) {
      case 0: 
	return x==y;
      case 1:
	// nessun controllo di tipo dinamico
	return (x.ptr)->b == (y.ptr)->b;
      case 2:
	// controllo di tipo dinamico
	return typeid(*(x.ptr)) == typeid(*(y.ptr)) && 
	  (x.ptr)->i == (y.ptr)->i;
      case 3:
	{
	Book* p= dynamic_cast<Book*>(x.ptr); 	
	Book* q= dynamic_cast<Book*>(y.ptr); 
	return p && q && p->d == q->d;
	}
      case 4:
	{
	Journal* p= dynamic_cast<Journal*>(x.ptr); 	
	Journal* q= dynamic_cast<Journal*>(y.ptr); 
	return p && q && p->c == q->c;
	}
      default:
	return x==y;
      }
    }
  };
};

int main() {
  Book b(1,2,3); Journal j(4,0,5);
  Book b1(1,0,0); Journal j1(0,0,5);
  Container<SmartLibraryItem> c1(&b);
  cout << c1.find(SmartLibraryItem(&b)) << endl; // 1
  cout << c1.find(SmartLibraryItem(&j)) << endl; // 0
  SmartLibraryItem::Funct eq1(1);
  cout << c1.find(SmartLibraryItem(&b1),eq1) << endl; // 1
  Container<SmartLibraryItem> c2(&j); 
  cout << c1.find(SmartLibraryItem(&j1),eq1) << endl; // 0
  cout << c1.find(SmartLibraryItem(&b1),eq1) << endl; // 1
  SmartLibraryItem::Funct eq2(2);
  cout << c2.find(SmartLibraryItem(&b1),eq2) << endl; // 0
  cout << c2.find(SmartLibraryItem(&j1),eq2) << endl; // 1
  SmartLibraryItem::Funct eq3(3);
  cout << c2.find(SmartLibraryItem(&j1),eq3) << endl; // 0
}
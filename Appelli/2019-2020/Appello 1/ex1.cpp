/*
Soluzione di Ranzato all'esercizio 1
*/

template<class T>
class SmartP {
private:
  T* ptr;
public: 
  SmartP(const T* p=0): ptr(p ? new T(*p) : 0) {}

  SmartP(const SmartP& x): ptr(x.ptr ? new T(*(x.ptr)) : 0) {}

  ~SmartP() { delete ptr; }

  SmartP& operator=(const SmartP& x) {
    if(this != &x){
      delete ptr; 
      ptr = x.ptr ? new T(*(x.ptr)) : 0;
    }
    return *this;
  }

  T& operator*() const {return *ptr;}

  bool operator==(const SmartP& x) const {return ptr == x.ptr;}
};

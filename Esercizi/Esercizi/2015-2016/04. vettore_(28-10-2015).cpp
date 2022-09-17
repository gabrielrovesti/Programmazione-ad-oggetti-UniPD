/* TESTO
L'esercizio sulla classe Vettore della lezione del 28/10/2015:
Definire una classe Vettore i cui oggetti rappresentano array di interi.
Vettore deve includere un costruttore di default, l'overloading dell'uguaglianza, dell'operatore di output e dell'operatore di indicizzazione.
Deve inoltre includere il costruttore di copia profonda, l'assegnazione profonda e la distruzione profonda. */



class Vettore {
private:
  int* a; // a punta all'array "dinamico" allocato sullo heap
  int _size;
  // funzione statica privata di copia profonda
  static int* copia(const Vettore& v) {
    int* aux = new int[v._size];
    for(int j=0;j<v._size; ++j) 
      aux[j]=v.a[j];
    return aux;
  }
public:

  Vettore(int k=0, int s=0): a(new int[0]), _size(s) {
    for(int j=0; j<s; ++j) a[j]=k;
  }
  int size() const {return _size;}
  int& operator[](int i) const { return a[i]; }
  bool operator==(const Vettore& v) const {
    if(_size != v._size) return false;
      for(int j=0; j<_size; ++j) 
	if(a[j]!=v.a[j]) return false;
      return true;
  }
  // assegnazione profonda
  Vettore& operator=(const Vettore& v) {
    if(this != &v) {
      delete[] a;
      a = copia(v); 
      _size=v._size;
    }
    return *this;
  }
  // costruzione di copia profonda
  Vettore(const Vettore& v): a(copia(v)), _size(v._size) {} 
  // distruttore
  ~Vettore() { delete[] a; }

};

std::ostream& operator<<(std::ostream& os, const Vettore& v) {
  for(int i=0; i<v.size(); ++i) 
    os << v[i] << " ";
  return os;
}
class Nodo {
  friend class Tree;
private:
  Nodo(string i, Nodo* s, Nodo* d); 
  string info;
  Nodo* sx;
  Nodo* dx;
};
class Tree {
private:
  static Nodo* copia(Nodo* r) {
    if(!r) return 0;
    return Nodo(r->info,copia(r->sx),copia(r->dx));
  }
  static void distruggi(Nodo* r) {
    if(r) {
      distruggi(r->sx);
      distruggi(r->dx);
      delete r;
    }
  }
public:
  Tree& operator=(const Tree& t) {
    if(this != &t) {
      distruggi(radice);
      radice = copia(t.radice);
    }
    return *this;
  }
  ~Tree() {distruggi(radice);}
};

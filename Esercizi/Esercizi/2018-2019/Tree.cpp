class Nodo {
  friend class Tree;
private:
  Nodo(char c='*', Nodo* s=0, Nodo* d=0): info(c), sx(s), dx(d) {}
  char info;
  Nodo* sx;
  Nodo* dx;
};

class Tree {
public:
  Tree(): root(0) {}
  Tree(const Tree& t): root(copy(t.root)) {}
  Tree& operator=(const Tree& t) {
    if(this != &t) {
      destroy(root);
      root = copy(t.root);
    }
    return *this;
  }
  ~Tree() {destroy(root);}
private:
  Nodo* root;
  static Nodo* copy(Nodo* r) {
    // caso base r==0
    if(!r) return 0;
    // r != 0, passo induttivo
    return new Nodo(r->info,copy(r->sx),copy(r->dx));
  }

  static void destroy(Nodo* r) {
    // caso base: se r==0, nulla da fare
    if(r) { // r != 0, passo induttivo
      destroy(r->sx);
      destroy(r->dx);
      delete r;
    }
  }
};

int main() {
  Tree t;
}

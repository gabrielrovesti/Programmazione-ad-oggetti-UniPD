#include <iostream>

/*
Si chiede di ridefinire assegnazione, costruttore di copia e 
distruttore come assegnazione, copia e distruzione profonda
*/

class Nodo{
    friend class Tree;
    private:
    Nodo(char c='*', Nodo *s=0, Nodo*d=0): info(c), sx(s), dx(d) {}
    char info;
    Nodo* sx;
    Nodo* dx;
};


class Tree{

    private:
    Nodo* root;
    static Nodo* copia(Nodo*);
    static void distruggi(Nodo*r);

    public:
    Tree(): root(0) {}
    Tree& operator=(const Tree&);
    Tree(const Tree&);
    ~Tree();   //il controllo if(root) è completamente opzionale, ma evita una chiamata in più nel momento in cui sia vuoto
};

Tree& Tree::operator=(const Tree& t){
        if(this != &t){
            distruggi(root);
            //delete r non basta, perché in questa versione distruggerebbe solamente la radice dell'albero
            root = copia(t.root);     //copia l'albero puntato da root
        }
        return *this;
}

Nodo* Tree::copia(Nodo* r){
        if(r == nullptr)    return nullptr;
        return new Nodo(r->info, copia(r->sx), copia(r->dx));
}

void Tree::distruggi(Nodo*r){
    if(r != nullptr){
        distruggi(r->sx);
        distruggi(r->dx);
        delete r;
    }
}

Tree::Tree(const Tree& t): root(copia(t.root)) {}

Tree::~Tree(){
    delete root;
}

int main(){
    Tree t1, t2;
    t1=t2;
    Tree t3=t2;
}
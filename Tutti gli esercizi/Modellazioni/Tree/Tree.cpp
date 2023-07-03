#include <iostream>

/*
Alberi binari ricorsivamente definiti di char.
Si chiede di ridefinire assegnazione, costruttore di copia e 
distruttore come assegnazione, copia e distruzione profonda.
Scrivere esplicitamente eventuali dichiarazioni friend
che dovessero essere necessarie.
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
        static void distruggi(Nodo*);
        static void stampa(Nodo*);
    public:
        Tree(): root(0){}
        Tree(Nodo* r): root(r) {}
        Tree& operator=(const Tree&); //assegnazione profonda
        Tree(const Tree&); //copia profonda
        ~Tree(); //distruttore standard
};

Tree& Tree::operator=(const Tree& t){
    // La struttura dell'operatore di assegnazione
    // (1) controllo se l'oggetto costante sia diverso 
    // da this
    // (2) se diverso, distruggo in modo profondo
    // (3) copio in modo profondo
    /*
    if(this != &t){
        if(root) delete root;
        root = new Nodo(t.root->info);
        if(t.root->sx) root->sx = new Nodo(t.root->sx->info);
        if(t.root->dx) root->dx = new Nodo(t.root->dx->info);
    }
    return *this;
    */
    if(this != &t){ //passo (1)
        distruggi(root); //passo (2)
        root = copia(t.root); //passo (3)
    }
    return *this;
}

void Tree::stampa(Nodo* r){
    if(r){
        std::cout << r->info << " ";
        stampa(r->sx);
        stampa(r->dx);
    }
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

// Modo 1
Tree::Tree(const Tree& t): root(copia(t.root)){}
// Modo 2
// La struttura del costruttore di copia
// (1) copio in modo profondo
/*
root = new Nodo(t.root->info);
if(t.root->sx) root->sx = new Nodo(t.root->sx->info);
if(t.root->dx) root->dx = new Nodo(t.root->dx->info);
*/

//Modo 3
//root = copia(t.root); //passo (1)

Tree::~Tree(){
    distruggi(root);
    //delete root;
}

int main(){
    Tree t1, t2;
    t2 = t1;
    Tree t3(t2);
    return 0;
}
//Esercizio 1
C(int) UNO
C(int) D(int) DUE
Cc Pippo C(int) D(int) Pluto ~C() TRE
Cc Pippo C(int) D(int) Pluto 7 ~D() ~C() ~C() QUATTRO
7 ~D() ~C() 3 ~D() ~C() ~C()

//Esercizio 2
Z() UNO
A() Z() C0-1 A() 1 B() D() DUE
TRE
A() Z() C0-1 1 B() Z(int) 2 D(int,1Z) E() 1 F(1Z) QUATTRO
A(int,int) Z() C0-1 3 B(int) D() E() 2 F() CINQUE
A() Z() Z() C0-1 Z(int) 2 D(int,1Z) SEI
SETTE
A() Z() Z() C0-1 A() Z() C0-1 E() A() Z() C0-1 OTTO

//Esercizio 3
int Fun(vector<B*>& v){
    int tot=0;
    for(auto it=v.begin(); it!=v.end(); ++it)
        if((typeid(*v[0])) != typeid(*(*it)) && dynamic_cast<C*>(*it)) ++tot;
    return tot;
}

//Esercizio 4
A(1) A(1) A(1) A(2) 

//Esercizio 5
nodo(): next(0) {}
lista(): info(0), next(0){}
lista(const lista& l){
    if(this != &l){
        nodo*aux=l;
        info=aux.info;
        next=aux.next;
        l=aux->next;
        delete aux;
    }
}
void lista::Aggiungi_in_testa(int i){
    first=new nodo(i, first);
}
void lista::Aggiungi_in_coda(int i){
    nodo*aux=L;
    nodo*prec=0;
    while(aux && aux->info != i){
        prec=aux;
        aux=aux->next;
    }
    if(aux){
        if(!prec) first=aux->next;
        else prec->next=aux->next;
        delete aux;
    }
}


ostream& operator<<(ostream& os, lista& l){

}
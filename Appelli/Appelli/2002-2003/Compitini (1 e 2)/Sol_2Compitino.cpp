//Esercizio 1
Risposta (A)

//Esercizio 2
Risposta (D)

//Esercizio 3
F: pippo pippo G: pippo UNO
F: pippo topolino pippo G: topolino DUE
F: paperino pippo G: paperino TRE
F: paperino paperino G: paperino QUATTRO

//Esercizio 4
A(int) C(int) UNO
A() B() 1 E() DUE
A() B() A() B() TRE
A(int) B() 2 E() C(string) Z(char) D() F() QUATTRO

//Esercizio 5
Risposta (B)
Z(char) Zc A() B() 2 E() C(int) Z(char) D() Z() F(Z)

//Esercizio 6
Non compila 
error: ‘A A >::x’ is private within this context

//Esercizio 7
Risposta (A)

//Esercizio 8 - Modellazione
#include <iostream>
#include <vector>
using namespace std;
class Messaggio{
    private:
    string mess;
    public:
    string getMess() const{return mess;}
    virtual void stampaMessaggio() const=0;
    virtual ~Messaggio();
};

class Warning: public Messaggio{
    private:
    int l_g;
    int *v;
    public:
    int getl_g() const{return l_g;}
    Warning(int l): l_g(l) {
        for(int i=0; i<l_g; i++){
            v[i]=i;
        }
    }
    virtual void stampaMessaggio() const{
        Messaggio* m;
        for(int i=0; i<l_g; i++){
            cout << m->getMess() << l_g;
        }
    }
};

class Errore: public Messaggio{
    private:
    bool tipo;
    string* cat;
    int n_errori;
    int *errori;
    public:
    Errore(bool t, string* c, int ne, int *e): tipo(t), cat(c), n_errori(ne), errori(e){
        for(int i=0; i<n_errori; i++){
            if(tipo){
                errori[i]=i;
                cat[i]="Tipo";
            }
            else{
                errori[i]=i;
                cat[i]="Non tipo";
            }
        }
    }
    virtual void stampaMessaggio() const{
        Messaggio* m;
        for(int i=0; i<n_errori; i++){
            if(tipo)
            cout << m->getMess() << cat[i] << errori[i];
            else
            cout << m->getMess() << cat[i] << errori[i];
        }
    }
};

class Gestione_Messaggi{
    public:
    void stampa(Messaggio* p){
        Warning *w=dynamic_cast<Warning*>(p);
        if(w) w->stampaMessaggio();
        else{
            Errore *e=dynamic_cast<Errore*>(p);
            if(e) ey->stampaMessaggio();
        }
    }
};

int main(){
    return 0;
}
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Biglietto{
    private:
        string nome;
        bool galleria;
    protected:
        Biglietto(const Biglietto& b): nome(b.nome), galleria(b.galleria){}
        Biglietto(string n, bool g): nome(n), galleria(g) {}
        Biglietto(string n): nome(n) {}
        Biglietto() {}
        virtual ~Biglietto() {}
    public:
        string getNome() const{return nome;}
        bool getGalleria() const{return galleria;}
};

class PostoNumerato: public Biglietto{
    private:
        bool fila;
    public:
        PostoNumerato(string nome, int f):   Biglietto(nome), fila(f){}
        int getFila() const{return fila;}
};

class PostoNonNumerato: public Biglietto{
    private:
        bool prezzo_r;
    public:
        PostoNonNumerato(string nome, bool g=true, bool p=false): Biglietto(nome, g), prezzo_r(p){}
        double getPrezzo() const{return prezzo_r;}
};

class Spettacolo: public Biglietto{
    private:
        double base_pr, add_pr;
        int maxNum, maxFila;
        int posti_venduti;
        list<Biglietto*> l;
    public:
        Spettacolo(double b, double a, int mn, int mf, int pv):
        base_pr(b), add_pr(a), maxNum(mn), maxFila(mf), posti_venduti(pv) {}
        void aggiungiBiglietto(const Biglietto& b){
            Biglietto* p=const_cast<Biglietto*>(&b);
            if(dynamic_cast<PostoNonNumerato*>(p)){
                l.push_back(p);
            }
            else if(dynamic_cast<PostoNumerato*>(p)){
                if(posti_venduti < maxNum){
                    posti_venduti++;
                    l.push_back(p);
                } 
            }
        }
        double prezzo(const Biglietto& b) const{
            Biglietto* p=const_cast<Biglietto*>(&b);
            double pr=0;
            PostoNonNumerato*x=dynamic_cast<PostoNonNumerato*>(p);
            if(x){
                if(x->getGalleria()) pr+=base_pr;
                else pr+=base_pr+add_pr;
                if(x->getPrezzo())  pr-=add_pr/2;
            }
            PostoNumerato*y=dynamic_cast<PostoNumerato*>(p);
            if(y){
                if(y->getFila() == 1 && y->getFila() < maxFila)   pr+=2*add_pr+2*base_pr;
                else if(y->getFila() > 1)   pr+=2*add_pr;
            }
            return pr;
        }
        double incasso() const{
            double inc=0;
            for(list<Biglietto*>::const_iterator it=l.begin(); it!=l.end(); ++it)
                inc += prezzo(**it);
            return inc;
        }
};

int main(){
    Spettacolo s(10, 6, 200, 10, 20);
    PostoNumerato a1("pippo", 2);
    PostoNumerato a2("pluto",17);
    PostoNonNumerato b1("zagor");
    PostoNonNumerato b2("pluto", false, true);
    s.aggiungiBiglietto(a1); s.aggiungiBiglietto(a2);
    s.aggiungiBiglietto(b1); s.aggiungiBiglietto(b2);
    cout << s.incasso();
}
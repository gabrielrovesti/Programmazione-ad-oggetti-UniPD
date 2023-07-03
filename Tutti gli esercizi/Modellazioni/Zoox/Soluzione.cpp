#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <typeinfo>

using namespace std;

class Capo{
    private:
        string marca;
        int taglia;
    public:
        Capo(string m = "", int t=0): marca(m), taglia(t){}
        virtual ~Capo() = 0;
        string getMarca() const{ return marca; }
        int getTaglia() const{ return taglia; }
        virtual bool operator==(const Capo& c) const{
            return marca == c.marca && taglia == c.taglia;
        }
};

class Jeans : public Capo{
    private:
        double fondo;
    public:
        Jeans(string m = "", int t=0, double f=0): Capo(m,t), fondo(f){}
        double getFondo() const{ return fondo; }
        virtual bool operator==(const Capo& c) const{
            return typeid(const Jeans&) == typeid(c) && Capo::operator==(c) &&
            fondo == (static_cast<const Jeans&>(c)).fondo;
        }
};

class Articolo{
    friend class Zoox;
    private:
        Capo* c;
        unsigned int q;
    public:
        Articolo(Capo *capo = 0, unsigned int quantita = 0): c(capo), q(quantita){}
        unsigned int getQuantita() const{ return q; }
};

class TShirt : public Capo{
    private:
        bool manicaLunga;
    public:
        TShirt(string m = "", int t = 0, bool manica = false): Capo(m,t), manicaLunga(manica){}
        bool isManicaLunga() const{ return manicaLunga; }
        virtual bool operator==(const Capo& c) const{
            return typeid(const TShirt&) == typeid(c) && Capo::operator==(c);
        }
};

class Exc{
    private:
        string msg;
    public:
        Exc(string m): msg(m){};
        string getException() const{ return msg; }
};

class Zoox{
    private:
        vector<Articolo> magazzino;
    public:
        int giacenza(const Capo& c){
            int n_articoli=0;
            for(auto it = magazzino.begin(); it != magazzino.end(); ++it){
                if(*it->c == c){
                    n_articoli += it->q;
                }
            }
            return n_articoli;
        }

        vector<Jeans> getJeans(string marca, int size, double x){
            vector<Jeans> v;
            for(auto it = magazzino.begin(); it != magazzino.end(); ++it){
                Jeans *j = dynamic_cast<Jeans*>(it->c);
                if(j && j->getMarca() == marca && j->getTaglia() == size && j->getFondo() >= x){
                    v.push_back(*j);
                }
            }
            return v;
        }

        void scarica(const TShirt* pt){
            for(auto it = magazzino.begin(); it != magazzino.end(); ++it){
                TShirt *t = dynamic_cast<TShirt*>(it->c);
                if(t && *t == *pt){
                    if(it->q > 1){
                        it->q--;
                    }
                    else{
                        magazzino.erase(it);
                    }
                }
            }
            //if(*pt != *magazzino.back().c)
            //if(pt != dynamic_cast<TShirt*>(magazzino.back().c))
            throw Exc("TShirt non presente nel magazzino");
        }

        void insert(const TShirt& t, int num){
            for(auto it = magazzino.begin(); it != magazzino.end(); ++it){
                TShirt *ts = dynamic_cast<TShirt*>(it->c);
                if(ts && ts->isManicaLunga() && ts->getMarca() == t.getMarca()){
                    throw Exc("presente");
                }
            }
            magazzino.push_back(Articolo(new TShirt(t), num));
        }
};

int main(){
    return 0;
}
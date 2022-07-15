#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Abbonato{
    private:
    double traffico_mb;
    double traffico_ore;
    public:
    static double costo_base;
    static double costo_extra;
    virtual double costoMeseCorrente()=0;
    double get_traffico_mb() const{return traffico_mb;}
    double get_traffico_ore() const{return traffico_ore;}
};
double Abbonato::costo_base=15;
double Abbonato::costo_extra=5;

class AbbonatoTraffico: public Abbonato{
    private:
    double soglia_traffico;
    public:
    double get_soglia_traffico() const{return soglia_traffico;}
    virtual double costoMeseCorrente(){
        if(soglia_traffico <= get_traffico_mb()){
            return costo_base;
        }
        else{
            return costo_base+costo_extra;
        }
    }
};

class AbbonatoTempo: public Abbonato{
    private:
    double soglia_tempo;
    public:
    double get_soglia_tempo() const{return soglia_tempo;}
    virtual double costoMeseCorrente(){
        if(soglia_tempo <= get_traffico_ore()){
            return costo_base;
        }
        else{
            return costo_base+costo_extra;
        }
    }
};

class Exc{
    int error;
    public:
    Exc(int e): error(e) {}
};

class FilialeWI{
    private:
    int n_max_abb;
    int n_abb;
    list<const Abbonato*>v;
    public:
    int get_n_abb() const{return n_abb;}
    int get_nmax_abb() const{return n_max_abb;}
    void aggiungiAbbonato(const Abbonato& a){
        if(n_abb < n_max_abb){
            v.push_back(&a);
        }
        else{
            throw Exc(n_max_abb);
        }
    }
    list<const Abbonato*> abbonatiOltreSoglia(){
        list<const Abbonato*> l;

        list<const Abbonato*>::const_iterator it=v.begin();
        for(; it!=v.end(); ++it){
            AbbonatoTempo*a=dynamic_cast<AbbonatoTempo*>(const_cast<Abbonato*>(*it));
            if(a->costoMeseCorrente() > 50 && (*it)->get_traffico_ore() > a->get_soglia_tempo()){
                l.push_back(*it);
            }
        }
        return l;
    }
};

int main(){

    return 0;
}
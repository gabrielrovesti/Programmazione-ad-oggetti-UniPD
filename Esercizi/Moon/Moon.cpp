#include <iostream>
#include <vector>
using namespace std;
class Cliente{
    private:
    unsigned int minuti_t, n_tel, n_sms, t_dati;
    public:
    static unsigned int const costo_t_d;
    virtual ~Cliente() = default;
    virtual double costoMeseCorrente() const=0;
    unsigned int getMinuti() const{return minuti_t;}
    unsigned int getTel() const{return n_tel;}
    unsigned int getSms() const{return n_sms;}
    unsigned int getMb() const{return t_dati;}
    virtual Cliente* clone() const=0;
};
unsigned int const Cliente::costo_t_d=0.1;

class AlMinuto: public Cliente{
    private:
    static double const scatto_r, costo_t, costo_s;
    public:
    virtual double costoMeseCorrente() const{
        return static_cast<double>(Cliente::getMinuti())*costo_t +
        static_cast<double>(Cliente::getSms())*costo_s+
        static_cast<double>(Cliente::getTel())*scatto_r;
    }
    virtual AlMinuto* clone() const{
        return new AlMinuto(*this);
    }
};
const double AlMinuto::scatto_r=0.15;
const double AlMinuto::costo_t=0.2;
const double AlMinuto::costo_s=0.1;

class Abbonamento: public Cliente{
    private:
    double costo_m, soglia_t;
    public:
    static const double soglia_t_m;
    double get_costo_m() const{return costo_m;}
    double get_soglia_t() const{return soglia_t;}
    virtual double costoMeseCorrente() const{
        return costo_m + (soglia_t < Cliente::getMinuti() ?
        static_cast<double>(Cliente::getMinuti() - soglia_t) * soglia_t_m : 0)+
        static_cast<double>(Cliente::getMb())*costo_t_d;
    }
    virtual Abbonamento* clone() const{
        return new Abbonamento(*this);
    }
};
const double Abbonamento::soglia_t_m=0.3;

class SedeMoon {
private:
    vector<Cliente*> vClienti;
public:
    void aggiungiCliente(const Cliente& c) {
        vClienti.push_back(c.clone());
    }
    double incassoMensileCorrente() const {
        double tot = 0;
        for(auto it = vClienti.begin(); it != vClienti.end(); ++it){
            tot += (*it)->costoMeseCorrente();
        }
        return tot;
    }
    int numClientiAbbonatiOltreSoglia() const {
        int somma = 0;
        for(auto it = vClienti.begin(); it != vClienti.end(); ++it){
            Abbonamento* b = dynamic_cast<Abbonamento*>(*it);
            if(b && b->getMinuti() > b->get_soglia_t()) ++somma;
        }
        return somma;
    }
    vector<AlMinuto> alMinutoSMS(int x) const {
        vector<AlMinuto> v;
        for(auto it = vClienti.begin(); it != vClienti.end(); ++it){
            auto* p = dynamic_cast<AlMinuto*>(*it);
            if(p && p->getSms() > x) v.push_back(*(p->clone()));
        }
        return v;
    }
};

int main(){

}
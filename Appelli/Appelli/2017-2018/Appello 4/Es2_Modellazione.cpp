#include<iostream>
#include<vector>

using namespace std;

class Cliente{
    private:
        unsigned int min_effettuati;
        unsigned int num_tel_effettuate;
        unsigned int num_sms_inviati;
        unsigned int mb_effettuati;
    
    public:
        //metodi get
        unsigned int getMin_Effettuati() const  {return min_effettuati;}
        unsigned int getNum_Tel_Effettuate() const  {return num_tel_effettuate;}
        unsigned int getNum_Sms_Inviati() const {return num_sms_inviati;}
        unsigned int getMb_Effettuati() const   {return mb_effettuati;}
        
        //metodo virtuale puro
        virtual double costoMeseCorrente() const = 0;

        //membro statico
        static double costo_mb;

        unsigned int minOltreSoglia(unsigned int soglia) const {
            if(min_effettuati>soglia) return mb_effettuati-soglia;
            else return 0;
        }
};
double Cliente::costo_mb = 0.01;

class AlMinuto : public Cliente{
    public:
        //membri statici
        static double costo_scatto;
        static double costo_tel;
        static double costo_sms;

        //metodo virtuale
        double costoMeseCorrente() const{
            return (costo_scatto*getNum_Tel_Effettuate())+(costo_tel*getMin_Effettuati())+(costo_sms*getNum_Sms_Inviati())+Cliente::costo_mb*getMb_Effettuati();
        }
};
double AlMinuto::costo_scatto = 0.15;
double AlMinuto::costo_tel = 0.2;
double AlMinuto::costo_sms = 0.1;

class Abbonamento : public Cliente{
    private:
        double costo_abb;
        unsigned int min_mensili;
    public:
    unsigned int getMin_Mensili() const{
        return min_mensili;
    }
    //membro statico
    static double costo_oltre_soglia;
    double costoMeseCorrente() const{
        return costo_abb+(getMb_Effettuati()*Cliente::costo_mb)+minOltreSoglia(min_mensili)*costo_oltre_soglia;
    }
};
double Abbonamento::costo_oltre_soglia = 0.3;

class SedeMoon{
    private:
        std::vector<Cliente*> v;
    public:
    void aggiungiCliente(const Cliente& c){
        const Cliente* p1 = &c; // un oggetto costante può essere puntato solamente da un puntatore costante
        v.push_back(const_cast<Cliente*>(p1));
    }

    double incassoMensile() const{
        std::vector<Cliente*>::const_iterator it = v.begin(); // devo aggiungere const_iterator perchè sono dentro una funzione constante, perciò il mio *this è costante, essendo *this costante, lo sarà anche *this.v

        double totale = 0;
        for(; it!=v.end(); ++it){
            totale+=(*it)->costoMeseCorrente();
        }
        return totale;
    }

    int numClientiAbbonatiOltreSoglia() const{
        int num = 0;
        std::vector<Cliente*>::const_iterator it = v.begin();
        for(; it!=v.end(); ++it){
            Abbonamento* p = dynamic_cast<Abbonamento*>(*it);
            if(p && p->minOltreSoglia(p->getMin_Mensili())>0)num++;
        }
        return num;
    }
    vector<AlMinuto> alMinuto(int n) const{
        std::vector<Cliente*>::const_iterator it = v.begin();
        std::vector<AlMinuto> aux;
        for(; it!=v.end(); ++it){      
            AlMinuto* p = dynamic_cast<AlMinuto*>(*it);
            if(p && p->getNum_Sms_Inviati()>n){
                aux.push_back(*p);
            }
        }
        return aux;
    }

};

int main(){

}
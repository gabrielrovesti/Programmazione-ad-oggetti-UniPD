#include <iostream>
#include <vector>

using namespace std;

class Anomalia{
    private:
    char e;

    public: 
    Anomalia(char c): e(c) {}
    char getException() const{return e;}
};

class Scheda{
    private:
    string num_tel;
    double cr_res;
    double costo_sms;

    public:
    string getNumTel() const{return num_tel;}
    double getCrRes() const{return cr_res;}
    double getCostoSMS() const{return cr_res;}
    Scheda(string n, double cr, double co): num_tel(n), cr_res(cr), costo_sms(co){
        if(cr_res < 0) cr_res=0;
    }
    void addebita(double c){
        cr_res-=c;
    }
    virtual void telefonata(unsigned int)=0;
    virtual void connessione(double)=0;

    void messaggioSMS(unsigned int m){
        if(cr_res > m*costo_sms){
            cr_res-=m*costo_sms;
        }
        else throw Anomalia('c');
    }

    virtual ~Scheda(){}
};

class Mensile: public Scheda{
    private:
    //tutto const ma possono cambiare le soglie se cambiassi piano
    const int soglia_tel;
    unsigned int traffico_tel;
    const double soglia_mb;
    double traffico_mb;
    const double costo_abb;

    public:
    Mensile(string n_tel=0, double cr_res=0, 
    double costo_s=0.1, const unsigned int soglia_t=60000, const double soglia_c=2096):Scheda(n_tel, cr_res, costo_s), soglia_tel(soglia_t), traffico_tel(soglia_c),
    soglia_mb(0), traffico_mb(0), costo_abb(0){}
    
    virtual void telefonata(unsigned int t){
        if(traffico_tel + t > soglia_tel){
            throw Anomalia('v');
        }
        else{
            traffico_tel+=t;
        }
    }

    virtual void connessione(double k){
        if(traffico_mb + k > soglia_mb){
            throw Anomalia('d');
        }
        else{
            traffico_mb+=k;
        }
    }
};

class Consumo: public Scheda{
    private:
    const double costo_sec;
    const double costo_mb;

    public:
    Consumo(string num_tel=0, double cr_res=0, double costo_s=0.2, const double costo_tel=0.01, const double costo_m=0.1): 
    Scheda(num_tel, cr_res, costo_s), costo_sec(costo_tel), costo_mb(costo_m) {}

    virtual void telefonata(unsigned int n){
        if(costo_sec + n > getCrRes()){
            throw Anomalia('v');
        }
        else{
            addebita(n*costo_sec);
        }
    }

    virtual void connessione(double k){
        if(costo_mb + k > getCrRes()){
            throw Anomalia('d');
        }
        else{
            addebita(k*costo_mb);
        }
    }
};

class P2{
    private:
    vector <Scheda*> v;
    public:
    Consumo* cambioPiano(string p){
        vector<Scheda*>::iterator it=v.begin();
        bool trovato=false;
        for(; it<v.end() && !trovato; ++it){
            if((*it)->getNumTel() == p){
                trovato=true;
            }
        }

        if(!trovato && !(dynamic_cast<Mensile*>((*it))))    return 0;
        else{
            Consumo* c=new Consumo((*it)->getNumTel(), (*it)->getCrRes());
            delete *it;
            *it=c;
            return c;
        }
    }
    
    vector<Consumo> rimuoviConsumoZero(){
        vector<Scheda*>::iterator it=v.begin();
        vector<Consumo> c;

        for(; it<v.end(); ++it){
            if((*it)->getCrRes()==0){
                Consumo* aux=dynamic_cast<Consumo*>((*it));
                if(aux)    
                    c.push_back(Consumo(*aux));
                    delete aux;
                    it=v.erase(it);
                    it--;
                }
            }
            return c;
        }

        double contabilizza(){
            double prima, dopo;
            vector<Scheda*>::iterator it=v.begin();
            for(; it<v.end() && (*it)->getCrRes() > 0; ++it){
                prima=prima+(*it)->getCrRes();

                (*it)->telefonata(1);
                (*it)->connessione(1);
                (*it)->messaggioSMS(1);

                dopo=dopo+(*it)->getCrRes();
            }

            return prima-dopo;
        }
};

int main(){

}
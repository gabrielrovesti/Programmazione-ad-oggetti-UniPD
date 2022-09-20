#include <iostream>
#include <vector>
using namespace std;

class Prodotto{
    private:
        double prezzo;
    public:
        Prodotto(double pr): prezzo(pr) {};
        double getPrezzo() const{return prezzo;}
};

class Cliente{
    private:
        vector<Prodotto> lista;
    public:
        virtual ~Cliente();
        virtual double spesaTotale() const{
            double tot=0;
            for(int i=0; i<lista.size(); i++){
                tot += lista[i].getPrezzo();
            }
            return tot;
        }
};

class RitiroPremio{};

class ClienteFedele: public Cliente{
    private:
    unsigned int saldo;
    static int sconto;  
    static int premio;  
    static int soglia;
    public:
        ClienteFedele(int punti): saldo(punti) {}
        virtual double spesaTotale() const{
            double tot=Cliente::spesaTotale();
            tot *= 1 - sconto / 100;
            return tot;
        }
        void accreditaPunti(int n){
            saldo+=n;
            if(saldo >= soglia){
                try{saldo -= soglia;}
                catch(RitiroPremio) {}
            }
        }
        int getSaldo() const{return saldo;}
};
int ClienteFedele::soglia=100;
int ClienteFedele::premio=5;

//Per i poveri cristi
//NON mettete throw quando lanciate l'errore; le dynamic exceptions
//sono deprecate in C++ 11; si fa con try e catch come sotto
class Gestionegiornaliera{
    private:
        vector<Cliente*> lista_c;
    public:
        double chiudiCassa() const{
            double tot=0, s=0;
            for(int i=0; i<lista_c.size(); i++){
                s += lista_c[i]->spesaTotale();
                tot += s;
                ClienteFedele *p=dynamic_cast<ClienteFedele*>(lista_c[i]);
                try{p->accreditaPunti(static_cast<int>(tot/10));}
                catch(RitiroPremio) {}
            }
            return tot;
        }
        int saldoPuntiGiornaliero() const{
            int tot=0;
            for(int i=0; i<lista_c.size(); i++){
                ClienteFedele *p=dynamic_cast<ClienteFedele*>(lista_c[i]);
                if(p) tot+=p->getSaldo();
            }
            return tot;
        }
};  

int main(){
   
}
#include <iostream>
#include <vector>
using namespace std;

class Prodotto{
    private:
        double prezzo;

    public:

        Prodotto(double pr): prezzo(pr) {};
        double getPrezzo() const {return prezzo;}
        virtual ~Prodotto() {}
};

class Cliente{

    public:
        vector<Prodotto> lista;
        virtual ~Cliente();
        virtual double spesaTotale() const{
            double tot=0;
            for(int i=0; i<lista.size(); i++)
                tot += lista[i].getPrezzo();
            return tot;
        }
};

class RitiroPremio{

    private:
        int punti;

    public:
        RitiroPremio(int p): punti(p) {}
        int getPunti() const { return punti; }
};

class ClienteFedele: public Cliente{

    private:
        unsigned int saldo;
        static int SC;  
        static int SP;

    public:
        ClienteFedele(int punti): saldo(punti) {}

        virtual double spesaTotale() const{
            double tot=0;
            for(int i=0; i<lista.size(); i++)
                tot += lista[i].getPrezzo() * SC;
            return tot;
        }

        void accreditaPunti(int n){
            saldo += n;
            if(saldo>=SP){
                saldo -= SP;
                throw RitiroPremio(SP);
            }
        }

        int getSaldo() const { return saldo; }
};

int ClienteFedele::SP=100;
int ClienteFedele::SC=0.5;

class Gestionegiornaliera{
    private:
        vector<Cliente*> lista_c;
    public:

        //Il metodo chiudiCassa deve ritornare l'incasso totale giornaliero del supermercato, ovvero per la lista giornaliera dei clienti rappresentata da g ed accreditare tutti i clienti fedeli della giornata i punti fedeltà accumulati secondo la seguente regola: per un cliente fedele con una spesa totale di s euro vengono accreditati s/10 punti (dove s/10 denota il troncamento intero della divisione)
        double chiudiCassa() const{
            double tot=0;
            for(int i=0; i<lista_c.size(); i++){
                tot += lista_c[i]->spesaTotale();
                ClienteFedele *p=dynamic_cast<ClienteFedele*>(lista_c[i]);
                if(p) p->accreditaPunti(p->spesaTotale()/10);
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
    return 0;
}
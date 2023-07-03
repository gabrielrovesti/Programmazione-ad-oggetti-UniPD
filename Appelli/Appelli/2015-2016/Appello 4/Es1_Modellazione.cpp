#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

class Nome{
    private:
        string nome;
    public:
        Nome(string n = "") : nome(n) {}
        string getNome() const { return nome; }
};

class Numero{
    private:
        string numero;
    public:
        Numero(string n = "") : numero(n) {}
        string getNumero() const { return numero; }
};

class Contatto{
    private:
        Nome nome;
    public:
        virtual Contatto* clone() const = 0;
        virtual bool operator==(const Contatto&) const = 0;

        Contatto(string n = "") : nome(n) {}
        Nome getNome() const { return nome; }
};

class Telefonico: public Contatto{
    private:
        Numero numero;
        unsigned int sms;
        bool isWhatsapp = false;
    public:
        Numero getNumeroTelefonico() const { return numero; }
        unsigned int getSms() const { return sms; }
        bool getWhatsappState() const { return isWhatsapp; }

        Telefonico(string n = "", string num = "", unsigned int s = 0, bool w = false) : Contatto(n), numero(num), sms(s), isWhatsapp(w) {}
        virtual Contatto* clone() const {
            return new Telefonico(*this);
        }
        virtual bool operator==(const Contatto &q) const{
            const Telefonico* t = dynamic_cast<const Telefonico*>(&q);
            if(t && t->getNumeroTelefonico().getNumero() == numero.getNumero())
                return true;
        }
};

class Skype: public Contatto{
    private:
        string username;
        bool isVideochiamata = false;
    public:
        string getUsername() const { return username; }
        bool getVideoState() const { return isVideochiamata; }

        Skype(string n = "", string u = "", bool v = false) : Contatto(n), username(u), isVideochiamata(v) {}
        virtual Contatto* clone() const {
            return new Skype(*this);
        }
        virtual bool operator==(const Contatto &q) const{
            const Skype* t = dynamic_cast<const Skype*>(&q);
            if(t && t->getUsername() == username){
                return true;
            }
        }
};

class Rubrica{
    public:
        class Entry{
            public:
                Contatto *c;
                int n_com;
                Contatto *getContatto() const { return c; }
                int getN_com() const { return n_com; }

                Entry(Contatto *contatto, int n): c(contatto == nullptr ? nullptr : contatto->clone()), n_com(n) {}

                //assegnazione profonda
                Entry& operator=(const Entry &e){
                    if(this != &e){
                        delete c;
                        c = e.c->clone();
                        n_com = e.n_com;
                    }
                    return *this;
                }


                //distruzione profonda
                ~Entry(){
                    if(c) delete c;
                }

                //copia profonda
                Entry(const Entry &e): c(e.c->clone()), n_com(e.n_com) {}
        };
    vector<Entry> rubrica;

    void insert(Contatto *p, int n){
        bool found = false;
        for(auto i = rubrica.begin(); i != rubrica.end(); ++i){
            if(i->c == p){
                i->n_com += n;
                found = true;
            }
        }

        if(!found){
            Entry e(p, n);
            rubrica.push_back(e);
            //rubrica.push_back(Entry(p, n));
        }
    }
    
    list<Telefonico> tel(const Nome& name, int s){
        list<Telefonico> l;
        for(auto i = rubrica.begin(); i != rubrica.end(); ++i){
            Telefonico *t = dynamic_cast<Telefonico*>(i->c);
            if(t && t->getNome().getNome() == name.getNome() && t->getSms() >= s){
                l.push_back(*t);
            }
        }
        return l;
    }

    int whatsCall(){
        int contacts_number = 0;
        for(auto i = rubrica.begin(); i != rubrica.end(); ++i){
            Telefonico *t = dynamic_cast<Telefonico*>(i->c);
            if(t && t->getWhatsappState()){
                contacts_number++;
            }
            else{
                Skype *s = dynamic_cast<Skype*>(i->c);
                if(s && s->getVideoState()){
                    contacts_number++;
                }
            }
        }
        return contacts_number;
    }
};

int main(){

}
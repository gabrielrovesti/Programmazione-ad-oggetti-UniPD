#include <iostream>
#include <vector>
#include <list>
using std::cout;
using std::endl;

class Nome {
    std::string nome;
public:
    Nome(std::string n = "") :nome(n) {} //non necessario
    std::string getNome() const { return nome; }
};
class Numero {
    std::string numero;
public:
    Numero(std::string n = "") :numero(n) {} //non necessario
    std::string getNumero() const { return numero; }
};

class Contatto {
protected:
    Nome nome;
public:
    Contatto(std::string n = "") :nome(n) {} //non necessario
    Nome getNome()const { return nome; }
    virtual Contatto* clone()const = 0;
    virtual bool operator==(const Contatto&)const = 0;
};
class Telefonico: public Contatto {
    Numero numero;
    int n_sms;
    bool whatsapp;
public:
    Telefonico(std::string nome = "", std::string n = "", int sms = 0, bool w = true) : Contatto(nome), numero(n), n_sms(sms > 0 ? sms : 0), whatsapp(w) {} //non necessario
    Numero getNumero()const { return numero; }
    int getN_sms()const { return n_sms; }
    bool getWhatsapp()const { return whatsapp; }
    Telefonico* clone()const { return new Telefonico(*this); }
    bool operator==(const Contatto& c)const {
        const Telefonico* tmp = dynamic_cast<const Telefonico*>(&c);
        if (tmp && tmp->getNumero().getNumero() == numero.getNumero())
            return true;
        return false;
    }
};
class Skype :public Contatto {
    std::string username;
    bool videochiamata;
public:
    Skype(std::string nome = "", std::string u = "", bool v = true) :Contatto(nome), username(u), videochiamata(v) {} //non necessario
    std::string getUsername()const { return username; }
    bool getVideochiamata()const { return videochiamata; }
    Skype* clone()const { return new Skype(*this); }
    bool operator==(const Contatto& c)const{
        const Skype* tmp = dynamic_cast<const Skype*>(&c);
        if (tmp && tmp->getUsername() == username)
            return true;
        return false;
    }
};
class Rubrica {
    class Entry {
    public:
        Contatto* p;
        int n_comunicazioni;
        Entry(Contatto* c = nullptr, int n = 0) :p(c == nullptr ? nullptr : c->clone()), n_comunicazioni(n) {}
        Entry(const Entry& e) :p(e.p == nullptr ? nullptr : e.p->clone()), n_comunicazioni(e.n_comunicazioni) {}
        Entry& operator=(const Entry& e) {
            if (&e != this) {
                p = e.p->clone();
                n_comunicazioni = e.n_comunicazioni;
            }
            return *this;
        }
        ~Entry() { if (p) delete p; }
    };
    std::vector<Entry> vettore;
public:
    void insert(Contatto* p, int n) {
        bool trovato = false;
        for (auto it = vettore.begin(); it != vettore.end() && !trovato; it++) {
            if (it->p->getNome().getNome() == p->getNome().getNome()) {
                trovato = true;
                it->n_comunicazioni += n;
            }
        }
        if (!trovato)
            vettore.push_back(Entry(p, n));
    }
    std::list<Telefonico> tel(const Nome& name, int s) const {
        std::list<Telefonico> da_ritornare;
        for (auto it = vettore.begin(); it != vettore.end(); it++) {
            Telefonico* tmp = dynamic_cast<Telefonico*>(it->p);
            if (tmp && tmp->getNome().getNome() == name.getNome() && tmp->getN_sms() >= s)
                da_ritornare.push_back(*tmp);
        }
        return da_ritornare;
    }
    int whatsCall()const {
        int n = 0;
        for (auto it = vettore.begin(); it != vettore.end(); it++) {
            Telefonico* tmp = dynamic_cast<Telefonico*>(it->p);
            if (tmp && tmp->getWhatsapp())
                n++;
            else {
                Skype* tmp2 = dynamic_cast<Skype*>(it->p);
                if (tmp2 && tmp2->getVideochiamata())
                    n++;
            }
        }
        return n;
    }
    void stampaRubrica()const {
        int i = 0;
        for (auto it = vettore.begin(); it != vettore.end(); it++, i++) {
            cout << "CONTATTO " << i + 1 << ":" << endl;
            cout << "Nome: " << it->p->getNome().getNome() << endl;
            Telefonico* tmp = dynamic_cast<Telefonico*>(it->p);
            if (tmp) {
                cout << "Numero: " << tmp->getNumero().getNumero() << endl;
                cout << "Numero SMS: " << tmp->getN_sms() << endl;
                cout << "Whatsapp: "; if (tmp->getWhatsapp()) cout << "si" << endl; else cout << "no" << endl;
            }
            else {
                Skype* tmp2 = dynamic_cast<Skype*>(it->p);
                cout << "Username: " << tmp2->getUsername()<< endl;
                cout << "Videochiamate: "; if (tmp2->getVideochiamata()) cout << "si" << endl; else cout << "no" << endl;
            }
            cout << "numero comunicazioni: " << it->n_comunicazioni << endl;;
            cout << endl;
        }
    }
};
int main()
{
    Rubrica r;
    Telefonico* t1 = new Telefonico("Roberto", "123456789", 10, true);
    Telefonico* t2 = new Telefonico("Anegla", "987654321", 20, true);
    Telefonico* t3 = new Telefonico("Maria", "135792468", 12, false);
    Telefonico* t4 = new Telefonico("Lucrezia", "192837465", 3, true);
    Skype* s1 = new Skype("Marco", "Marco123", true);
    Skype* s2 = new Skype("Samuel", "DarkSamuel09", false);
    Skype* s3 = new Skype("Laura", "SakuraSempai", false);
    Skype* s4 = new Skype("Maurizia", "JesusBeliver1", true);
    r.insert(t1, 10);
    r.insert(t1, 10);//inserimento doppio di t1 per verificare se insert funziona
    r.insert(t2, 5);
    r.insert(t3, 7);
    r.insert(t4, 3);
    r.insert(s1, 9);
    r.insert(s2, 6);
    r.insert(s3, 2);
    r.insert(s4, 0);
    
    r.stampaRubrica();
    Nome roberto("Roberto");
    std::list<Telefonico> lista = r.tel(roberto, 4);
    cout << "CONTENUTO LISTA:" << endl;
    int i = 0;
    for (auto it = lista.begin(); it != lista.end(); it++) {
        cout << i + 1 << ") " << it->getNome().getNome() << endl;
    }

    cout << endl << "Contatti che fanno videochiamate o hanno whatsapp: " << r.whatsCall() << endl;
}



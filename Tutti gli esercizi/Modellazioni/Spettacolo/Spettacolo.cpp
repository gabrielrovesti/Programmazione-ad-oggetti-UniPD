#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Biglietto {
private:
    string nome;
    bool galleria;

protected:
    Biglietto(const Biglietto& b) : nome(b.nome), galleria(b.galleria) {}
    Biglietto(string n, bool g) : nome(n), galleria(g) {}
    Biglietto(string n) : nome(n) {}
    Biglietto() {}
    virtual ~Biglietto() {}

public:
    string getNome() const { return nome; }
    bool getGalleria() const { return galleria; }
};

class PostoNumerato : public Biglietto {
private:
    int fila;

public:
    PostoNumerato(string nome, int f) : Biglietto(nome), fila(f) {}
    int getFila() const { return fila; }
};

class PostoNonNumerato : public Biglietto {
private:
    double prezzo_r;

public:
    PostoNonNumerato(string nome, bool g = true, bool p = false) : Biglietto(nome, g), prezzo_r(p) {}
    double getPrezzo() const { return prezzo_r; }
};

class Spettacolo {
private:
    double base_pr, add_pr;
    int maxNum, maxFila;
    int posti_venduti;
    list<Biglietto*> l;

public:
    void aggiungiBiglietto(const Biglietto& b) {
        const PostoNonNumerato* x = dynamic_cast<const PostoNonNumerato*>(&b);
        if (x) {
            l.push_back(const_cast<Biglietto*>(&b));
            return;
        }
        const PostoNumerato* y = dynamic_cast<const PostoNumerato*>(&b);
        if (y) {
            if (posti_venduti < maxNum) {
                l.push_back(const_cast<Biglietto*>(&b));
                posti_venduti++;
            }
        }
    }

    double prezzo(const Biglietto& b) const {
        const PostoNumerato* x = dynamic_cast<const PostoNumerato*>(&b);
        if (x) {
            if (x->getFila() == 1)
                return 2 * base_pr + 2 * add_pr;
            else
                return base_pr + add_pr;
        }
        const PostoNonNumerato* y = dynamic_cast<const PostoNonNumerato*>(&b);
        if (y) {
            if (y->getGalleria())
                return base_pr;
            else
                return base_pr + add_pr;
        }
        return 0;
    }

    double incasso() const {
        double tot = 0;
        for (list<Biglietto*>::const_iterator it = l.begin(); it != l.end(); ++it) {
            tot += prezzo(**it);
        }
        return tot;
    }
};

int main() {
    Spettacolo s;
    s.aggiungiBiglietto(PostoNonNumerato("Mario", true, true));
    s.aggiungiBiglietto(PostoNonNumerato("Luigi", false, true));
    s.aggiungiBiglietto(PostoNumerato("Peach", 1));
    s.aggiungiBiglietto(PostoNumerato("Toad", 2));
    cout << s.incasso() << endl;
    return 0;
}

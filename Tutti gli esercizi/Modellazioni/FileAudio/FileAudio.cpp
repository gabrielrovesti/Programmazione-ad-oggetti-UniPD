/*
Si consideri il seguente modello di realtà concernente i file audio memorizzati in un riproduttore audio
digitale iZod.

(A) Definire la seguente gerarchia di classi.

1. Definire una classe base polimorfa astratta FileAudio i cui oggetti rappresentano un file audio
memorizzabile in un iZod. Ogni FileAudio caratterizzato dal titolo (una stringa) e dalla propria dimensione
in MB. La classe è astratta in quanto prevede i seguenti metodi virtuali puri:
• un metodo di “clonazione”: FileAudio* clone().
• un metodo bool qualita() con il seguente contratto: f->qualita() ritorna true se il file audio *f è
considerato di qualità, altrimenti ritorna false.

2. Definire una classe concreta Mp3 derivata da FileAudio i cui oggetti rappresentano un file audio in
formato mp3. Ogni oggetto Mp3 è caratterizzato dal proprio bitrate espresso in Kbit/s. La classe Mp3
implementa i metodi virtuali puri di FileAudio come segue:
• per ogni puntatore p a Mp3, p->clone() ritorna un puntatore ad un oggetto Mp3 che è una copia di *p.
• per ogni puntatore p a Mp3, p->qualita() ritorna true se il bitrate di *p è ≥ 192 Kbit/s, altrimenti
ritorna false.

3. Definire una classe concreta WAV derivata da FileAudio i cui oggetti rappresentano un file audio in
formato WAV. Ogni oggetto WAV è caratterizzato dalla propria frequenza di campionamento espressa in kHz e
dall’essere lossless oppure no (cioè con compressione senza perdita oppure con perdita). La classe WAV
implementa i metodi virtuali puri di FileAudio come segue:
• per ogni puntatore p a WAV, p->clone() ritorna un puntatore ad un oggetto WAV che è una copia di *p.
• per ogni puntatore p a WAV, p->qualita() ritorna true se la frequenza di campionamento di *p è ≥ 96 kHz,
altrimenti ritorna false.

(B) Definire una classe iZod i cui oggetti rappresentano i brani memorizzati in un iZod. La classe iZod deve
soddisfare le seguenti specifiche:

1. E definita una classe annidata Brano i cui oggetti rappresentano un brano memorizzato nell’iZod. Ogni
oggetto Brano è rappresentato da un puntatore polimorfo ad un FileAudio.
• La classe Brano deve essere dotata di un opportuno costruttore Brano(FileAudio*) con il seguente
comportamento: Brano(p) costruisce un oggetto Brano il cui puntatore polimorfo punta ad una copia dell’oggetto *p.
• La classe Brano ridefinisce costruttore di copia profonda, assegnazione profonda e distruttore profondo.

2. Un oggetto di iZod è quindi caratterizzato da un vector di oggetti di tipo Brano che contiene tutti i
brani memorizzati nell’iZod.

3. La classe iZod rende disponibili i seguenti metodi:
• Un metodo vector<Mp3> mp3(double, int) con il seguente comportamento: 
una invocazione iz.mp3(dim,br)
ritorna un vector di oggetti Mp3 contenente tutti e soli i file audio in formato mp3 memorizzati nell’iZod
iz che: (i) hanno una dimensione ≥ dim e (ii) hanno un bitrate ≥ br.

• Un metodo vector<FileAudio*> braniQual() con il seguente comportamento: una invocazione iz.braniQual()
ritorna il vector dei puntatori ai FileAudio memorizzati nell’iZod iz che: (i) sono considerati di qualità e
(ii) se sono dei file audio WAV allora devono essere lossless.

• Un metodo void insert(Mp3*) con il seguente comportamento: una invocazione iz.insert(p) inserisce il nuovo
oggetto Brano(p) nel vector dei brani memorizzati nell’iZod iz se il file audio mp3 *p non è già memorizzato
in iz, mentre se il file audio *p risulta già memorizzato non provoca alcun effetto.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class FileAudio{
    private:
        string titolo;
        double MB;
    public:
        virtual FileAudio* clone() const = 0;
        virtual bool qualita() const = 0;
        string getTitolo() const {return titolo;}
        double getMB() const {return MB;}
};

class Mp3: public FileAudio{
    private:
        unsigned int bitrate;
    public:
        virtual Mp3* clone() const {return new Mp3(*this);}
        virtual bool qualita() const {return bitrate >= 192;}
        unsigned int getBitrate() const {return bitrate;}
};

class WAV: public FileAudio{
    private:
        unsigned int frequenza;
        bool lossless;
    public:
        virtual WAV* clone() const {return new WAV(*this);}
        virtual bool qualita() const {return frequenza >= 96;}
        unsigned int getFrequenza() const {return frequenza;}
        bool getLossless() const {return lossless;}
};

class iZod{
    private:
        class Brano{
            public:
                FileAudio *ptr; //puntatore polimorfo = puntatore (*)
                Brano(FileAudio *p): ptr(p->clone()){}
                //clono qualsiasi formato possa avere

                Brano(const Brano &b): ptr(b.ptr->clone()){}

                Brano& operator=(const Brano &b){
                    if(this != &b){
                        delete ptr;
                        ptr = b.ptr->clone();
                    }
                    return *this;
                }

                ~Brano(){delete ptr;}
        };

       vector<Brano> brani;

    /*
    • Un metodo vector<Mp3> mp3(double, int) con il seguente comportamento: 
    una invocazione iz.mp3(dim,br)
    ritorna un vector di oggetti Mp3 contenente tutti e soli i file audio in formato mp3 memorizzati nell’iZod
    iz che: (i) hanno una dimensione ≥ dim e (ii) hanno un bitrate ≥ br.
    */
       vector<Mp3> mp3(double dim, unsigned int br) const{
            vector<Mp3> v;

            for(vector<Brano>::const_iterator cit = brani.begin(); cit != brani.end(); ++cit){
                Mp3 *p = dynamic_cast<Mp3*>(cit->ptr);
                if(p && p->getMB() >= dim && p->getBitrate() >= br)
                    v.push_back(*p);
            }

            return v;
       }

/*
• Un metodo vector<FileAudio*> braniQual() con il seguente comportamento: una invocazione iz.braniQual()
ritorna il vector dei puntatori ai FileAudio memorizzati nell’iZod iz che: 
(i) sono considerati di qualità e
(ii) se sono dei file audio WAV allora devono essere lossless.
*/

        vector<FileAudio*> braniQual() const{
            vector <FileAudio*> v;

            for(vector<Brano>::const_iterator cit = brani.begin(); cit != brani.end(); ++cit){
                if(cit->ptr->qualita()){ //prendo il fileAudio, controllo che sia di qualità
                    WAV *p = dynamic_cast<WAV*>(cit->ptr);
                    if(p && p->getLossless())
                        v.push_back(cit->ptr);
                }
            }

            return v;
        }

/*
• Un metodo void insert(Mp3*) con il seguente comportamento: una invocazione iz.insert(p) inserisce il nuovo
oggetto Brano(p) nel vector dei brani memorizzati nell’iZod iz se il file audio mp3 *p non è già memorizzato
in iz, mentre se il file audio *p risulta già memorizzato non provoca alcun effetto.
*/

        void insert(Mp3 * m){
            for(vector<Brano>::const_iterator cit = brani.begin(); cit != brani.end(); ++cit){
                Mp3 *p = dynamic_cast<Mp3*>(cit->ptr);
                if(p && p->getTitolo() == m->getTitolo())
                    return;
            }
        }
};

//Crea un main d'esempio e testiamo i metodi creati
int main(){
    return 0;
}

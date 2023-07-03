// Esercizio 11.18 del libro

/*
Si consideri il seguente modello di realtà concernente i file audio memorizzati in un riproduttore audio digitale iZod.

(A) Definire la seguente gerarchia di classi.

1. Definire una classe base polimorfa astratta FileAudio i cui oggetti rappresentano un file audio memorizzabile in un iZod. Ogni FileAudio  caratterizzato dal titolo (una stringa) e dalla propria dimensione in MB. La classe è astratta in quanto prevede i seguenti metodi virtuali puri:

• un metodo di “clonazione”: FileAudio* clone().

• un metodo bool qualita() con il seguente contratto: f->qualita() ritorna true se il file audio *f è considerato di
qualità, altrimenti ritorna false.

2. Definire una classe concreta Mp3 derivata da FileAudio i cui oggetti rappresentano un file audio in formato mp3. Ogni oggetto Mp3 è caratterizzato dal proprio bitrate espresso in Kbit/s. La classe Mp3 implementa i metodi virtuali puri di FileAudio come segue:

• per ogni puntatore p a Mp3, p->clone() ritorna un puntatore ad un oggetto Mp3 che è una copia di *p.

• per ogni puntatore p a Mp3, p->qualita() ritorna true se il bitrate di *p è ≥ 192 Kbit/s, altrimenti ritorna false.

3. Definire una classe concreta WAV derivata da FileAudio i cui oggetti rappresentano un file audio in formato WAV. Ogni oggetto WAV è caratterizzato dalla propria frequenza di campionamento espressa in kHz e dall’essere lossless oppure no (cioè con compressione senza perdita oppure con perdita). La classe WAV implementa i metodi virtuali puri di FileAudio come segue:

• per ogni puntatore p a WAV, p->clone() ritorna un puntatore ad un oggetto WAV che è una copia di *p.

• per ogni puntatore p a WAV, p->qualita() ritorna true se la frequenza di campionamento di *p è ≥ 96 kHz, altrimenti
ritorna false.

(B) Definire una classe iZod i cui oggetti rappresentano i brani memorizzati in un iZod. La classe iZod deve soddisfare le seguenti specifiche:
`
1. E definita una classe annidata Brano i cui oggetti rappresentano un brano memorizzato nell’iZod. Ogni oggetto Brano è
rappresentato da un puntatore polimorfo ad un FileAudio.

• La classe Brano deve essere dotata di un opportuno costruttore Brano(FileAudio*) con il seguente comportamento:
Brano(p) costruisce un oggetto Brano il cui puntatore polimorfo punta ad una copia dell’oggetto *p.

• La classe Brano ridefinisce costruttore di copia profonda, assegnazione profonda e distruttore profondo.

2. Un oggetto di iZod è quindi caratterizzato da un vector di oggetti di tipo Brano che contiene tutti i brani memorizzati nell’iZod.

3. La classe iZod rende disponibili i seguenti metodi:

• Un metodo vector<Mp3> mp3(double, int) con il seguente comportamento: una invocazione iz.mp3(dim,br) ritorna un vector di oggetti Mp3 contenente tutti e soli i file audio in formato mp3 memorizzati nell’iZod iz che: (i) hanno una dimensione ≥ dim e (ii) hanno un bitrate ≥ br.

• Un metodo vector<FileAudio*> braniQual() con il seguente comportamento: una invocazione iz.braniQual() ritorna il vector dei puntatori ai FileAudio memorizzati nell’iZod iz che: (i) sono considerati di qualità e (ii) se sono dei file audio WAV allora devono essere lossless.

• Un metodo void insert(Mp3*) con il seguente comportamento: una invocazione iz.insert(p) inserisce il nuovo oggetto Brano(p) nel vector dei brani memorizzati nell’iZod iz se il file audio mp3 *p non è già memorizzato in iz, mentre se il file audio *p risulta già memorizzato non provoca alcun effetto.

*/

#include<string>

class FileAudio {
private:
  std::string titolo;
  double dim;
public:
  virtual FileAudio* clone() const =0;
  virtual bool qualita() const =0;
  virtual ~FileAudio() {}
  double getSize() const {return dim;}
  virtual bool operator==(const FileAudio& f) const {
    return titolo == f.titolo && dim==f.dim;
  }
};

class Mp3: public FileAudio {
private:
  unsigned int bitrate; // kbit/s
  static unsigned int qualitybitRate;
public:
  Mp3* clone() const override {return new Mp3(*this);}
  bool qualita() const override {return bitrate >= qualitybitRate; }
  unsigned int getBitrate() const {return bitrate;}
  bool operator==(const FileAudio& f) const override {
    return typeid(*this) == typeid(Mp3) && typeid(f) == typeid(*this) 
      && FileAudio::operator==(f) && bitrate == static_cast<const Mp3&>(f).bitrate;
  }
};

unsigned int Mp3::qualitybitRate = 192;

class WAV: public FileAudio {
private:
  unsigned int freq; // kHz
  bool lossLess;
  static unsigned int qualityFreq;
public:
  WAV* clone() const override {return new WAV(*this);}
  bool qualita() const override {return freq >= qualityFreq; }
  bool isLossLess() const {return lossLess;}
 bool operator==(const FileAudio& f) const override {
    return typeid(*this) == typeid(WAV) && typeid(f) == typeid(*this) 
      && FileAudio::operator==(f) && lossLess == static_cast<const WAV&>(f).lossLess
      && freq == static_cast<const WAV&>(f).freq;
  }
 
};
unsigned int WAV::qualityFreq = 96;

#include<vector>

class iZod {
private:
  class Brano {
  public:
    FileAudio* p; // puntatore super-polimorfo
    // agisce da convertitore FileAudio* a Brano
    Brano(FileAudio* q): p(q->clone()) {}
    Brano(const Brano& b): p(b.p->clone()) {} 
    Brano& operator=(const Brano& b) {
      if(this != &b) {
	if(p) delete p;
	p =  b.p->clone();
      }
      return *this;
    }
    ~Brano() {if(p) delete p;} // corretto perche' ~FileAudio e' virtuale
    FileAudio* operator->() const {return p;}
    FileAudio& operator*() const {return *p;}
  };
  
  std::vector<Brano> v;  

public:
  std::vector<Mp3> mp3(double d, int b) const {
    std::vector<Mp3> r;
    for(std::vector<Brano>::const_iterator cit = v.begin(); cit != v.end(); ++cit) {
      Mp3* t = dynamic_cast<Mp3*>(cit->p);
      if(t && t->getBitrate()>= b &&  t->getSize() >= d) r.push_back(*t); 
    }
    return r;
  }

  std::vector<FileAudio*> braniQual() const {
    std::vector<FileAudio*> r;
    for(std::vector<Brano>::const_iterator cit = v.begin(); cit != v.end(); ++cit) {
      if( (*cit)->qualita() && (!(dynamic_cast<WAV*> (cit->p)) || (static_cast<WAV*>(cit->p))->isLossLess() ) )
	r.push_back(cit->p);
    }
    return r;
  }
  
  void insert(Mp3* q) {
    auto it = v.begin();
    for( ; !(*(it->p) == *q) && it != v.end(); ++it);
    if(it==v.end()) v.push_back(q);
  }

};

int main() {}

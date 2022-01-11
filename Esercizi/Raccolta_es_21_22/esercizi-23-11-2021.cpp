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
#include<vector>
#include<typeinfo>

class FileAudio {
private:
  std::string titolo;
  double MB;
public:
  virtual FileAudio* clone() const =0;
  virtual bool qualita() const =0;
  virtual ~FileAudio() {}
  double getSize() const {return MB;}
  virtual bool operator==(const FileAudio& f) const {
    return typeid(*this)== typeid(f) && titolo==f.titolo && MB==f.MB; 
  }
};

class Mp3: public FileAudio {
private:
  static unsigned int sogliaQualita;
  unsigned int bitrate; // Kbit/s
public:
  Mp3* clone() const {return new Mp3(*this);}
  bool qualita() const {return bitrate >= sogliaQualita;}
  unsigned int getBitrate() const {return bitrate;}
  virtual bool operator==(const FileAudio& f) const {
    return FileAudio::operator==(f) && bitrate==static_cast<const Mp3&>(f).bitrate;
  }

};
unsigned int Mp3::sogliaQualita = 192;

class WAV: public FileAudio {
private:
  unsigned int frequenza; // in KHz
  bool lossless; // true se e' senza perdita
  static unsigned int sogliaQualita;
public:
  WAV* clone() const {return new WAV(*this);}
  bool qualita() const {return frequenza >= sogliaQualita;}
  bool isLossLess() const {return lossless;}
    virtual bool operator==(const FileAudio& f) const {
    return FileAudio::operator==(f) && frequenza==static_cast<const WAV&>(f).frequenza &&
      lossless==static_cast<const WAV&>(f).lossless;
    }
};

unsigned int WAV::sogliaQualita = 96;

class iZod {
private:
  class Brano {
  public:
    FileAudio* ptr; 
    // conversione FileAudio* => Brano
    Brano(FileAudio* p): ptr(p->clone()) {}
    Brano(const Brano& b): ptr(b.ptr->clone()) {}
    Brano& operator=(const Brano& b) {
      if(this != &b) {
	delete ptr; // distruzione polimorfa 
	ptr = b.ptr->clone();
      }
      return *this;
    }
    ~Brano() {delete ptr;}
  };

  std::vector<Brano> brani;  

public:
  std::vector<Mp3> mp3(double dim, unsigned int br) const {
    std::vector<Mp3> v;
    for(std::vector<Brano>::const_iterator cit = brani.begin(); cit != brani.end(); ++cit) {
      Mp3* q = dynamic_cast<Mp3*>(cit->ptr); 
      if(q && (cit->ptr)->getSize() > dim && q->getBitrate() > br)
	v.push_back(*q);
    }
    return v;
  }

  std::vector<FileAudio*> braniQual() const {
    std::vector<FileAudio*> v;
    for(std::vector<Brano>::const_iterator cit = brani.begin(); cit != brani.end(); ++cit)
      if((cit->ptr)->qualita() && (!dynamic_cast<WAV*>(cit->ptr) ||
				   static_cast<WAV*>(cit->ptr)->isLossLess()))
	v.push_back(cit->ptr);
    return v;
  }

  void insert(Mp3* m) {
    bool found = false;
    for(auto it =  brani.begin(); !found && it!=brani.end(); it++)
      found = *(it->ptr)==*m;
    if(!found) brani.push_back(m);
  }
};


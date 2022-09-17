// Esercizio 1, vacanze natalizie 2017/18

#include<vector>
#include<list>

class GalloFile {
private: 
  double sizeMB;
public:
  virtual GalloFile* clone() const =0;
  virtual bool highQuality() const =0;
  virtual ~GalloFile() = default;
  double getSize() const {
    return sizeMB;
  }
};

class Foto: public GalloFile {
private:
  unsigned int ISO;
  bool flash;
  static unsigned int ISOquality;
public:
  Foto* clone() const {
    return new Foto(*this);
  }
  bool highQuality() const {
    return ISO >= ISOquality;
  }
  bool withFlash() const {
    return flash;
  }
};
unsigned int Foto::ISOquality = 500;

class Video: public GalloFile {
private:
  unsigned int durata; // in secondi
  bool fullHD;
public:
  Video* clone() const {
    return new Video(*this);
  }
  bool highQuality() const {
    return fullHD;
  }
  unsigned int getDurata() const {
    return durata;
  } 
};

/*
nota: l'esercizio non dice nulla riguardo all'utilizzare una lista o un vector.
	il professore però tiene conto dell'efficienza del programma, quindi dato la rimozione di elementi che viene fatta
	in tempo lineare su liste rispetto al tempo costante (senza contare la compattazione) sui vector bisogna usare le liste
*/


class Gallo {
private:
  std::list<const GalloFile*> l;
public:
  std::vector<GalloFile*> selectHQ() const {
    std::vector<GalloFile*> v;
    auto cit = l.begin();
    for( ; cit != l.end(); ++cit) 
      if((*cit)->highQuality() &&
	 (!dynamic_cast<const Foto*>(*cit) || (static_cast<const Foto*>(*cit))->withFlash()) )
	v.push_back(const_cast<GalloFile*>(*cit));	  
    return v;
  }
  
  void removeNonFoto(double size) {
    bool erased=false;
    auto it = l.begin();
    for( ; it!=l.end(); ++it)
      if(!dynamic_cast<const Foto*>(*it) && (*it)->getSize() > size) { 
	delete *it; it=l.erase(it); --it; 
	if(!erased) erased=true;
      }
    if(!erased) throw std::logic_error("NoRemove");
  }
  
  const GalloFile* insert(const GalloFile* pf) {
    const Video* pv = dynamic_cast<const Video*>(pf);
    if(!pv || pv->getDurata() <60) { 
      const GalloFile* t = pf->clone(); 
      l.push_back(t); return t;
    }
    return nullptr;
  }
  
};
// ESAME SCRITTO 1/2/2016
#include<list>
#include<vector>
#include<exception>
using namespace std;

class GalloFile { 
private:
  double MBsize;
public:
  virtual GalloFile* clone() const =0;
  virtual bool highQuality() const =0;
  virtual ~GalloFile() {} 
  double getSize() const {return MBsize;} 
};

class Foto: public GalloFile { 
private:
  bool flash;
  unsigned int ISO;
public: 
  Foto* clone() const {
    return new Foto(*this); 
  }
  bool highQuality() const {
    return ISO >= 500; 
  }
  unsigned int getISO() const {return ISO;}
  bool withFlash() const {return flash;}
};

class Video: public GalloFile {
private:
  unsigned int durata; // in sec
  bool fullHD;         // true se e' formato almeno fullHD
public:
  Video* clone() const {
    return new Video(*this);
  }
  bool highQuality() const {
    return fullHD; 
  }
  unsigned int getDurata() const {return durata;}
};

class Gallo {
private:
  list<const GalloFile*> g;
public:  
  vector<GalloFile*> selectHQ() const {
    vector<GalloFile*> ris;
    for(list<const GalloFile*>::const_iterator cit = g.begin(); cit != g.end(); ++cit) {
      const Foto* pf = dynamic_cast<const Foto*>(*cit);
      if(((*cit)->highQuality() && (!pf || pf->withFlash())))  
	ris.push_back(const_cast<GalloFile*>(*cit)); 
    }
    return ris;
  }
  
  void removeNonFoto(double size) {
    bool removed=false;
    list<const GalloFile*>::iterator it = g.begin(); 
    while(it != g.end()) {
      const Foto* pf = dynamic_cast<const Foto*>(*it); 
      if(!pf && (*it)->getSize() > size) {
	delete *it; it = g.erase(it); removed=true;
      }
      else ++it;
    }
    if(!removed) throw std::logic_error("NoRemove");
  }

  const GalloFile* insert(const GalloFile* f) {
    const Video* pv = dynamic_cast<const Video*>(f);
    if(!pv || pv->getDurata()<60) { 
   // f = f->clone(); // ALTERNATIVA ACCETTABILE 
      g.push_back(f); 
      return f;
    }
    else return 0;
  }

};
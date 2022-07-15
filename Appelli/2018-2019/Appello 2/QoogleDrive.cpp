#include <iostream>
#include <vector>
#include <list>
using namespace std;

class File{
private:
	double dimensione;
	bool accessibile;
public:
	File(double d=0, bool a=false): dimensione(d),accessibile(a){}
	virtual ~File() = default;
	double getDim() const{ return dimensione;}
	double getAccessibility() const{ return accessibile;}
};

class Audio: public File{
private:
	bool lossy;
public:
	Audio(bool l=false): lossy(l) {}
	bool isLossy() const{ return lossy;}
};

class Mp3:public Audio{
 private:
    bool l;
public:
	Mp3(bool l=false):Audio(l){}
};

class Video:public File{
private:
	unsigned int framerate;
public:
	Video(unsigned int fps):framerate(fps){}
	unsigned int getFps() const{ return framerate;}
};

class Exc{
private:
	int err;
public:
	Exc(int e=0): err(e){std::cout<<"Exception caught";}
};

class QooqleDrive{
private:
	std::vector<File*> ptr;
	int capacity;
public:

Audio uploadFile(File& f){
    auto it = ptr.begin();
    Audio* q = dynamic_cast<Audio*>(&f);
    if(q && q->getAccessibility() && q->getDim() < capacity){
        ptr.push_back(q);
        return new Audio(q);
    }
    else throw Exc(1);
}

list<Audio*> audioCopy(){
	std::list<Audio*> saved;
	Audio* q = 0;
	for(auto it= ptr.begin(); it!= ptr.end(); ++it){
	q = dynamic_cast<Audio*>(*it);
	if(q && !q->isLossy() || dynamic_cast<Mp3*>(q))
		saved.push_back(q);
	}
	return saved;
}

Video* minVideo(unsigned int f){
    int minDim = INT_MAX;
    Video* q = 0;
    Video* s = 0;
    for(auto it=ptr.begin();it!=ptr.end();++it){
      q = dynamic_cast<Video*>(*it);
      if(q && q->getFps() > f && minDim ){
          s = q;
          minDim = q->getDim();
      }
	}
	if(!s) throw Exc(1); else return s;
}

};

int main(){
    
}


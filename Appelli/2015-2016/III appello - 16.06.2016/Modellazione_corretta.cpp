#include <iostream>
#include <vector>
#include <list>

using namespace std;

class FileAudio{
    private:
    double size_mb;
    public:
    virtual FileAudio* clone()=0;
    virtual bool quality() const=0;
    double getMb() const{return size_mb;}
    virtual ~FileAudio();
};

class Mp3: public FileAudio{
    private:
    double bitrate;
    public:
    virtual Mp3* clone(){
        return new Mp3(*this);
    }
    virtual bool quality() const{
        return (bitrate >=256) ? true : false;
    }
    double getBitrate() const{
        return bitrate;
    }
};

class Wav: public FileAudio{
    private:
    unsigned int frequenza;
    public:
    virtual Wav* clone(){
        return new Wav(*this);
    }
    virtual bool quality() const{
        return (frequenza >192) ? true : false;
    }
    unsigned int getFrequency() const{
        return frequenza;
    }
};

class MusicPlay{
    private:
    vector<FileAudio*> v;
    public:
    vector<Wav*> qualityWav(double dim){
        vector<Wav*> ret;
        vector<FileAudio*>::iterator it=v.begin();
        for(; it!=v.end(); ++it){
            Wav* w=dynamic_cast<Wav*>(*it);
            if(w && (*it)->getMb() <= dim && (*it)->quality()) ret.push_back(w);
        }
        return ret;
    }
    list<FileAudio*> nonConstCopy(){
        list<FileAudio*> ret;
        vector<FileAudio*>::iterator it=v.begin();
        for(; it!=v.end(); ++it){
            ret.push_back(*it);
        }
        return ret;
    }
    vector<Mp3> removeMp3(unsigned int br){
        vector<Mp3> ret;
        vector<FileAudio*>::iterator it=v.begin();
        for(; it!=v.end(); ++it){
            Mp3* m=dynamic_cast<Mp3*>(*it);
            if(m && m->getBitrate() < br){
                ret.push_back(*m);
                delete m;
                it=v.erase(it);
                it--;
            }
        }
        return ret;
    }
};


int main(){
    
}
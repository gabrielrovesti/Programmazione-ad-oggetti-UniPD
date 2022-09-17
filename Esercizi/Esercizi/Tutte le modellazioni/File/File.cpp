#include <iostream>
#include <list>
#include <vector>
using namespace std;

class File {
private:
    unsigned int size;
    bool publicAccess;
public:
    File(unsigned int s, bool a=false) : size(s), publicAccess(a) {}
    virtual ~File() {}

    unsigned int getSize() const {return size;}
    bool isPublic() const {return publicAccess;}
};

class Audio: public File {
private:
    bool lossy;
public:
    Audio(unsigned int s, bool l, bool a=false): File(s,a), lossy(l) {}
    bool isLossy() const {return lossy;}
};

class Mp3: public Audio {
public:
    Mp3(unsigned int s, bool a=false):
        Audio(s,true,a) {}
};

class Video: public File {
private:
    unsigned int framerate;
public:
    Video(unsigned int s, unsigned int fr, bool a=false):
    File(s,a), framerate(fr) {}  
    unsigned int giveFramerate() const {return framerate;} 
};

class Exc {
public:
    const char* description;
    Exc(const char* d) : description(d) {}
};

class QooqleDrive {
private:
    unsigned int capacity;
    std::vector<const File*> files;
public:
    Audio uploadFile(File& f) {
        if(dynamic_cast<Audio*>(&f) && f.isPublic() && capacity-f.getSize() >= 0)
        {
            files.push_back(&f);
            return static_cast<Audio&>(f);
        }
        else throw Exc("File non idoneo!");
    }

    list<Audio*> audioCopy() const {
        list<Audio*> l;
        for(int i = 0; i<files.size(); i++)
        {
            const Audio* file = dynamic_cast<const Audio*>(files[i]); //dynamic_cast non droppa il qualifier const
            if(file != nullptr && (!file->isLossy() || dynamic_cast<const Mp3*>(file) != nullptr))
                l.push_back(const_cast<Audio*>(file));
        }
        return l;
    }

    Video* minVideo(unsigned int fr) const {
        const Video* out = nullptr;
        bool found = false;
        unsigned int sizeMin = 0;
        for(unsigned int i = 0; i<files.size(); i++)
        {
            const Video* v = dynamic_cast<const Video*>(files[i]);
            if(v != nullptr && v->giveFramerate() > fr)
            {
                if(found && v->getSize() < sizeMin)
                {
                    out = v;
                    sizeMin = v->getSize();
                }
                else if(!found)
                {
                    out = v;
                    found = true;
                }
            }
        }
        if(found) return const_cast<Video*>(out);
        else throw Exc("Nessun video idoneo trovato!");
    }
};

int main()
{

}
#include <iostream>
#include <list>
#include <vector>
using namespace std;

/*
Si consideri il seguente modello concemente il servizio di file hosting QoogleDrive®. 
(A) Definire la seguente gerarchia di classi. 
1. Definire una classe File i cui oggetti rappresentano un generico file memorizzabile in
un account QooqleDrive®. Ogni File è caratterizzato dalla sua dimensione(in MB)
e dall'essere pubblicamente accessibile o meno. Dotare la classe File di opportuno/i
costruttori. 
2. Definire una classe Audio derivata da File i cui oggetti rappresentano un file audio.
Ogni file audio e caratterizzato dall' essere lossy, (cioe compresso con perdita di
informazione) oppure no. Dotare la classe Audio di opportuno/i costruttore/i. 
3. Definite una classe mp3 derivata da Audio i cui oggetti rappresentano un file audio in
formato mp3. Tutti i file audio in formate mp3 sono lossy. Dotare la classe mp3 di
opportuno/i costruttore/i. 
4. Definire una classe video derivata da File i cui oggetti rappresentano un file video.
Ogni Video è caratterizzato dal suo framerate, che è un numero intero positivo the
rappresenta la frequenza in hertz. Dotare la classe Video di opportuno/i costruttori. 
(B) Definire una classe Qoogledrive i cui oggetti rappresentano un account QooqleDrive®.
Più precisamente, un oggetto Qoogledrive è caratterizzato da tutti i file correntemente
memorizzati dall'account, che devono essere rappresentati mediante un contenitore di
puntatori al tipo File costante, e dalla capacità massima di memorizzazione (in MB)
dell'account. Devono essere definite le seguenti funzionalità: 
5. un metodo di istanza Audio uploadFile(File&) con it seguente comportamento: 
una invocazione qd.uploadFile(f) provoca l'upload del file f nell'account qd quando: 
(1) f è un file audio pubblicamente accessibile, e (2) la memoria libera dell' account qd
consente l'upload: se l' upload di f va a buon fine allora viene ritornata una copia del
file audio f, altrimenti viene sollevata una eccezione di tipo Exc, un tipo di cui è
richiesta la definizione. 
6. un metodo di istanza list<Audio*> audioCopy() con il seguente comportamento: 
una invocazione qd. audioCopy() ritorna una lista (possibilmente vuota) contenente tutti e
soli i puntatori ai file audio memorizzati nell' account qd che: 
o (1) sono dei file audio non lossy oppure (2) sono dei file audio in formato mp3.
7. un metodo di istanza Video* minVideo (unsigned int) con il seguente comportamento: una
invocazione qd.minVideo(fr) ritorna un puntatore sempre non nullo ad un video memorizzato
nell'account qd che: 
(1) abbia un framerate maggiore di fr e (2) abbia dimensione minima tra tutti i video
memorizzati nell'account qd; se un tale video non dovesse essere trovato tra i file
memorizzati nell'account qd allora viene sollevata una eccezione di tipo Exc. 

*/

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
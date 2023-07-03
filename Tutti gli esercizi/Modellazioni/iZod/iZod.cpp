#include <vector>
#include <string>
#include <typeinfo>
class FileAudio{
    private:
        std::string titolo;
        double MB;
    public:
        virtual FileAudio* clone() const=0;
        virtual bool qualita() const=0;
        virtual ~FileAudio() {}
        double getSize() const{return MB; }
        virtual bool operator==(const FileAudio &f) const{
            return typeid(*this) == typeid(f) && titolo == f.titolo && MB == f.MB;
        }
};

class Mp3: public FileAudio{
    private:
        unsigned int bitrate;   //espressa in Kb/s
    public:
        static const unsigned int sogliaQualita;
        virtual Mp3* clone() const{return new Mp3(*this); }  //usando il costr. di copia standard
        virtual bool qualita() const{return bitrate >= sogliaQualita;}
        unsigned int getBitrate() const{return bitrate >= sogliaQualita;}
        //siccome è un overriding la firma della stessa funzione deve essere sempre quella
        //bitrate ha come tipo dinamico almeno mp3
        virtual bool operator==(const FileAudio &f) const{
            return FileAudio::operator==(f) && bitrate==static_cast<const Mp3&>(f).bitrate;
        }
};
const unsigned int Mp3::sogliaQualita=192;

class WAV: public FileAudio{
    private:
        unsigned int frequenza; //in KHz
        bool lossless;          //true sse non ho perdita di qualità
    public:
        static const unsigned int sogliaQualita;
        virtual WAV* clone() const{return new WAV(*this); }  //usando il costr. di copia standard
        virtual bool qualita() const{return frequenza >= sogliaQualita;}
        bool isLossless() const{return lossless;}
        virtual bool operator==(const FileAudio &f) const{
            return FileAudio::operator==(f) && frequenza==static_cast<const WAV&>(f).frequenza &&
            lossless == static_cast<const WAV&>(f).lossless;
        }
};

const unsigned int WAV::sogliaQualita=96;

class iPhone{
    private:
    class Brano{
        public:
            FileAudio* ptr;     //puntatore superpolimorfo
            Brano(FileAudio* p): ptr(p->clone()) {}         //costruzione di copia profonda
            Brano(const Brano& b): ptr(b.ptr->clone()) {}   //costruzione di copia profonda polimorfa
            Brano& operator=(const Brano& b){
                if(this != &b){
                    delete ptr;                             //distr. polimorfa (attenzione alla marcatura del distr. FileAudio)
                    ptr = b.ptr->clone();
                }
                return *this;
            }
            ~Brano() {delete ptr; }
    };
    std::vector<Brano> brani;

    public:
    std::vector<Mp3> mp3(double dim, unsigned int br) const{
        std::vector<Mp3> v;
        for(std::vector<Brano>::const_iterator cit = brani.begin(); cit != brani.end(); ++cit){
            Mp3 *q = dynamic_cast<Mp3*>(cit->ptr);
            if(q && (q->getSize() >= dim && q->getBitrate() >= br))
            v.push_back(*q);
        }
        return v;
    }

    std::vector<FileAudio*> braniQual() const{
        std::vector<FileAudio*> v;
        for(std::vector<Brano>::const_iterator cit = brani.begin(); cit != brani.end(); ++cit){
            //il check sull'OR vuol dire non essere WAV o un suo sottotipo
            if((cit->ptr)->qualita() && (!dynamic_cast<WAV*>(cit->ptr) || static_cast<WAV*>(cit->ptr)->isLossless() ))
            v.push_back(cit->ptr);
        return v;
        }
    }
    //Nella scrittura della funzione di inserimento, si considera l'ereditarietà implicita
    //del brano (superclasse), di cui Mp3 è un chiaro subtype. Richiede quindi un operatore di uguaglianza
    //che non confronta un subtyping, ma l'uguaglianza sul tipo dinamico (perché hanno un tipo diverso, 
    //ma usando il dynamic cast il confronto sarebbe uguale) 
    //--> quindi uso typeid

    void insert(Mp3* m){
        bool found = false;
        //alternativamente uso la keyword auto, che deduce dinamicamente il tipo dal contesto di invocazione, quindi:
        //ad esempio qui: auto it=brani.begin()
        for(std::vector<Brano>::iterator it=brani.begin(); !found && it!=brani.end(); it++){
            found = *(it->ptr) == *m;
            if(!found) brani.push_back(m);
        }
    }
};

int main(){

}
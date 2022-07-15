#include<QVector>
#include<QList>
using namespace std;
class FileAudio {
private:
    unsigned int m_dim;
public:
    virtual FileAudio* Clone() const = 0;
    virtual bool Quality() const = 0;
    virtual ~FileAudio() = default;
    unsigned int getDim() const {return m_dim;}
    void setDim(unsigned int s_dim){m_dim = s_dim;}

};

class Mp3 : public FileAudio{
private:
    unsigned int m_bitRate;
public:
    virtual Mp3* Clone() const{
        return new Mp3(*this);
    }
    virtual bool Quality() const{
        return m_bitRate >= 256;
    }
    unsigned int getBitRate() const{return m_bitRate;}
    void setBitRate(unsigned int s_bitRate){m_bitRate = s_bitRate;}
};
class Wav : public FileAudio{
private:
    unsigned int m_frequenza;
public:
    virtual Wav* Clone() const{
        return new Wav(*this);
    }
    virtual bool Quality() const{
        return m_frequenza >= 192;
    }
};
class MusicPlay{
private: std::list <const FileAudio*> f;

public:

    std::vector<Wav*> QualityWav(double d){
        std::vector<Wav*> aux;
        auto it = f.begin();
        for(; it!= f.end(); ++it)
        {
            const Wav* p = dynamic_cast<const Wav*> (*it);
            if(p && p->getDim() <= d && p->Quality())
                aux.push_back(const_cast<Wav*>(p));
        }
        return aux;
    }

    std::list<FileAudio*> nonConstCopy(){
        std::list<FileAudio*> aux;
        auto it = f.begin();
        for(; it != f.end(); ++it)
        {
            FileAudio* p = const_cast<FileAudio*>(*it);
            aux.push_back(p->Clone());
        }
        return aux;
    }
    std::vector<Mp3> RemoveMp3 (unsigned int br){
        vector<Mp3> aux;
        auto it = f.begin();
        for(; it != f.end(); ++it){
            const Mp3* p = dynamic_cast<const Mp3*> (*it);
            if(p && br>p->getBitRate())
            {
                Mp3* p2 = const_cast<Mp3*>(p);
                aux.push_back(*p2);
            }
        }
        return aux;
    }
};



#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}

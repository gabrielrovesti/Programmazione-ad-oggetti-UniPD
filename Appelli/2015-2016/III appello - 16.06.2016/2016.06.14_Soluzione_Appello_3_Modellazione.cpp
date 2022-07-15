class FileAudio {
private:
    unsigned int dimMB;
    
public:
    virtual FileAudio* clone() = 0;
    virtual bool * quality() const = 0;
    
    unsigned int getDimMB() const {
        return dimMB;
    }//getDimMB.
    
    ~FileAudio(){}
}; //FileAudio.


class Mp3: public FileAudio{
private:
    unsigned int bitrate;
    
public:
    virtual Mp3* clone(){
        return new Mp3(*this);
    }//clone.
    
    virtual bool * quality() const {
        return bitrate >= 256;
    }// quality.
    
    unsigned int getBitRate() const {
        return bitrate;
    }//getBitRate.
    
}; // Mp3.

class Wav : public FileAudio {
private:
    unsigned int frequenza;
    
public:
    virtual Wav * clone()  {
        return new Wav(*this);
    }//clone.
    
    virtual bool * quality() const {
        return frequenza > 192;
    }// quality.
    
};// Wav.


class MusicPlay {
private:
    list<FileAudio*> mp;
    
public:
    vector<WAV*> qualityWAV(double dim){
        vector<WAV*> to_ret;
        list<FileAudio*>::iterator it=mp.begin();
    
        for(; it!=mp.end(); ++it){
            WAV * q= dynamic_cast<WAV*>(*it);
            
            if(q && (*it)->getDimMB() <= dim && (*it)->quality() ){
                to_ret.push_back(q);
            }//if.
        }//for.
        return to_ret;
    }//qualityWAV.
    
    
    list<FileAudio*> nonConstCopy() {
        list<FileAudio*> to_ret;
        list<FileAudio*>::iterator it=mp.begin();
        
        for(; it != mp.end(); ++it){
            to_ret=push_back(*it);
        }//for.
        
        return to_ret;
    }//nonConstCopy.
    
    vector<Mp3> removeMp3(unsigned int br){
        vector<Mp3> to_ret;
        list<FileAudio*>::iterator it=it.begin();
        
        for(; it!=mp.end(); ++it){
            Mp3* file=dynamic_cast<Mp3*>(it);
            
            if(file && (*it)->getBitRate() < br ){
                to_ret=to_ret.push_back(p);
                delete p;
                it=it.erase(it);
                it--;
            }//if.
        }//for.
        return to_ret;
    }//removeMp3.
    
    
}; // MusicPlay.


















class File{
private:
	double dimensione;
	bool accessibile;
public:
	File(double d=0, bool a=false): dimensione(d),accessibile(a){}
	virtual ~File() = 0;
	double getDim() const{ return dimensione;}
	double getAccessibility() const{ return accessibilità;}


};

class Audio: public File{
private:
	bool lossy;
public:
	Audio(bool l=false ): lossy(l);
	bool isLossy() const{ return lossy;}


};

class Mp3:public Audio{
public:
	Mp3(Audio a):a(true){}

};

class Video:public File{
private:
	unsigned int framerate;
public:
	Video(unsigned int fps):framerate(fps){}
	unsigned int getFps() const{ return framerate;}
};

class QooqleDrive{
private:
	std::vector<File*> ptr;
	int capacity;
public:

Audio uploadFile(File& f){

Audio* q = 0;

auto it = ptr.begin();

q = dynamic_cast<Audio*>(f);
if(q && q->getAccessibility() && q->getDim < capacity){
	it.push_end(q);
	return new Audioq);
}
else throw Exc;

			}
list<Audio*> audioCopy(){
	std::list<Audio*> saved;
	Audio* q = 0;

	for(auto it= ptr.begin(); it!= ptr.end(); ++it;){

	q = dynamic_cast<Audio*>(it);
	if(it && !it->isLossy() || dynamic_cast<Mp3*>(it))
		saved.push_back(it);

							}
	return saved;
			}

Video* minVideo(unsigned int f){

int minDim = MAX_INT;
Video* q = 0;
Video* s = 0;
for(auto it=ptr.begin();it!=ptr.end();++it)
{

q = dynamic_cast<Video*>(it);
if(q && q->getFps > f && minDim )
	{
	s = q;
	minDim = q->getDim();


	}


}

if(!s)
	thorw Exc;
else
	return s;
};

class Exc{
private:
	int err;
public:
	Exc(int e=0): err(e){std::cout<<"Eccezione . . .";}

}

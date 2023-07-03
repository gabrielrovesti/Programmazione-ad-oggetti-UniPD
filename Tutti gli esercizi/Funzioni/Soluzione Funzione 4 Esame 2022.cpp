using namespace std;
#include <iostream>
#include <fstream>
#include <vector>

vector<fstream*> Fun (const vector<const ios*>& v){
    vector<fstream*> res;
    for(vector<const ios*>::const_iterator cit=v.begin(); cit!=v.end(); cit++){
        istream *i=dynamic_cast<istream*>(const_cast<ios*>(*cit));
        ostream *o=dynamic_cast<ostream*>(const_cast<ios*>(*cit));
        if(i && o){
            if(i->tellg()>o->tellp()){
                i->setstate(ios::goodbit);
            }
        }
        fstream *f=dynamic_cast<fstream*>(const_cast<ios*>(*cit));
        if(f && (f->rdstate() && std::ifstream::failbit == 0) && f->is_open()){
            f->close();
            res.push_back(f);
        }
        else throw std::exception();
    }
    return res;
}

int main(){

}
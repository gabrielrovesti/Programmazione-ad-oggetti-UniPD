#include <iostream>
#include <vector>
using namespace std;

class Component;

class Container {
public:
	virtual ~Container();
	vector<Component*> getComponents() const;
};

class Component: public Container {};

class Button: public Component {
public:
	vector<Container*> getContainers() const;
};

class MenuItem: public Button {
public:
	void setEnable(bool b = true);
};

class NoButton {};


Button** Fun(const Container& c){
    vector<Button*>* res=new vector<Button*>;
    vector<Component*> v=c.getComponents();
    vector<Component*>::iterator it;
    for(it=v.begin();it!=v.end();++it){
        Button* b=dynamic_cast<Button*>(*it);
        if(b){
            res->push_back(b);
            MenuItem* m=dynamic_cast<MenuItem*>(b);
            if(m && (m->getContainers()).size()>=2)
                m->setEnable(false);
        }
    }
    if(res->size()==0)
        throw NoButton();
	Button* rit = res->front();
    return &rit;
}



int main(){
	
}

	




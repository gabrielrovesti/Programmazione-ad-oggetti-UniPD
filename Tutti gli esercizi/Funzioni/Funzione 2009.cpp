#include <iostream>
#include <vector>
using namespace std;

class Component;

class Container {
    public:
        virtual ~Container() = default;

        /*Il comportamento del metodo getComponents() della classe Container e il seguente: ` c.getComponents() ritorna
        un vector di puntatori a tutte le componenti inserite nel contenitore c; se c non ha alcuna componente allora ritorna un
        vector vuoto*/
        vector<Component*> getComponents() const{
            return vector<Component*>();
        };
};

class Component: public Container {};

class Button: public Component {
    public:
        /*
        Il comportamento del metodo getContainers() della classe Button e il seguente: ` b.getContainers() ritorna un
        vector di puntatori a tutti i contenitori che contengono il pulsante b; se b non appartiene ad alcun contenitore allora ritorna
        un vector vuoto
        */
        vector<Container*> getContainers() const{
            return vector<Container*>();
        };
};

class MenuItem: public Button {
    public:
        bool enabled;
        /*
        Il comportamento del metodo setEnabled() della classe MenuItem e il seguente: ` mi.setEnabled(b) abilita (con
        b==true) o disabilita (con b==false) l’entrata di menu mi
        */
        void setEnabled(bool b = true){
            enabled = b;
        };
};

class NoButton {};

/*
Definire una funzione Button** Fun(const Container&) con il seguente comportamento: in ogni invocazione Fun(c)
1. Se c contiene almeno una componente Button allora
ritorna un puntatore alla prima cella di un array dinamico di puntatori a pulsanti contenente tutti e soli i puntatori ai
pulsanti che sono componenti del contenitore c ed in cui tutte le componenti che sono una entrata di menu e sono
contenute in almeno 2 contenitori vengono disabilitate.
2. Se invece c non contiene nessuna componente Button allora solleva una eccezione di tipo NoButton
*/

Button** Fun(const Container& c){
    vector<Component*> components = c.getComponents();
    vector<Button*> buttons;
    for(auto component: components){
        if(typeid(*component) == typeid(Button)){
            buttons.push_back(dynamic_cast<Button*>(component));
        }
    }
    if(buttons.size() == 0){
        throw NoButton();
    }
    Button** buttonsArray = new Button*[buttons.size()];
    for(int i = 0; i < buttons.size(); i++){
        buttonsArray[i] = buttons[i];
    }
    for(auto button: buttons){
        vector<Container*> containers = button->getContainers();
        if(containers.size() >= 2){
            MenuItem* menuItem = dynamic_cast<MenuItem*>(button);
            if(menuItem != nullptr){
                menuItem->setEnabled(false);
            }
        }
    }
    return buttonsArray;
}

int main(){

};

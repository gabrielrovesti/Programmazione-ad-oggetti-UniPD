
// Classe base astratta (interfaccia)
class Variable {
/*[...]*/
};

// Classe che definisce uno slot di output di un nodo
class Slot {
private:
    // Funzione output
    function<string()> _callback;
public:
    // Costruttore: passa allo slot la funzione che dà l'output
    template<class Callback>
    Slot(Callback f) : _callback(f) {}

    // Restituisce il valore
    string getValue() const {
        return _callback();
    }
};

class Node {
protected:
    // Lista di Slot output
    vector<Slot*> output;
public:
    // TODO: ridefinire distruttore affinche distrugga tutti gli slot
     virtual ~Node() = default;
    // Restituisce l'output di uno slot
    string getOutput(int slot) const{
        // TODO: controllare l'esistenza dello slot

        // Chiama la funzione che prende l'output dello slot
        return output[slot]->getValue();
    }
};

// Classe base che identifica un nodo con un flusso di esecuzione
class NodeExec : public Node {
private:
    // Parametri in input

    // Parametri in output

    // Puntatore al prossimo nodo
    NodeExec* next;
public:
    // Funzione principale che esegue il nodo (da overridare)
    virtual void exec() {

        // Di default esegue il nodo sucessivo
        next->exec();
    }
};

// Classe nodo get variabile
class NodeGetVariable : public NodeNoExec {
private:
    // Puntatore alla variabile che deve settare
    Variable* _variable;
public:
 // Costruttore: setta la variabile e definisce gli slot
    NodeGetVariable(Variable* variable) : _variable(variable) {
        // Crea lo slot
        output.push_back(
            new Slot(
                [this]() -> string {
                    return this->_variable->toString();
                }
            )
        );
    }
};

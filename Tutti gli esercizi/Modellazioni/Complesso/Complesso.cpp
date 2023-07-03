#include <iostream>

using namespace std;

class complesso{
private:
    double reale;
    double immaginario;
public:
    void inizializza (double r, double i){
        reale = r;
        immaginario = i;
    }
    double get_reale(){
        return reale;
    }
    double get_immaginario(){
        return immaginario;
    }
    bool operator==(complesso c){
        return (reale == c.reale && immaginario == c.immaginario);
    }
    bool operator-(complesso c){
        return (reale - c.reale && immaginario - c.immaginario);
    }
    bool operator>(complesso c){
        return (reale > c.reale && immaginario > c.immaginario);
    }
    bool operator <(complesso c){
        return (reale < c.reale && immaginario < c.immaginario);
    }
    bool operator+(complesso c){
        return (reale + c.reale && immaginario + c.immaginario);
    }
};


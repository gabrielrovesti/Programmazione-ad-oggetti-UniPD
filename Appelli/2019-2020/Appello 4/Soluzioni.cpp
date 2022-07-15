//Esercizio 1- ridefinire il costr. di copia che sia come quello standard

E(const E& x): D::D(x), ref(x.ref), p(ref.p)

//Esercizio 2 - Cosa stampa

int main()
{
    Fun<A>(c); cout<<endl; //non compila
    Fun(a1); cout<<endl; //non compila
    Fun(b1); cout<<endl;     //B D::f 
    Fun<D>(e); cout<<endl;   //E E::f
    Fun(b2); cout<<endl;    //E E::f

    Fun<E>(e); cout<<endl;  //E E::f
    Fun(*b3); cout<<endl;   //B B::f
    Fun(*pd1); cout<<endl;  //E E::f
    Fun(e); cout<<endl; //E E::f
    return 0;
}

//Esercizio 3 - Cosa stampa

int main(){
    C x1; cout<<endl;   //C0
    C x2; cout<<endl;   //C0
    E y1; cout<<endl;   //C0 C0 E0
    E y2; cout<<endl;   //C0 E0 E0
    F z1; cout<<endl;   //C0 F0
    F z2; cout<<endl;   //C0 F0
    cout<<endl;
    cout<<"01 ";
    D d1; cout<<endl;   //01 C0 D0
    cout<<"02 ";
    D d2(d1); cout<<endl; //02 C0 Dc
    cout<<"03 ";
    E e1; cout<<endl;   //03 C0 C0 E0
    cout<<"04 ";
    E e2=y1; cout<<endl; //04 Cc Cc
    cout<<"05 non stampa";
    //y1=y2; cout<<endl;
    cout<<"06 ";    
    F* pF= new F(); cout<<endl;  //06  C0  F0
    cout<<"07 ";
    F f=z1; cout<<endl; //07  C0  Fc 
    cout<<"08 ";
    z1=z2; cout<<endl;  //08  C=  E= 
    cout<<"09 ";
    x1=y1; cout<<endl;  //09  C= 
    //z1=x1; cout<<endl;
}

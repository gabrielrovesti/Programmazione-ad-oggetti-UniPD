#include <iostream>
using namespace std;


class contobancario 
{
	int saldo() {return saldo};
	contobancario (int SI) {inf (SI<0) cout "ops"; saldo=SI}
	int preleva (int p) {return saldo+=p};
	int deposita (int p) {return saldo-=p};
	//Correzione: non avevano senso prima preleva e deposita :P
private:
	int saldo;


};



class contocorrente:: public contobancario 
{
	int preleva (int p) {saldo= saldo -p - spesafissa; return saldo};
	int deposita (int p) {saldo= saldo +p - spesafissa; return saldo};

private:
	static int spesafissa;
};



class contorisparmio:: public contocorrente 
{
public:
	int preleva (int p) 
	{
		if (p>saldo) return -1;
		saldo = saldo-p;
		return p;
	}
};



class contoarancio:: public contorisparmio
{
	contoarancio(contocorrente &c)::APP(c) {};
	
	int preleva (int p) //non prelievo ma trasferimento denaro tra conti
	{
		if (p>saldo) return -1;
		APP.deposita(p);
		return saldo-=p;
	}
	
	int deposita (int p) //sempre tra conti
	{
		APP.preleva(p);
		return saldo+=p;
	}
	
private:
	contocorrente &APP;
}




int main () 
{
}

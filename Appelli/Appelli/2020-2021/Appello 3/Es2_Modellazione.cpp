// by Cek

class Abbonato{
private:
	unsigned int trafficoMese; //MB
	unsigned int connessioneMese; //ore
public:
	static const double costoMensileBase;
	static const double extra;
	virtual double costoMeseCorrente() const = 0;
	unsigned int gettrafficoMese() const {return trafficoMese;}
	unsigned int getconnesioneMese() const {return connesioneMese;}
};

const double Abbonato::costoMensileBase = 15;
const double Abbonato::extra = 5;

class AbbonatoTraffico : public Abbonato{
private:
	unsigned int soglia; //GB
public:
	virtual double costoMeseCorrente() const {
		unsigned int sogliaMB = soglia*1024;
		if (gettrafficoMese() <= sogliaMB) return Abbonato::costoMensileBase;
		unsigned int scarto = gettrafficoMese() - sogliaMB;
		unsigned int extraGB = (scarto / 1024) + 1; // +1 perchè paghi anche il GB extra iniziato ma non completamente sfruttato
		return (Abbonato::costoMensileBase + extraGB*Abbonato::extra);
	}
};


class AbbonatoTempo : public Abbonato{
private:
	unsigned int sogliaTempo; //ore
public:
	virtual double costoMeseCorrente() const {
		if (getconnessioneMese() <= sogliaTempo) return Abbonato::costoMensileBase;
		unsigned int scarto = getconnessioneMese() - sogliaTempo;
		return (Abbonato::costoMensileBase + scarto*Abbonato::extra);
	}
	bool isExtra() const {return getconnessioneMese() <= sogliaTempo;}
};

class Exc{
private:
	unsigned int M;
public:
	Exc(unsigned int max) : M(max) {}
};

class FilialeWI{
private:
	unsigned int max;
	unsigned int current;
	std::list<const Abbonato*> abbonati;
public:
	void aggiungiAbbonato(const Abbonato& a) {
		if (current < max) {
			abbonati.push_back(&a);
			current++;
		} else {
			throw Exc(max);
		}
	}
	std::list<const Abbonato*> abbonatiOltreSoglia() {
		std::list<const Abbonato*> w;
		for (auto cit = abbonati.begin(); cit != abbonati.end(); ++cit) {
			const AbbonatoTraffico* atr = dynamic_cast<const AbbonatoTraffico*>(*cit);
			const AbbonatoTempo* ate = dynamic_cast<const AbbonatoTempo*>(*cit);
			if( atr && atr->costoMeseCorrente() > 50 ) {
				w.push_back(atr);
			}
			if ( (ate && ate->costoMeseCorrente() > 50) || (ate && ate->isExtra()) ) {
				w.push_back(ate)
			}
		}
		return w;
	}
};
/*

--- Possibile consegna ---

Si assumano le seguenti specifiche:
La classe wxWindow definisce una finestra grafica generica con alcune proprietà come la visibilità, le dimensioni e il titolo.

La classe wxDialog eredita da wxWindow e aggiunge la possibilità di impostare il fatto che la finestra sia modale, oltre a sovrascrivere il metodo setTitle per non fare nulla.

La classe wxFileDialog eredita da wxDialog e aggiunge la proprietà fd per contenere il nome del file selezionato, oltre al metodo SetFilename per impostare il nome del file.

La classe wxTextEntryDialog eredita da wxDialog e aggiunge la proprietà ted per contenere il testo inserito dall'utente, oltre al metodo SetValue per impostare il testo.

La classe wxPasswordEntryDialog eredita da wxTextEntryDialog e non aggiunge alcuna proprietà o metodo.

Scrivere una funzione void fun(const wxWindow& w) che, data una generica finestra di dialogo:
- se questa corrisponde ad una finestra di immissione password visibile, ne modifica le dimensioni;
- se la finestra è una finestra di impostazione file ed è modale, imposta il nome di default e il titolo "Open File" a quest'ultima;
- se la finestra di tipo widget è visibile, allora ne imposta le dimensioni a (100, 50).

*/


#include <iostream>
using namespace std;

class wxWindow{
private:
	bool visibile;
	int larg, alt;
	string title;
public:
	virtual bool isShown() const {return visibile;}
	virtual void setSize(int l, int a) {larg = l; alt = a;}
	virtual void setTitle (const string & s) {title = s;}
};

class wxDialog : public wxWindow {
private:
	bool modale;
public:
	bool isModal() const {return modale;}
	virtual void setTitle (const string & s) {}
};

class wxFileDialog : public wxDialog {
public:
	string fd;
	void SetFilename( const string & s ) {fd = s;}
};

class wxTextEntryDialog : public wxDialog {
public:
	string ted;
	void SetValue(const string & s) { ted = s; }
};


class wxPasswordEntryDialog : public wxTextEntryDialog {
};

void fun(const wxWindow& w) {
	wxPasswordEntryDialog* pwped = dynamic_cast<wxPasswordEntryDialog*>(const_cast<wxWindow*>(&w));

	if(pwped && pwped->isShown()) pwped->SetValue("password");
	
	wxFileDialog* pfd = dynamic_cast<wxFileDialog*>(const_cast<wxWindow*>(&w));

	if(pfd && pfd->isModal()){ 
		pfd->SetFilename("Default File");
		pfd->setTitle("Open File");
	}
	
	wxWindow* pww = const_cast<wxWindow*>(&w);
	
	if(pww && pww->isShown()) pww->setSize(100, 50);
}
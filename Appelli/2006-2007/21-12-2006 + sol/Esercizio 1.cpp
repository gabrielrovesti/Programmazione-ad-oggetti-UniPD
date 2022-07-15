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
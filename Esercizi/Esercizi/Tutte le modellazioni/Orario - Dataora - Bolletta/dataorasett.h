#ifndef DATAORASETT_H
#define DATAORASETT_H

enum settimana {lun, mar, mer, gio, ven, sab, dom};

class dataorasett : public dataora
{
public:
    settimana GiornoSettimana() const;
private:
    settimana giornosettimana;
};
#endif // DATAORASETT_H

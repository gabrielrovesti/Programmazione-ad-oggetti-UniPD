#ifndef ERRORI_H
#define ERRORI_H
#include<QString>

class Errori
{
public:
  Errori(QString);
  QString get_error()const;
private:
  QString errore;
};

#endif // ERRORI_H

#ifndef QFILM_H
#define QFILM_H
#include <QString>

class qFilm
{
public:
    qFilm();
    qFilm(QString tytulPL, QString tytulEN, int dlugosc, int plyta, QString kom);

    QString tytulPL;
    QString tytulEN;
    int dlugosc;
    int plyta;
    QString koment;
};

#endif // QFILM_H

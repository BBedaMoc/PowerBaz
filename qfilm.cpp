#include "qfilm.h"

qFilm::qFilm()
{

}

qFilm::qFilm(QString tytulPL, QString tytulEN, int dlugosc, int plyta, QString kom){
    this->tytulPL=tytulPL;
    this->tytulEN=tytulEN;
    this->dlugosc=dlugosc;
    this->plyta=plyta;
    this->koment=kom;
}

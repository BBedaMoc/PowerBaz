#include "dialog3.h"
#include "ui_dialog3.h"
#include "qfilm.h"

Dialog3::Dialog3(qFilm *film, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3)
{
    ui->setupUi(this);
    this->film=film;
    if(film!=NULL){
        ui->lEtytulPL->setText(film->tytulPL);
        ui->lEtytulEN->setText(film->tytulEN);
        int a=film->dlugosc;
        int b=a%60;
        int c=(a-b)/60;
        ui->lEDh->setText(QString().setNum(c));
        ui->lEDm->setText(QString().setNum(b));
        ui->lEnP->setText(QString().setNum(film->plyta));
        ui->pTEkom->setPlainText(film->koment);
        this->setWindowTitle(QString("Edytuj: ")+film->tytulPL);
    }
}

Dialog3::~Dialog3()
{
    delete ui;
}

void Dialog3::on_buttonBox_accepted()
{
    film->tytulPL=ui->lEtytulPL->text();
    film->tytulEN=ui->lEtytulEN->text();
    film->plyta=ui->lEnP->text().toInt();
    film->dlugosc=60*ui->lEDh->text().toInt()+ui->lEDm->text().toInt();
    film->koment=ui->pTEkom->toPlainText();
    QString opis="Tytuł polski:\n"+film->tytulPL+"\n\nTytuł oryginału:\n"+film->tytulEN+"\n\nNr płyty: "+QString().setNum(film->plyta)+"     Długość: "+QString().setNum(film->dlugosc)+"\n\nKomentarz:\n"+film->koment;
    emit changeOp(opis);
    close();
}

void Dialog3::on_buttonBox_rejected()
{
    close();
}

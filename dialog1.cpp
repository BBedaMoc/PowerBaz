#include "dialog1.h"
#include "ui_dialog1.h"
#include "qfilm.h"

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
    elem=NULL;
}

Dialog1::~Dialog1()
{

    delete ui;
}

void Dialog1::on_buttonBox_accepted()
{
    elem=new qFilm();
    elem->tytulPL=ui->lEtytulPL->text();
    elem->tytulEN=ui->lEtytulEN->text();
    elem->koment=ui->pTEkom->toPlainText();
    elem->dlugosc=ui->lEDh->text().toInt()*60+ui->lEDm->text().toInt();
    elem->plyta=ui->lEnP->text().toInt();
    emit accepted(elem);

    close();
}

void Dialog1::on_buttonBox_rejected()
{
    close();
}

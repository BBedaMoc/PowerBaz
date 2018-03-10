#include "dialog2.h"
#include "ui_dialog2.h"
#include "dialog3.h"
#include "dialog4.h"
#include "qfilm.h"

Dialog2::Dialog2(QString text, QString tytol, qFilm *f, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{

    ui->setupUi(this);
    this->text = text;
    ui->pTEopis->setPlainText(text);
    this->setWindowTitle(tytol);
    film=f;

}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::on_pushButton_3_clicked()
{
    close();
}

void Dialog2::on_pushButton_clicked()
{

    Dialog3* u=new Dialog3(film);
    u->setAttribute(Qt::WA_DeleteOnClose);
    connect(u,SIGNAL(changeOp(QString)),this,SLOT(setOpis(QString)));
    u->show();
}


void Dialog2::on_pushButton_2_clicked()
{
    if(film!=NULL){
        Dialog4* u2=new Dialog4("Czy na pewno chcesz usunąć film:\n"+film->tytulPL+" ?");
        u2->parent=this;
        u2->setAttribute(Qt::WA_DeleteOnClose);
        connect(u2,SIGNAL(toDelete(bool)),this,SLOT(toDelete(bool)));
        u2->show();
    }
}

void Dialog2::toDelete(bool f){
    if(f) emit removeFilm(film);
    close();
}

void Dialog2::setOpis(QString opis){
    ui->pTEopis->setPlainText(opis);
    emit edited(film);
}


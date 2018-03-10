#include "dialog4.h"
#include "ui_dialog4.h"

Dialog4::Dialog4(QString op,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog4)
{
    ui->setupUi(this);
    ui->label->setText(op);
}

Dialog4::~Dialog4()
{
    delete ui;
}

void Dialog4::on_pushButton_2_clicked()
{
    emit toDelete(true);
    close();
}

void Dialog4::on_pushButton_clicked()
{
    emit toDelete(false);
    close();
}

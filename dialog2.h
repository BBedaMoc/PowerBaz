#ifndef DIALOG2_H
#define DIALOG2_H

#include <QDialog>
#include <QPlainTextEdit>
#include "mainwindow.h"

namespace Ui {
class Dialog2;
}

class qFilm;
class Dialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2(QString text,QString tytol, qFilm *f ,QWidget *parent = 0);
    ~Dialog2();
    MainWindow * parent;

    QString text;
    QString tytol;
    qFilm *film;

signals:
    void removeFilm(qFilm *f);
    void edited(qFilm *f);

public slots:
    void setOpis(QString opis);


private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void toDelete(bool f);





    void on_pushButton_2_clicked();

private:
    Ui::Dialog2 *ui;
};

#endif // DIALOG2_H

#ifndef DIALOG3_H
#define DIALOG3_H

#include <QDialog>
#include "dialog2.h"

namespace Ui {
class Dialog3;
}

class qFilm;
class Dialog3 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog3(qFilm* film, QWidget *parent = 0);
    ~Dialog3();
    qFilm *film;

signals:
    void changeOp(QString op);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dialog3 *ui;
};

#endif // DIALOG3_H

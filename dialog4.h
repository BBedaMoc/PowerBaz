#ifndef DIALOG4_H
#define DIALOG4_H

#include <QDialog>
#include "dialog2.h"

namespace Ui {
class Dialog4;
}

class Dialog4 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog4(QString op,QWidget *parent = 0);
    ~Dialog4();
    Dialog2* parent;


signals:
    void toDelete(bool flag);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Dialog4 *ui;
};

#endif // DIALOG4_H

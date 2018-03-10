#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>
#include <QList>

namespace Ui {
class Dialog1;
}

class qFilm;
class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = 0);
    ~Dialog1();
    qFilm *elem;

signals:
    void accepted(qFilm *nFilm);


private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::Dialog1 *ui;
};

#endif // DIALOG1_H

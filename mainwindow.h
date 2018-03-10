#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QMap>
#include <QList>



namespace Ui {
class MainWindow;
}

class qFilm;
class QXmlStreamWriter;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setLicznik(int liczba);
    void reset();

private slots:
    void on_actionDodaj_Nowy_Film_triggered();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_pushButton_clicked();
    void on_comboBox_activated(int index);

    void resizeEvent(QResizeEvent *event);
    void newFilmAdded(qFilm *film);
    void filmDeleted(qFilm *film);
    void filmChanged(qFilm *film);


private:
    void writeList();
    void loadList();
    void writeFilm(qFilm *film, QXmlStreamWriter *writer);



    Ui::MainWindow *ui;    
    QMap <int, qFilm*> len, disc;
    QList <qFilm*> elem;

};

#endif // MAINWINDOW_H

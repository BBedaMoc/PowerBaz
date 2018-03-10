#include "mainwindow.h"

#include <QApplication>
#include "plik.h"




int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow* w;
    int k=9;
    w = new MainWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);    
    w->show();


    return a.exec();
}

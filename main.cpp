#include "mainwindow.h"

#include <QApplication>
#include "plik.h"




int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow* w;
    w = new MainWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);    
    w->show();
	int z=0;


    return a.exec();
}

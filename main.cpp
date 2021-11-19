#include "mainwindow.h"

#include <QApplication>







int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;



    w.resize(800, 800);
    w.setWindowTitle("Distribution Modeling");

      w.show();
     return a.exec();
}







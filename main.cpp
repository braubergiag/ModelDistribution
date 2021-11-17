#include "mainwindow.h"

#include <QApplication>

#include "Distribution.h"
#include "Generator.h"
#include "Histogram.h"
#include "TID_Generator.h"
#include "TISM_Generator.h"
void DrawHist();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;



    w.resize(800, 800);

      w.show();
     return a.exec();
}







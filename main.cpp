#include "mainwindow.h"
#include <QApplication>
#include "defines.h"
#include "espendata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.show();


    return a.exec();
}




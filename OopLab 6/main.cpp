#include "mainwindow.h"
#include <QApplication>
#include "target.h"
#include <iostream>
class Form
{
public:

    Form() {

    }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}

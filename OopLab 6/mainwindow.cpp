#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "target.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Target *t = new Target(85.0f, 85.0f, 200.0f, 200.0f);
    t->GenerateFigures(0);
    t->FreeAreaofTarget();
    //std::cout << t.area * 100  <<  "%" << "Free Area";
    ui->statusBar->showMessage("Free Area" + QString::number(t->area * 100));
}

MainWindow::~MainWindow()
{
    delete ui;
}

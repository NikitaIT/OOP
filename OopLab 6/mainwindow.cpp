#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "target.h"
#include <string>
#include <sstream>
#include <memory>

class Calc{
public:
    struct config{
        float widht;
        float height;
        int figuresCount;
        int iterationCount;
    };
    static double CalculateArea(config c){
        auto t = new Target(1000, 1000, c.widht, c.height);
        t->GenerateFigures(c.figuresCount);
        t->FreeAreaofTarget(c.iterationCount);
        return t->area;
    }
};




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Target *t = new Target(85.0f, 85.0f, 200.0f, 200.0f);
   // t->GenerateFigures(0);
    //t->FreeAreaofTarget();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    Calc::config a;
    a.widht = (float)ui->sbWidth->value();
    a.height = (float)ui->sbHight->value();
    a.figuresCount = ui->sbFiguresCount->value();
    a.iterationCount = ui->sbRandomScanCount->value();
    auto area = Calc::CalculateArea(a);
    std::ostringstream buff;
    buff<< area * 100;buff<<  " % " << "Free Area";
    qDebug(buff.str().c_str());
    ui->statusBar->showMessage(buff.str().c_str());
}

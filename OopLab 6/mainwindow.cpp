#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "target.h"
#include <string>
#include <sstream>
#include <memory>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    calc = new Calc();
}

MainWindow::~MainWindow()
{
    delete calc;
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    Calc::config configuration = calc->GetConf();
    configuration.widht = (float)ui->sbWidth->value();
    configuration.height = (float)ui->sbHight->value();
    configuration.figuresCount = ui->sbFiguresCount->value();
    this->setResult(configuration);
}

void MainWindow::on_pushButton_clicked()
{
    this->setResult(calc->GetConf());
}

void MainWindow::setResult(Calc::config configuration)
{
    configuration.iterationCount = ui->sbRandomScanCount->value();
    configuration.regularScanW = ui->sbRegularScanIntervalStart->value();
    configuration.regularScanH = ui->sbRegularScanIntervalEnd->value();
    configuration.isRandomScan = ui->cbRandomScanCount->isChecked();
    configuration.isRegularScan = ui->cbRegularScanInterval->isChecked();

    float area = calc->CalculateArea(configuration);
    std::ostringstream buff;
    buff<< area * 100;buff<<  " % " << "Free Area";
    qDebug(buff.str().c_str());
    ui->statusBar->showMessage(buff.str().c_str());
    if(area!=0){
        ui->lArea->setText( QString::number(calc->CalculateAreaSize(area)/area) );
    }
    ui->lFreeArea->setText( QString::number(calc->CalculateAreaSize(area)) );
}

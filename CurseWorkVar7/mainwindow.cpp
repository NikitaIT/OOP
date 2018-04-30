#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    live(new Live())
{
    ui->setupUi(this);
    ui->cashe1->setValue(3);
    ui->cashe2->setValue(1);
    ui->secPerMinute->setValue(60);
    ui->clock->setValue(2);
    live->Start();
    connect(ui->actionStart, SIGNAL(triggered()), this, SLOT(OnStart()));
    connect(ui->actionStop, SIGNAL(triggered()), this, SLOT(OnStop()));
    connect(ui->actionReStart, SIGNAL(triggered()), this, SLOT(OnReStart()));
    connect(ui->actionStatistic, SIGNAL(triggered()),this, SLOT(OnStatistic()));
    connect(live, SIGNAL(StateChange()),this, SLOT(OnStateChange()));
    OnReStart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnStart()
{
    live->Start();
}

void MainWindow::OnStop()
{
    live->Stop();
}

void MainWindow::OnReStart()
{
    if(ui->cashe1->value() <= 0
            || ui->cashe2->value() <= 0
            || ui->clock->value() <= 0
            || ui->secPerMinute->value() <= 0)
        return;
    live->SetParams(ui->cashe1->value(),ui->cashe2->value(),ui->clock->value(), ui->secPerMinute->value());
}

void MainWindow::OnStateChange()
{
    auto st = live->stores.first();
    auto f =  st->_dequeEmployes.first();
    auto s =  st->_dequeEmployes.at(1);
    ui->PeopleCount1->setNum(f->isInProcess());
    ui->PeopleCount2->setNum(s->isInProcess());
    ui->PeopleCount3->setNum(st->Count()>2);
    ui->PeopleCount4->setNum(st->Count()>3);
}

void MainWindow::OnStatistic()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Статистика");
    msgBox.setText(QString("Среднее число клиентов в здании = %1 СКО =  %2")
                   .arg(live->statistic.Mean())
                   .arg(std::sqrt(live->statistic.Sd())));
    msgBox.exec();
}

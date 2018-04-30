#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    live(new Live())
{
    ui->setupUi(this);
    ui->cashe1->setValue(1);
    ui->cashe2->setValue(1);
    ui->secPerMinute->setValue(1);
    ui->clock->setValue(90);
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
    auto f = live->stores.first();
    auto s = live->stores.at(1);
    if(f->order == 1){
        ui->PeopleCount1->setNum(f->Count());
        ui->PeopleCount2->setNum(s->Count());
    } else{
        ui->PeopleCount1->setNum(s->Count());
        ui->PeopleCount2->setNum(f->Count());
    }
}

void MainWindow::OnStatistic()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Статистика");
    msgBox.setText(QString("Среднее число обслуживаний в минуту = %1 СКО =  %2")
                   .arg(live->statistic.Mean())
                   .arg(std::sqrt(live->statistic.Sd())));
    msgBox.exec();
}

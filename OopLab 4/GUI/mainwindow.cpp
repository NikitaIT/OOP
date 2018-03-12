#include "./mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(this, SIGNAL(fileOpened(QString)), ui->Graph, SLOT(openFile(QString)));
    connect(ui->Graph, SIGNAL(cantReadFileWithMatrix()), this, SLOT(reopenFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()){
        emit fileOpened(fileName);
    }
}

void MainWindow::reopenFile()
{
    QErrorMessage* fileErr = new QErrorMessage(this);
    fileErr->showMessage(tr("Sorry, i can't load your file. Check file structure, or file right."));
}

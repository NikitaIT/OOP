#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphwindow.h"
#include <QFileDialog>
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action,SIGNAL(triggered(bool)),this,SLOT(showGraph()));
    connect(ui->action_3,SIGNAL(triggered(bool)),this,SLOT(generateEvent()));
    connect(ui->action_2,SIGNAL(triggered(bool)),this,SLOT(generateEvents()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showGraph()
{

    QObject *tmp = new QObject();
    foreach (tmp, this->children())
        if(tmp->objectName() == "GraphWindow")
            delete (graphWindow);

   graphWindow= new GraphWindow(this);
   connect(this,SIGNAL(makeGraph(graph&,matrix&)),graphWindow,SLOT(createGraph(graph&,matrix&)));
   graphWindow->show();
   if(!ui->pathToFile1->text().isEmpty() && !ui->pathToFile1->text().isEmpty())
    emit(makeGraph(Graph,Map));




}
void MainWindow::generateEvent(){
    srand(time(0));
    int eventJ = rand()%Graph.count;
    QString event;
    event.setNum(eventJ);
    event = "J" + event;
    ui->lastEvent->setText(event);
    if(Graph.relations(Graph.currentEdge,eventJ)){
        Graph.currentEdge = Graph.relations(Graph.currentEdge,eventJ) - 1;
        QString state;
        state.setNum(Graph.currentEdge+1);
        state = "S" + state;
        ui->prevState->setText(ui->currentState->text());
        ui->currentState->setText(state);
        emit(makeGraph(Graph,Map));
    }


}
void MainWindow::generateEvents(){
    if(tmr == NULL){
    tmr = new QTimer();
    tmr->setInterval(500);
    connect(tmr, SIGNAL(timeout()), this, SLOT(generateEvent()));
    tmr->start();
}
    else{
        disconnect(tmr, SIGNAL(timeout()), this, SLOT(generateEvent()));
        delete tmr;

    }
}

QString MainWindow::openFile()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
   QString path;
    if(dialog.exec()){
        fileNames = dialog.selectedFiles();
    }

    if(!fileNames.isEmpty())
         path = fileNames.at(0);

    return path;

}

void MainWindow::on_openFile1_clicked()
{
    ui->pathToFile1->setText(MainWindow::openFile());
}

void MainWindow::on_openFile2_clicked()
{
    ui->pathToFile2->setText(MainWindow::openFile());
}

void MainWindow::on_pathToFile1_textChanged(const QString &arg1)
{
    int count = 0;
    QStringList lines;

    QFile file(ui->pathToFile1->text());
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
       while (!in.atEnd()) {
           QString line = in.readLine();
           line.remove(" ");
           lines << line;
           count++;
       }
       int *relation = new int[count*count];
       for(int i = 0, k = 0; i < lines.size(); k+=count, i++){
           QString tmp = lines.at(i);
           for (int j = 0; j < count; j++){
               relation[j+k] = (tmp[j].unicode())-48;
              // qDebug() << relation[i+j];
           }
       }

       Graph.count = count;
       Graph.relations = matrix(count,count,relation);
       Graph.currentEdge = 0;
       ui->currentState->setText("S1");
      //  for(int i = 0 ; i < count; i++)
       //   for (int j = 0; j < count; j++)
        //       qDebug() << Graph.relations(i,j);
}

void MainWindow::on_pathToFile2_textChanged(const QString &arg1)
{
        int row = 0;
        int col = 0;
        int count = 0;
        QStringList lines;


        QFile file(ui->pathToFile2->text());
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;

        QTextStream in(&file);
           while (!in.atEnd()) {
               QString line = in.readLine();
               line.remove(" ");
               lines << line;
               row++;
               if(!col)
                   col = line.size();
           }

           int *map = new int[col*row];
           for(int i = 0, k = 0; i < lines.size(); k+=col, i++){
               QString tmp = lines.at(i);
               for (int j = 0; j < col; j++){
                   if(count < (tmp[j].unicode()-48))
                       count = tmp[j].unicode()-48;
                     map[j+k] = tmp[j].unicode()-48;
                   }
               }
           Map = matrix(row,col,map);
           countFromMap = count;
           //for(int i = 0 ; i < row; i++)
           //     for (int j = 0; j < col; j++)
            //         qDebug() << Map(i,j);
    }


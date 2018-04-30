#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtGui>
#include "graph.h"
#include "graphwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();




signals:
    void makeGraph(graph&,matrix&);

private slots:
    void showGraph();
    void on_openFile1_clicked();
    void on_openFile2_clicked();
    void on_pathToFile1_textChanged(const QString &arg1);
    void on_pathToFile2_textChanged(const QString &arg1);
    void generateEvent();
    void generateEvents();

private:
    Ui::MainWindow *ui;
    GraphWindow *graphWindow;
    QString openFile();
    graph Graph;
    matrix Map;
    int countFromMap;
    QTimer *tmr;

};

#endif // MAINWINDOW_H

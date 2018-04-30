#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "live.h"
#include <QMessageBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Live *live;

private slots:
    void OnStart();
    void OnStop();
    void OnReStart();
    void OnStateChange();
    void OnStatistic();


};

#endif // MAINWINDOW_H

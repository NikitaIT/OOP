#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphwidget.h"
#include <QFileDialog>
#include <QErrorMessage>

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
    void fileOpened(QString filename);
private slots:
    void openFile();
    void reopenFile();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

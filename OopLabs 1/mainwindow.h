#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<iomanip>
#include <vector>
#include <sstream>
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include "polynom.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void calculateValue();
    void calculateRoots();
    bool lineEditorValueChanged(const QString &);
private:
    Ui::MainWindow *ui;
    QList<QLabel*> _labels;
    QList<QLineEdit*> _lineEditors;
    Polynom<double> _polynom;
};

#endif // MAINWINDOW_H

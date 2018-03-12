#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../Shared/include.h"
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include "polynom.h"
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    typedef QLabel* TContainer;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void calculateValue();
    void calculateRoots();
    bool lineEditorValueChanged(const QString &);
private slots:
    void on_sbDimension_valueChanged(int arg1);

private:
    QGridLayout *addLayout(Matrix n,QGridLayout *l, int row, int column);
    bool readLayout(QGridLayout* layout, Matrix &n);
    void calculateValue(TContainer container);
    void setValidators();
    void onInit(size_t dimension);
    Ui::MainWindow *ui;
    QList<QLabel*> _lables;
    QList<QGridLayout*> _layouts;
    Polynom<Matrix> _polynom;
};

#endif // MAINWINDOW_H

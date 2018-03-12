#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polynom.h"
#include "parse.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->onInit(2);
}
MainWindow::~MainWindow()
{
    qDeleteAll(_lables);
    _lables.clear();
    qDeleteAll(_layouts);
    _layouts.clear();
    delete ui;
}

void MainWindow::calculateValue()
{
    if(!this->lineEditorValueChanged(""))
        return;
    auto num = new Matrix(_polynom.Koefs->at(0).get_rows(),_polynom.Koefs->at(0).get_cols(),0);
    auto lay = (QGridLayout *)ui->leValueGridLayout->itemAt(0);
    if(readLayout(lay,*num)){
        auto value = _polynom.calculateValue(*num);
        auto sa = QString::fromStdString(_polynom.ToString());
        sa.replace(QRegExp("X"),"*" + Parse::parse(*num));
        sa.append(" = " + Parse::parse(value));
        ui->statusBar->showMessage(sa);
        addLayout(value, ui->labelValueGridLayout,0,0);
    }else{
        addLayout(Matrix(num->get_rows(),num->get_cols(),0), ui->labelValueGridLayout,0,0);
    }

}

void MainWindow::calculateRoots()
{
    if(!this->lineEditorValueChanged(""))
        return;
    auto roots = _polynom.calculateRoots();
    if(roots == NULL)
    {
        ui->statusBar->showMessage("NaN");
        return;
    }
    addLayout(roots->first,ui->labelRoot1GridLayout,0,0);
    addLayout(roots->second,ui->labelRoot2GridLayout,0,0);
}
QGridLayout *MainWindow::addLayout(Matrix n,QGridLayout *l, int row, int column){
    auto layout = new QGridLayout(this);
    for (unsigned i=0; i<n.get_rows(); i++) {
        for (unsigned j=0; j<n.get_cols(); j++) {
            auto lineEditor = new QLineEdit(this);
            if(i!=j){
                lineEditor->setDisabled(true);
            }
            lineEditor->setText(Parse::parse(n(i,j)));
            layout->addWidget(lineEditor, i, j);
        }
    }
    l->addLayout(layout,row,column);
    return layout;
}
bool MainWindow::lineEditorValueChanged(const QString &)
{
    size_t c = 0;
    for (auto layout : _layouts)
    {
        if(!readLayout(layout,_polynom.Koefs->at(c))){
            return false;
        }
        c++;
    }
    return true;
}
//todo: методы с сайд-эффектами пишут только говнари
bool MainWindow::readLayout(QGridLayout* layout,Matrix &n){
    bool ok;
    auto layouta = layout->rowCount();

    for (unsigned i=0; i<layout->rowCount(); ++i) {
        for (unsigned j=0; j<layout->columnCount(); j++) {
            auto lineEditor = (QLineEdit *)layout->itemAtPosition(i,j)->widget();
            auto num = Parse::parse(lineEditor->text(),&ok);
            if(!ok){
                ui->statusBar->showMessage("Error in input №"+QString::number(i) +" Exemple:12.405");
                return false;
            }
            n(i,j) = num;
        }
    }
    return ok;
}
void clearLayout(QLayout * layout) {
   if (! layout)
      return;
   while (auto item = layout->takeAt(0)) {
      delete item->widget();
      clearLayout(item->layout());
   }
}
void MainWindow::onInit(size_t dimension)
{

    clearLayout(ui->leValueGridLayout);
    clearLayout(ui->labelValueGridLayout);
    clearLayout(ui->labelRoot1GridLayout);
    clearLayout(ui->labelRoot2GridLayout);
    size_t r = 0;
    while (auto item = ui->polynomLayout->takeAt(0)) {
        if(r%2){
            clearLayout(item->layout());
        } else{
            delete item->widget();
            clearLayout(item->layout());
        }
        r++;
    }
    clearLayout(ui->polynomLayout);

    qDeleteAll(_lables);
    _lables.clear();
    qDeleteAll(_layouts);
    _layouts.clear();
    _lables.reserve(3);
    _polynom.Koefs->clear();
    _polynom.Koefs->reserve(3);
    _polynom.Koefs->push_back( Matrix(dimension,0));
    _polynom.Koefs->push_back( Matrix(dimension,0));
    _polynom.Koefs->push_back( Matrix(dimension,0));

    addLayout(Matrix(dimension,0),ui->leValueGridLayout, 0, 0);
    addLayout(Matrix(dimension,0),ui->labelValueGridLayout, 0, 0);
    addLayout(Matrix(dimension,0),ui->labelRoot1GridLayout, 0, 0);
    addLayout(Matrix(dimension,0),ui->labelRoot2GridLayout, 0, 0);
    size_t i = 0;
    for (auto n : *_polynom.Koefs)
    {
        auto label = new QLabel(this);
        label->setText(Polynom<double>::GetX(i).c_str());

        _layouts.append(addLayout(n,ui->polynomLayout,0,i*2));
        _lables.append(label);
        ui->polynomLayout->addWidget(_lables.back(),0,i*2+1);
        i++;
    }
    ui->statusBar->showMessage(_polynom.ToString().c_str());
}
void MainWindow::calculateValue(MainWindow::TContainer container)
{
}

void MainWindow::on_sbDimension_valueChanged(int dimension)
{
    this->onInit(dimension);
}


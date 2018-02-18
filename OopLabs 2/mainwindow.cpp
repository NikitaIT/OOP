#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polynom.h"

QString parse(double n){
  return QString::number(n);
}
QString parse(complex<double> n){
  return QString::number(n.real())+QString::number(n.imag());
}

complex<double> parse(QString n, bool *ok = 0){
  auto com = new complex<double> (0,0);
  bool ok1,ok2;
  QRegExp ii("i");
  QRegExp reg("[\\s]");
  n.replace(reg, "");
  QRegExp isTooDouble("([0-9]+[i]?)([+-]+)([+-]?[i]?[0-9.,]+[i]?)");
  if (isTooDouble.indexIn(n) >= 0) {
      QRegExp rx("([+|-]?[0-9.,]+)([a-zA-Z0-9]*)([+-]?[i]?[0-9.,]+[i]?)");

      if (rx.indexIn(n) >= 0) {
          if(rx.cap(2)!="i"){
              if(ii.indexIn(rx.cap(3))>= 0){
                  com->real(rx.cap(1).replace(ii, "").toDouble(&ok1));
                  com->imag(rx.cap(3).replace(ii, "").toDouble(&ok2));
              } else{
                    com->real(rx.cap(1).replace(ii, "").toDouble(&ok1)+rx.cap(3).replace(ii, "").toDouble(&ok2));
                }
          } else{
              QRegExp rdx("([+|-]?[i]?[0-9.,]+[i]?)([a-zA-Z0-9]*)([+-]?[0-9.,]+)");

              if (rdx.indexIn(n) >= 0) {
                  if(ii.indexIn(rdx.cap(1))>= 0){
                      com->real( rdx.cap(3).replace(ii, "").toDouble(&ok1));
                      com->imag( rdx.cap(1).replace(ii, "").toDouble(&ok2));
                    } else{
                      ok1 = ok2=false;
                    }
                }
            }

        }

    }else{
      if (ii.indexIn(n) >= 0) {
          n.replace(ii, "");
          com->imag(n.toDouble(&ok2));ok1=true;
        }else
        {
          com->real(n.toDouble(&ok1));ok2=true;
        }

    }
  *ok = ok1 && ok2;
  return *com;
}
/*
double parse(QString n, bool *ok = 0){
  return n.toDouble(ok);
}
*/
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  _labels.reserve(3);
  //auto sd=new QDoubleValidator(-1100, 1100, 4, this);
  //sd->setLocale(QLocale::Interlingua);
  //ui->leValue->setValidator( sd );

  _polynom.Koefs->push_back(0);
  _polynom.Koefs->push_back(0);
  _polynom.Koefs->push_back(0);

  size_t i = 0;
  for (auto n : *_polynom.Koefs)
    {
      auto label = new QLabel(this);
      auto lineEditor = new QLineEdit(this);
      label->setText(Polynom<double>::GetX(i).c_str());
      lineEditor->setText(parse(n));
      _lineEditors.append(lineEditor);
      _labels.append(label);
      ui->polynomLayout->addWidget(_lineEditors.back());
      ui->polynomLayout->addWidget(_labels.back());
      i++;
    }
  ui->statusBar->showMessage(_polynom.ToString().c_str());
}

MainWindow::~MainWindow()
{
  qDeleteAll(_labels);
  _labels.clear();
  qDeleteAll(_lineEditors);
  _lineEditors.clear();
  delete ui;
}

void MainWindow::calculateValue()
{
  if(!this->lineEditorValueChanged(""))
    return;
  stringstream str;
  bool isNum = false;
  if(ui->leValue->hasAcceptableInput()){
      auto num = parse(ui->leValue->text(),&isNum);
      if(isNum){
          str << _polynom.calculateValue(num);
          auto sa = QString::fromStdString(_polynom.ToString());
          sa.replace(QRegExp("X"),"*" + ui->leValue->text());
          sa.append(" = " + QString::fromStdString(str.str()));
          ui->statusBar->showMessage(sa);
        }else{
          str<<"NaN";
        }
    }else{
      str<<"NotValid";
    }
  ui->labelValue->setText( str.str().c_str() );

}

void MainWindow::calculateRoots()
{
  if(!this->lineEditorValueChanged(""))
    return;
  auto roots = _polynom.calculateRoots();
  if(roots == NULL)
    {
      ui->labelRoot1->setText("NaN");
      ui->labelRoot2->setText("NaN");
      return;
    }
  ui->labelRoot1->setText( parse(roots->first) );
  ui->labelRoot2->setText( parse(roots->second) );

}

bool MainWindow::lineEditorValueChanged(const QString &)
{
  size_t i = 0;
  bool ok;
  for (auto lineEditor : _lineEditors)
    {
      auto num = parse(lineEditor->text(),&ok);
      if(!ok){
          ui->statusBar->showMessage("Error in input №"+QString::number(i) +" Exemple:12.405");
          return false;
        }
      _polynom.Koefs->at(i) = num;
      i++;
    }
  return true;
}

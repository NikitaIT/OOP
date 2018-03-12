#ifndef PARSE
#define PARSE
#include "include.h"
#include "matriximpl.h"
using namespace std;
class Parse
{
public:
    static QString parse(double n){
        return QString::number(n);
    }
    static QString parse(std::complex<double> n){
        QString res;
        if (n.real() != 0)
        {
            res.append(QString::number(n.real()));
            if (n.imag() > 0)
            {
                res.append("+");
            }
        } else if (n.imag() == 0){
            res.append("0");
        }

        if (n.imag() != 0)
        {
            res.append(QString::number(n.imag())+"i");
        }
        return res;
    }
    static QString parse(Matrix n){
        return QString::fromStdString(n.toString());
    }
    static std::complex<double> parse(QString n, bool *ok = 0){
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
  static double parse(QString n, bool *ok = 0){
    return n.toDouble(ok);
  }

  static Matrix<std::complex<double>> parse(QString n, bool *ok = 0){

  }*/
};

#endif // PARSE


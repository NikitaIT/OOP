#ifndef __QS_MATRIX_H
#define __QS_MATRIX_H

#include <complex>
#include <vector>
#include <QString>
#include <string>
template <typename T> class QSMatrix {
protected:
    std::vector<std::vector<T> > mat;
    unsigned rows;
    unsigned cols;

public:
    QSMatrix(unsigned _rows, unsigned _cols, const T& _initial);
    QSMatrix(const QSMatrix<T>& rhs);

    QSMatrix(unsigned _rows,const int& _initial):QSMatrix(_rows, _rows, std::complex<double>(_initial)){}
    QSMatrix<T> *GetEqualScale(const int& _initial){
        return new QSMatrix<T>(this->rows,this->cols, T(_initial));
    }
    std::string toString(){
        std::stringstream s("");
        s<<"d(";bool fst = false;
        for(std::complex<double> c : this->diag_vec()){
            if(fst){
                s<< ",";
            }
            fst = true;
            QString res;
            auto n = c;
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
            s<< res.toStdString();
        }
        s<< ")";
        return s.str();
    }
    virtual ~QSMatrix();

    // Operator overloading, for "standard" mathematical matrix operations
    QSMatrix<T>& operator=(const QSMatrix<T>& rhs);

    // Matrix mathematical operations
    QSMatrix<T> operator+(const QSMatrix<T>& rhs);
    QSMatrix<T>& operator+=(const QSMatrix<T>& rhs);
    QSMatrix<T> operator-(const QSMatrix<T>& rhs);
    QSMatrix<T>& operator-=(const QSMatrix<T>& rhs);
    QSMatrix<T> operator*(const QSMatrix<T>& rhs);
    QSMatrix<T>& operator*=(const QSMatrix<T>& rhs);
    QSMatrix<T> transpose();
    bool operator==(QSMatrix<T>& rhs)const;
    // Matrix/scalar operations
    QSMatrix<T> operator+(const T& rhs);
    QSMatrix<T> operator-(const T& rhs);
    QSMatrix<T> operator*(const T& rhs);
    QSMatrix<T> operator/(const T& rhs);

    // Matrix/vector operations
    std::vector<T> operator*(const std::vector<T>& rhs);
    std::vector<T> diag_vec();

    // Access the individual elements
    T& operator()(const unsigned& row, const unsigned& col);
    const T& operator()(const unsigned& row, const unsigned& col) const;

    // Access the row and column sizes
    unsigned get_rows() const;
    unsigned get_cols() const;
    T det();

};

#include "matrix.cpp"

#endif
//https://www.quantstart.com/articles/Matrix-Classes-in-C-The-Source-File

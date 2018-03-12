#ifndef MATRIX_H
#define MATRIX_H

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <iostream>
#include <fstream>
#include <string>

struct BadFileError{
    BadFileError(std::string errMsg){
        std::cerr << "\n\n" << errMsg << "\n\n";
    }
};

typedef boost::numeric::ublas::matrix<int> Matrix;

class MatricesFromFileFactory{
public:
    MatricesFromFileFactory(std::string filename);
    void setNewFile(std::string filename);
    Matrix* getNextMatrix();
    ~MatricesFromFileFactory();
private:
    std::ifstream matrixFstream;
};

#endif

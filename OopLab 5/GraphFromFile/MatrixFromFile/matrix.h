#ifndef MATRIX_H
#define MATRIX_H

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <iostream>
#include <fstream>
#include <string>

struct IOException{
    IOException(std::string errMsg){
        std::cerr << std::endl << std::endl
                  << errMsg
                  << std::endl << std::endl;
    }
};

typedef boost::numeric::ublas::matrix<int> Matrix;

class MatricesFromFileGenerator{
public:
    MatricesFromFileGenerator(std::string filename);
    void Open(std::string filename) throw(IOException);
    Matrix* Next() throw(IOException);
    ~MatricesFromFileGenerator();
private:
    std::ifstream _fileStream;
};

#endif

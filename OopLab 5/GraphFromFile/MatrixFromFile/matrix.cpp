#include "./matrix.h"

MatricesFromFileGenerator::MatricesFromFileGenerator(std::string filename)
{
    Open(filename);
}

void MatricesFromFileGenerator::Open(std::string filename) throw(IOException)
{
    _fileStream.open(filename.c_str());
    if (!_fileStream)
        throw IOException("can't open file");
}

Matrix *MatricesFromFileGenerator::Next() throw(IOException)
{
    Matrix* matrix = new Matrix();
    if (!( _fileStream >> (*matrix) ))
        throw IOException("failed to write to matrix");
    return matrix;
}

MatricesFromFileGenerator::~MatricesFromFileGenerator()
{
    _fileStream.close();
}

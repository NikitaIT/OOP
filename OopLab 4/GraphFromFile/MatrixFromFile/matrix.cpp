#include "./matrix.h"

MatricesFromFileFactory::MatricesFromFileFactory(std::string filename)
{
    setNewFile(filename);
}

void MatricesFromFileFactory::setNewFile(std::string filename)
{
    matrixFstream.open(filename.c_str());
    if (!matrixFstream)
        throw BadFileError("can't open file");
}

Matrix *MatricesFromFileFactory::getNextMatrix()
{
    Matrix* matrix = new Matrix();
    if (!( matrixFstream >> (*matrix) ))
        throw BadFileError("failed to write to matrix");
    return matrix;
}

MatricesFromFileFactory::~MatricesFromFileFactory()
{
    matrixFstream.close();
}

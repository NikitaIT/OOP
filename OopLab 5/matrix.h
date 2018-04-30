#ifndef MATRIX_H
#define MATRIX_H


class matrix
{
    int **elements;
public:
    matrix();
    int row;
    int col;
    matrix(int, int,int *);
    int operator ()(int &i, int &j);
};

#endif // MATRIX_H

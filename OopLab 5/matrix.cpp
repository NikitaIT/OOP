#include "matrix.h"

matrix::matrix()
{

}
matrix::matrix(int n,int m, int *massiv){
    row = n;
    col = m;
    elements = new int* [n];
    for(int i = 0; i<n; i++){
        elements[i] = new int[m];
    }
    for(int i = 0, k = 0; i < n; i++, k+=m)
        for(int j = 0; j < m; j++)
            elements[i][j] = massiv[k+j];
}

int matrix::operator() (int &i, int &j){
    return elements[i][j];
}

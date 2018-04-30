#ifndef GRAPH_H
#define GRAPH_H
#include "matrix.h"

class graph
{
public:
    graph();
    graph(int, matrix);

    int count;
    int currentEdge;
    matrix relations;
};

#endif // GRAPH_H

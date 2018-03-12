#ifndef NODESLIST_H
#define NODESLIST_H
#include "MatrixFromFile/matrix.h"
#include <string>
#include <QPointF>
#include <memory>

using std::unique_ptr;
/*
 * Node position on rectangle area
 * in matrix representation:
 * [2,2]
 * ((0, 2),
 *  (1, 3))
 *
 * Adjacency matrix
 * For example {1}:
 * [4, 4]
 * ((1, 1, 1, 0),
 *  (0, 0, 0, 0),
 *  (1, 0, 0, 0),
 *  (0, 0, 0, 0))
 *
 * For example, it's look like:
 *   _
 *  | |
 * \/\/
 * (0)<-->(2)
 *  |      |
 * \/     \/
 * (1)   (3)
*/


class NodesListFromFile
{
public:
    NodesListFromFile(std::string filename, int rectWidht, int rectHeigth);

    QPointF getPosition(int nodeNumber) const;
    bool isConnected(unsigned nodeNumber1, unsigned nodeNumber2) const;

    void setNewFile(std::string filename);

    void setNewSizeOfArea(int rectWidht, int rectHeigth);
    int getRectWidht() const;
    void setRectWidht(int rectWidht);
    int getRectHeigth() const;
    void setRectHeigth(int rectHeigth);
    int getNodeRadius() const;

    int getSize() const;
    ~NodesListFromFile();
private:
    void calculateNodeRadius();
    int rectWidht_, rectHeigth_, nodeRadius_, cellWidth_, cellHeigth_;
    unique_ptr<Matrix> NodePositionOnMatrix;
    unique_ptr<Matrix> AdjacencyMatrix;
};
#endif // NODESLIST_H

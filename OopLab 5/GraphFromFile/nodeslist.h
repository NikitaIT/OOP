#ifndef NODESLIST_H
#define NODESLIST_H
#include "MatrixFromFile/matrix.h"
#include <string>
#include <QPointF>
#include <memory>

using std::unique_ptr;

class NodesListFromFile
{
public:
    NodesListFromFile(std::string filename, int rectWidht, int rectHeigth);

    QPointF GetPosition(int nodeNumber) const;
    bool IsConnected(unsigned nodeNumber1, unsigned nodeNumber2) const;

    void SetNewFile(std::string filename);

    void SetNewSizeOfArea(int rectWidht, int rectHeigth);
    int GetNodeRadius() const;

    int GetSize() const;
    ~NodesListFromFile();
private:
    int GetRectWidht() const;
    void SetRectWidht(int rectWidht);
    int GetRectHeigth() const;
    void SetRectHeigth(int rectHeigth);

    void CalculateNodeRadius();
    int _rectWidht,
        _rectHeigth,
        _nodeRadius,
        _cellWidth,
        _cellHeigth;
    unique_ptr<Matrix> _nodePositionOnMatrix;
    unique_ptr<Matrix> _adjacencyMatrix;
};
#endif // NODESLIST_H

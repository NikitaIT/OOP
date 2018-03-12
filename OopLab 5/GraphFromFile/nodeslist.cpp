#include "nodeslist.h"
#include <QDebug>

NodesListFromFile::NodesListFromFile(std::string filename, int rectWidht, int rectHeigth) :
    _rectWidht(rectWidht), _rectHeigth(rectHeigth)
{
    SetNewFile(filename);
}

QPointF NodesListFromFile::GetPosition(int nodeNumber) const
{
    for ( int y = _nodePositionOnMatrix->size1() - 1; y >= 0; --y )
        for ( int x = _nodePositionOnMatrix->size2() - 1; x >= 0; --x )
            if (_nodePositionOnMatrix->at_element(y, x) == nodeNumber)
                return QPointF(_cellWidth * (x + 0.5), _cellHeigth * (y + 0.5));

    return QPointF(0.0, 0.0);
}



bool NodesListFromFile::IsConnected(unsigned nodeNumber1, unsigned nodeNumber2) const
{
    return _adjacencyMatrix->at_element(nodeNumber1, nodeNumber2);
}

void NodesListFromFile::SetNewFile(std::string filename)
{
    _nodePositionOnMatrix.reset();
    _adjacencyMatrix.reset();

    unique_ptr<MatricesFromFileGenerator> MatrixFactory(new MatricesFromFileGenerator(filename));
    _nodePositionOnMatrix = unique_ptr<Matrix>(MatrixFactory->Next());
    _adjacencyMatrix = unique_ptr<Matrix>(MatrixFactory->Next());
    CalculateNodeRadius();
}

void NodesListFromFile::CalculateNodeRadius()
{
    int numOfGridRows = _nodePositionOnMatrix->size1(),
        numOfGridCols = _nodePositionOnMatrix->size2();

    _cellWidth = _rectWidht   / numOfGridCols;
    _cellHeigth = _rectHeigth / numOfGridRows;

    _nodeRadius = std::max(_cellWidth,_cellHeigth) / 2;
}

void NodesListFromFile::SetNewSizeOfArea(int rectWidht, int rectHeigth)
{
    SetRectWidht(rectWidht);
    SetRectHeigth(rectHeigth);
    CalculateNodeRadius();
}

int NodesListFromFile::GetNodeRadius() const
{
    return _nodeRadius;
}

int NodesListFromFile::GetSize() const
{
    return _adjacencyMatrix->size1();
}

int NodesListFromFile::GetRectHeigth() const
{
    return _rectHeigth;
}

void NodesListFromFile::SetRectHeigth(int rectHeigth)
{
    _rectHeigth = rectHeigth;
}

int NodesListFromFile::GetRectWidht() const
{
    return _rectWidht;
}

void NodesListFromFile::SetRectWidht(int rectWidht)
{
    _rectWidht = rectWidht;
}

NodesListFromFile::~NodesListFromFile()
{}

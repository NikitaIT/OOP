#include "nodeslist.h"
#include <QDebug>

NodesListFromFile::NodesListFromFile(std::string filename, int rectWidht, int rectHeigth) :
    rectWidht_(rectWidht), rectHeigth_(rectHeigth)
{
    setNewFile(filename);
}

QPointF NodesListFromFile::getPosition(int nodeNumber) const
{
    //Cause cols on the grid = x coordinates, rows = y coordinates
    int xOfCol = -1, yOfRow = -1;
    for (int i = NodePositionOnMatrix->size1() - 1; i >= 0; --i){
        for (int j = NodePositionOnMatrix->size2() - 1; j >= 0; --j){
            if (NodePositionOnMatrix->at_element(i, j) == nodeNumber){
                xOfCol = j; yOfRow = i;
                goto coordinateFindEnded;
            }
        }
    }
coordinateFindEnded:
    if (xOfCol == -1 || yOfRow == -1)
        return QPointF(0.0, 0.0);
    else
        return QPointF(cellWidth_ * (xOfCol + 0.5), cellHeigth_ * (yOfRow + 0.5));
}



bool NodesListFromFile::isConnected(unsigned nodeNumber1, unsigned nodeNumber2) const
{
    return AdjacencyMatrix->at_element(nodeNumber1, nodeNumber2);
}

void NodesListFromFile::setNewFile(std::string filename)
{
    NodePositionOnMatrix.reset();
    AdjacencyMatrix.reset();

    unique_ptr<MatricesFromFileFactory> MatrixFactory(new MatricesFromFileFactory(filename));
    NodePositionOnMatrix = unique_ptr<Matrix>(MatrixFactory->getNextMatrix());
    AdjacencyMatrix = unique_ptr<Matrix>(MatrixFactory->getNextMatrix());
    calculateNodeRadius();
}

void NodesListFromFile::calculateNodeRadius()
{
    int numOfGridRows = NodePositionOnMatrix->size1();
    int numOfGridCols = NodePositionOnMatrix->size2();

    cellWidth_ = rectWidht_   / numOfGridCols;
    cellHeigth_ = rectHeigth_ / numOfGridRows;

    //Diameter = 50% of cell max heigth||width
    nodeRadius_ = (cellWidth_ <= cellHeigth_) ? cellWidth_ * 0.5 / 2 : cellHeigth_ * 0.5 / 2;
}

void NodesListFromFile::setNewSizeOfArea(int rectWidht, int rectHeigth)
{
    setRectWidht(rectWidht);
    setRectHeigth(rectHeigth);
    calculateNodeRadius();
}

int NodesListFromFile::getNodeRadius() const
{
    return nodeRadius_;
}

int NodesListFromFile::getSize() const
{
    return AdjacencyMatrix->size1();
}

int NodesListFromFile::getRectHeigth() const
{
    return rectHeigth_;
}

void NodesListFromFile::setRectHeigth(int rectHeigth)
{
    rectHeigth_ = rectHeigth;
}

int NodesListFromFile::getRectWidht() const
{
    return rectWidht_;
}

void NodesListFromFile::setRectWidht(int rectWidht)
{
    rectWidht_ = rectWidht;
}

NodesListFromFile::~NodesListFromFile()
{}

#include "graphwidget.h"

GraphWidget::GraphWidget(QWidget *parent) :
    QWidget(parent)
{}

GraphWidget::~GraphWidget()
{}

void GraphWidget::resizeEvent(QResizeEvent *event)
{
    if (Nodes == nullptr) return;
    QSize newSize = event->size();
    Nodes->setNewSizeOfArea(newSize.width(), newSize.height());
}

void GraphWidget::paintEvent(QPaintEvent *event)
{
    if (Nodes == nullptr) return;
    Q_UNUSED(event);

    QPainter painter(this);
    int radius = Nodes->getNodeRadius();

    int numOfNodes = Nodes->getSize();

    // Brush setup
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    double vectorLength = 0;
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));

    QPointF nodePos1, nodePos2;
    //Drawing edges and arrows
    for (int i = 0; i < numOfNodes; ++i) {
        nodePos1 = Nodes->getPosition(i);
        for(int j = 0; j < numOfNodes; ++j) {
            if(Nodes->isConnected(i, j) != 0 && i != j) {
                nodePos2 = Nodes->getPosition(j);
                painter.drawLine(nodePos1, nodePos2);

                //drawing arrow
                painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));

                //Now, nodePos2 - coordinate of vector AB, where A = nodePos1, B = nodePos2:
                nodePos2.setX(nodePos2.x() - nodePos1.x());
                nodePos2.setY(nodePos2.y() - nodePos1.y());

                vectorLength = sqrt(nodePos2.x() * nodePos2.x() + nodePos2.y() * nodePos2.y());

                //Scale vector for radius exclusion
                nodePos2.setX(nodePos2.x() * (vectorLength - radius) / vectorLength);
                nodePos2.setY(nodePos2.y() * (vectorLength - radius) / vectorLength);
                //Move to old coordinate position
                nodePos2.setX(nodePos2.x() + nodePos1.x());
                nodePos2.setY(nodePos2.y() + nodePos1.y());
                //Draw ellips arrow (lol)
                painter.drawEllipse(nodePos2, radius / 4, radius / 4);
                painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
            }
        }
    }

    //Drawing nodes
    QPointF tmpPosition;
    for(int i = 0;  i < numOfNodes; ++i){
        tmpPosition = Nodes->getPosition(i);
        if (!tmpPosition.isNull()){
            if (!Nodes->isConnected(i, i))
                painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
            else
                painter.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
            painter.drawEllipse(tmpPosition, radius, radius);
            painter.drawText(tmpPosition, QString::number(i));
        }
    }
}

void GraphWidget::openFile(QString filename)
{
    try {
        Nodes = std::make_unique<NodesListFromFile>(filename.toStdString(), this->size().width(), this->size().height());
    } catch (BadFileError) {
        emit cantReadFileWithMatrix();
        return;
    }
    repaint();
}

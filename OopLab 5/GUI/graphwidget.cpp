#include "graphwidget.h"

GraphWidget::GraphWidget(QWidget *parent) :
    QGraphicsView(parent), scene(new QGraphicsScene(this))
{
    setScene(scene);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
}

void GraphWidget::addGraphInScene()
{
    scene->clear();
    QList<Node*> tmpListOfGraphicNodes;
    Node* tmpNode;
    int numOfNodes = Nodes->GetSize();
    QPointF tmpPosition;
    //Add Nodes to scene
    for (int i = 0; i < numOfNodes; ++i) {
        tmpPosition = Nodes->GetPosition(i);
        if (!tmpPosition.isNull()){ //For adding fake Nodes
            tmpNode = new Node(Nodes->GetNodeRadius(), i);
            tmpNode->setPos(
                        tmpPosition.x(),
                        tmpPosition.y()
                        );
            tmpListOfGraphicNodes.push_back(tmpNode);
            scene->addItem(tmpNode);
        }
    }

    //Connect Edges and add to scene
    for (int i = 0; i < numOfNodes; ++i) {
        for(int j = 0; j < numOfNodes; ++j) {
            if(Nodes->IsConnected(i, j) != 0 && i != j) {
                scene->addItem(
                            new Edge(tmpListOfGraphicNodes.at(i),
                                     tmpListOfGraphicNodes.at(j)
                                     )
                            );
            }
        }
    }
}

void GraphWidget::openFile(QString filename)
{
    try {
        Nodes = std::make_unique<NodesListFromFile>(filename.toStdString(), this->size().width(), this->size().height());
    } catch (IOException) {
        emit cantReadFileWithMatrix();
        return;
    }
    addGraphInScene();
}

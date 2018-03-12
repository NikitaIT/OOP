#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QResizeEvent>
#include <memory>

#include "GraphFromFile/nodeslist.h"
#include "node.h"
#include "edge.h"

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = 0);
signals:
    void cantReadFileWithMatrix();
public slots:
    void openFile(QString filename);
private:
    unique_ptr<NodesListFromFile> Nodes;
    QGraphicsScene *scene;
    void addGraphInScene();
};

#endif // GRAPHWIDGET_H

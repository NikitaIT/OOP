#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include "graph.h"


namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = 0);
    ~GraphWindow();

private:
    Ui::GraphWindow *ui;
    //QGraphicsItemGroup createEdge(QRectF &coord, int &nomer);
private slots:
    void createGraph(graph &, matrix &);
};

#endif // GRAPHWINDOW_H

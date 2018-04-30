#include "graphwindow.h"
#include "ui_graphwindow.h"
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>

GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::createGraph(graph &Graph,matrix &Map){

    QPen outlinePen(Qt::black);
    QPen bluePen(Qt::blue);
    QPen redPen(Qt::red);
    QBrush blueBrush(Qt::blue);
    QBrush greenBrush(Qt::green);
    QBrush yellowBrush(Qt::yellow);
    QGraphicsScene *scene = new QGraphicsScene();
    QPoint *coord = new QPoint[Graph.count+1];
    ui->graphicsView->setScene(scene);

    for(int i = 0; i<Map.row; i++)
        for(int j = 0; j<Map.col; j++){
            if(Map(i,j) != 0){
                QPoint center(j*20+20,i*20+20);
                coord[Map(i,j)] = center;
            }
        }

        for(int i = 0; i<Graph.count; i++)
            for(int j = 0; j<Graph.count; j++){
           //     QPoint halfLine;
              //   halfLine.setX((coord[i+1].x()+coord[j+1].x())/2);
             //    halfLine.setY((coord[i+1].y()+coord[j+1].y())/2);
             //    QLine line(coord[i+1],halfLine);
             //    scene->addLine(line,redPen);
              if(Graph.relations(i,j)){
                  QPoint halfLine;
                   halfLine.setX((coord[i+1].x()+coord[Graph.relations(i,j)].x())/2);
                   halfLine.setY((coord[i+1].y()+coord[Graph.relations(i,j)].y())/2);
                   QLine line(coord[i+1]+QPoint(10,10),coord[Graph.relations(i,j)]+QPoint(10,10));
                   scene->addLine(line,bluePen);
              }
                   // if(i == Graph.relations(i,j)){
                  //      QRect point(coord[i].x(),coord[i].y(),10,10);
                  //      scene->addEllipse(point,bluePen,blueBrush);
                 //   }

    }
        for(int i = 0; i < Graph.count; i++){
            QString number = QString::number(i+1);
            QGraphicsTextItem *textEdge = new QGraphicsTextItem(number);
            QRect center(coord[i+1].x(),coord[i+1].y(),40,40);
            textEdge->setPos(coord[i+1].x()+10,coord[i+1].y()+10);
            if(i == Graph.currentEdge)
             scene->addEllipse(center,outlinePen,yellowBrush);
            else
                scene->addEllipse(center,outlinePen,greenBrush);
            scene->addItem(textEdge);
        }
    //scene->addEllipse(0,0,50,50,outlinePen,greenBrush);

}

/*QGraphicsItemGroup GraphWindow::createEdge(QRectF & coord,int &nomer){

    QGraphicsScene *tmpScene = new QGraphicsScene();
    QString num;
    num.setNum(nomer);
    QGraphicsItemGroup *group = new QGraphicsItemGroup();
    QGraphicsTextItem *textEdge = new QGraphicsTextItem(num);
    textEdge->setPos(coord.x(),coord.y());
    group->addToGroup(tmpScene->addEllipse(coord,outlinePen,greenBrush));
    group->addToGroup(textEdge);

                QString num;
                num.setNum(Map(i,j));
                QGraphicsTextItem *textEdge = new QGraphicsTextItem(num);
                textEdge->setPos(center.x()+10,center.y()+10);
                scene->addEllipse(center,outlinePen,greenBrush);
                scene->addItem(textEdge);
}
*/

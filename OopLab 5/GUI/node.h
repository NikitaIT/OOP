#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class Edge;

class Node : public QGraphicsItem
{
public:
    Node(int radius, int id);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;


    void receiveColor(const Node *from, const QColor &color);
    const Node *getColorOwner() const;

protected:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void sendColor(const Node *from, const QColor &color);
    void setColorOwner(const Node *value);

    QList<Edge *> edgeList;
    int radius_;
    int id_;

    const Node* colorOwner;
    QColor color_ = Qt::white;
};

#endif // NODE_H

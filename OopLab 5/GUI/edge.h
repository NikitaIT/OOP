#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include "node.h"

class Edge : public QGraphicsItem
{
public:
    Edge(Node *sourceNode, Node *destNode);
    Node *sourceNode() const;
    Node *destNode() const;
    void sendColor(const Node *from, QColor color);
    void adjust();

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Node *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
};

#endif // EDGE_H

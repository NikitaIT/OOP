#include "edge.h"
#include "node.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>

static const QColor colours[10] = {QColor(255, 0, 0, 127), QColor("darkCyan"), QColor(0, 0, 255, 127), QColor("red"),
                                       QColor("darkRed"), QColor(0, 222, 255, 127),
                                       QColor(123, 43, 4, 222), QColor(23, 22, 255, 41), QColor(0, 122, 255, 127),
                                       QColor(123, 51, 255, 127)};

Node::Node(int radius, int id):
radius_(radius), id_(id), color_(colours[id % 10]), colorOwner(this)
{}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}

QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option)

    painter->setPen(Qt::NoPen);
    painter->setBrush(color_);
    painter->drawEllipse(-7, -7, 20, 20);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
    painter->drawText(QPointF(0, 0), QString::number(id_));

    //Draw all edges
    foreach (Edge *edge, edgeList)
        edge->adjust();
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    sendColor(this, colours[id_ % 10]);
    QGraphicsItem::mousePressEvent(event);
}

void Node::sendColor(const Node *from, const QColor &color)
{
    foreach (auto Edge, edgeList) {
        Edge->sendColor(from, color);
    }
}

const Node *Node::getColorOwner() const
{
    return colorOwner;
}

void Node::setColorOwner(const Node *value)
{
    colorOwner = value;
}

void Node::receiveColor(const Node *from, const QColor &color)
{
    setColorOwner(from);
    color_ = color;
    update();
    sendColor(from, color);
}

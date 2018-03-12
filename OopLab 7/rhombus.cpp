#include "rhombus.h"
#include <limits>
#include <cmath>

Rhombus::Rhombus(Point point1, Point point2, Point point3) :
    Parallelogram(point1, point2, point3)
{
    Vector2D edge1(point1, point2), edge2(point1, point3);
    bool edgeIsEqual = ( edge1.abs() - edge2.abs() ) < std::numeric_limits<double>::epsilon(); //compare 2 double variables
    if (!edgeIsEqual)
        throw BadCoordinateException();
}

double Rhombus::Area() const
{
    Vector2D edge1(coordinates[0], coordinates[1]);
    Vector2D edge2(coordinates[0], coordinates[2]);
    double edgeLength = edge1.abs();
    return edgeLength * edgeLength * sin(edge1, edge2);
}

double Rhombus::Perimeter() const
{
    Vector2D edge(coordinates[0], coordinates[1]);
    double edgeLength = edge.abs();
    return 4 * edgeLength;
}


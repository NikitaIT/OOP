#include "square.h"

Square::Square(Point point1, Point point2)
{
    coordinates.emplace_back(point1);
    coordinates.emplace_back(point2);
}

double Square::Area() const
{
    double edgeLength = Vector2D(coordinates[0], coordinates[1]).abs();
    return edgeLength * edgeLength;
}

double Square::Perimeter() const
{
    double edgeLength = Vector2D(coordinates[0], coordinates[1]).abs();
    return 4 * edgeLength;
}

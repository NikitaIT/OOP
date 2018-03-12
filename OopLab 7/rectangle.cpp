#include "rectangle.h"
#include <limits>
Rectangle::Rectangle(Point point1, Point point2, Point point3) :
    Parallelogram(point1, point3, point2)
{
    Vector2D edge1(point1, point2), edge2(point1, point3);
    bool edgeAngleIsRight = ( cos(edge1, edge2) + 1.0 ) == 1.0; //compare cos with zero (angle == 90 degree)
    if ( !( edgeAngleIsRight) )
        throw BadCoordinateException();
}

double Rectangle::Area() const
{
    Vector2D edge1(coordinates[0], coordinates[1]);
    Vector2D edge2(coordinates[0], coordinates[2]);
    return edge1.abs() * edge2.abs();
}

double Rectangle::Perimeter() const
{
    Vector2D edge1(coordinates[0], coordinates[1]);
    Vector2D edge2(coordinates[0], coordinates[2]);
    return 2 * edge1.abs() + 2 * edge2.abs();
}


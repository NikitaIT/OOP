#include "vector2d.h"

Vector2D::Vector2D(Point startPoint, Point endPoint) :
    vectorCoordinate( endPoint.x() - startPoint.x(), endPoint.y() - startPoint.y() )
{}

Vector2D::Vector2D(Point vectorCoordinate) :
    vectorCoordinate(vectorCoordinate)
{}

Point Vector2D::coordinate() const
{
    return vectorCoordinate;
}

double Vector2D::abs() const
{
    return std::sqrt(vectorCoordinate.x() * vectorCoordinate.x() + vectorCoordinate.y() * vectorCoordinate.y());
}

//Helpers definition

double scalarProduct(Vector2D a, Vector2D b)
{
    return a.coordinate().x() * b.coordinate().x() + a.coordinate().y() * b.coordinate().y();
}

double cos(Vector2D a, Vector2D b)
{
    return scalarProduct(a, b) / (a.abs() * b.abs());
}

double sin(Vector2D a, Vector2D b)
{
    return std::sqrt( 1-cos(a, b) * cos(a, b) );
}

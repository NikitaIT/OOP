#ifndef VECTOR2D_H
#define VECTOR2D_H
#include "point.h"
#include <cmath>
class Vector2D
{
private:
    Point vectorCoordinate;
public:
    Vector2D(Point startPoint, Point endPoint);
    Vector2D(Point vectorCoordinate);
    Point coordinate() const;
    double abs() const;
};

//Helpers declaration
double scalarProduct(Vector2D a, Vector2D b);
double cos(Vector2D a, Vector2D b);
double sin(Vector2D a, Vector2D b);
#endif // VECTOR2D_H

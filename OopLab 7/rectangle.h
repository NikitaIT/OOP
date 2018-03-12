#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "parallelogram.h"

class Rectangle : public Parallelogram
{
public:
    Rectangle(Point point1, Point point2, Point point3);
    virtual double Area() const override;
    virtual double Perimeter() const override;
};

#endif // RECTANGLE_H

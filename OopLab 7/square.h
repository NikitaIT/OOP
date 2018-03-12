#ifndef SQUARE_H
#define SQUARE_H
#include "rectangle.h"

class Square : public Figure
{
public:
    Square(Point point1, Point point2);
    virtual double Area() const override;
    virtual double Perimeter() const override;
};

#endif // SQUARE_H

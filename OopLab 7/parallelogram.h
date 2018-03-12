#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H

#include "figure.h"
#include <vector>

class Parallelogram : public Figure
{
public:
    Parallelogram(Point point1, Point point2, Point point3);
    virtual double Area() const override;
    virtual double Perimeter() const override;
};

#endif // PARALLELOGRAM_H

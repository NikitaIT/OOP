#ifndef POINT_H
#define POINT_H
#include "random.h"

class Point
{
public:
    float x;
    float y;

    Point(float x = 0, float y = 0)
    {
        this->x = x;
        this->y = y;
    }

    static Point *GeneratePoint(Point *min, Point*max, Random &r)
    {
        auto f = (float)r.NextDouble();
        auto f2 = f * (max->x - min->x);
        return new Point( f2 + min->x, (float)r.NextDouble() * (max->y - min->y) + min->y);
    }
};

#endif // POINT_H

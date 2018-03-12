#ifndef FIGURES_H
#define FIGURES_H
#include <cmath>

class Figures
{
public:
    float widht;
    float height;
    float xLeftTop;
    float yLeftTop;

     float area = 0;
    Figures(){}
    virtual  bool InTarget(float x, float y){return true;}
    virtual  void SetCenter(float x, float y){}
};

class Rectangle : public Figures
{
public:
    Rectangle(){}
    Rectangle (float x, float y, float h, float w)
    {
        xLeftTop = x;
        yLeftTop = y;
        height = h;
        widht = w;
    }

    void SetCenter(float x, float y) override
    {
        xLeftTop = x - widht / 2;
        yLeftTop = y - height / 2;
    }

    bool InTarget(float x0, float y0) override
    {
        return ((xLeftTop + widht) >= x0 && x0 >= xLeftTop) && ((yLeftTop + height) >= y0 && y0 >= yLeftTop);
    }
};

class Ellipse : public Figures
{
public:
    Ellipse (float x, float y,float h, float w)
    {
        xLeftTop = x;
        yLeftTop = y;
        widht = w;
        height = h;
    }
    void SetCenter(float x, float y) override
    {
        xLeftTop = x - widht / 2;
        yLeftTop = y - height / 2;
    }

    bool InTarget(float x, float y)override
    {
        return std::pow(x / widht, 2) + std::pow(y / height, 2) <= 1;
    }
};

class Square : public Rectangle
{

public:
    Square(float x, float y, float a) : Rectangle(x, y, a, a)
    {
        xLeftTop = x;
        yLeftTop = y;
        height = widht = a;
    }
};

class Circle : public Ellipse
{

public:
    Circle(float x, float y, float R) : Ellipse(x, y, R, R)
    {
        xLeftTop = x;
        yLeftTop = y;
        height = widht = R;
    }
};

#endif // FIGURES_H
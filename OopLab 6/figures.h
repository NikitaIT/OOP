#ifndef FIGURES_H
#define FIGURES_H
#include <cmath>
#include <string>
#include <sstream>

class CAlculateble{
public:
     virtual double Area() const {return 0;}
     virtual double Perimeter() const {return 0;}
};

class Figures : public CAlculateble
{
public:
    float widht;
    float height;
    float xLeftTop;
    float yLeftTop;

     float area = 0;
    Figures(){}
    virtual ~Figures(){}
    virtual  bool InTarget(float x, float y) = 0;
    virtual  void SetCenter(float x, float y) = 0;
    operator std::string() const {
        std::ostringstream buff;
        buff<< "area "<< area<<" widht"  <<widht<<" height"<<height <<" xLeftTop " <<xLeftTop<< " yLeftTop " << yLeftTop;
        return buff.str(); }
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

    void SetCenter(float x, float y)
    {
        xLeftTop = x - widht / 2;
        yLeftTop = y - height / 2;
    }

    bool InTarget(float x0, float y0)
    {
        return ((xLeftTop + widht) >= x0 && x0 >= xLeftTop) && ((yLeftTop + height) >= y0 && y0 >= yLeftTop);
    }
    double Area() const
    {
        return widht * height;
    }

    double Perimeter() const
    {
        return 2 * (widht + height);
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
    void SetCenter(float x, float y)
    {
        xLeftTop = x - widht / 2;
        yLeftTop = y - height / 2;
    }

    bool InTarget(float x, float y)
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
class Parallelogram : public Rectangle
{
    public:
    float angle;
    Parallelogram(float h, float w, float angle_){
        angle=(angle_);
        widht=(w);
        height=(h);
    }
    double Area() const
    {
        return widht * height * std::sin(angle * 3.14 / 180);
    }

    double Perimeter() const
    {
        return 2 * (widht + height);
    }
};

#endif // FIGURES_H

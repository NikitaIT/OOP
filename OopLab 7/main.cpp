#include <iostream>
#include "figures.h"
#include <vector>
#include <typeinfo>
class Calculateble {
public:
    virtual double Area() const = 0;
    virtual double Perimeter() const = 0;
};
class Parallelogram : public Calculateble {
protected: float angle, widht, height;
public:
    Parallelogram(float h, float w, float angle_): angle(angle_), widht(w), height(h){}
    double Area() const{return widht * height * std::sin(angle * 3.14 / 180);}
    double Perimeter() const{return 2 * (widht + height);}
};
class Rectangle : public Parallelogram  {public:Rectangle(float h, float w) : Parallelogram(h,w,90){}};
class Romb      : public Parallelogram  {public:Romb(float h, float angle)  : Parallelogram(h,h,angle){}};
class Square    : public Rectangle      {public:Square(float h)             : Rectangle(h,h){}};

int main(){
    std::vector<std::pair<Calculateble*,std::string>> figures;
    float a1,a2,a3;
    std::cout<< "Enter Input Parametrs"<< std::endl << "1. side1 = ";
    std::cin>>a1;
    std::cout<< std::endl << "2. side2 = ";
    std::cin>>a2;
    std::cout<< std::endl << "3. angle = ";
    std::cin>>a3;
    std::cout<< std::endl;

    figures.emplace_back(new Parallelogram(a1,a2,a3),"Parallelogram");
    figures.emplace_back(new Rectangle(a1,a2),"Rectangle");
    figures.emplace_back(new Romb(a1,a3),"Romb");
    figures.emplace_back(new Square(a1),"Square");

    for (std::pair<Calculateble*,std::string> figure : figures){
        std::cout <<  figure.second << std::endl
                   << "Периметр фигуры = " << figure.first->Perimeter()
                   << " Площадь фигуры = "   << figure.first->Area()
                   << std::endl;
    }
    return 0;
}

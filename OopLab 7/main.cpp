#include <iostream>
#include "../OopLab 6/figures.h"
#include <vector>
#include <typeinfo>
class Romb: public Parallelogram{
public:
    Romb(float h, float angle_) : Parallelogram( h,  h, angle_){}
};
int main(){
    std::vector<std::pair<CAlculateble*,std::string>> figures;
    float a1,a2,a3;
    std::cout<< "Enter Input Parametrs"<< std::endl;
    std::cout<< "1. side1 = ";
    std::cin>>a1;
    std::cout<< std::endl;
    std::cout<< "2. side2 = ";
    std::cin>>a2;
    std::cout<< std::endl;
    std::cout<< "3. angle = ";
    std::cin>>a3;
    std::cout<< std::endl;

    figures.emplace_back(new Parallelogram(a1,a2,a3),"Parallelogram");
    figures.emplace_back(new Rectangle(0,0,a1,a2),"Rectangle");
    figures.emplace_back(new Romb(a1,a3),"Romb");
    figures.emplace_back(new Square(0,0,a1),"Square");

    for (std::pair<CAlculateble*,std::string> figure : figures){
        std::cout <<  figure.second << std::endl
                   << "Периметр фигуры = " << figure.first->Perimeter()
                   << " Площадь фигуры = "   << figure.first->Area()
                   << std::endl;
    }
    return 0;
}

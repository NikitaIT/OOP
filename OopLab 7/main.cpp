#include <iostream>
#include "figure.h"
#include "parallelogram.h"
#include "rhombus.h"
#include "rectangle.h"
#include "square.h"
#include <vector>

enum figNum  {NParallelogram = '1', NRhombus = '2', NRectangle = '3', NSquare = '4'};

Figure* getFigure(int mode){
    Figure* tmpFigure = NULL;
    std::cout << "Введите " << ((mode == NSquare) ? "2" : "3") << " координаты вершин (1ая - общая)\n";
    std::vector<Point> inputCoordinates;
    double tmpX, tmpY;

    while (1){

        for ( int i = (mode == NSquare) ? 2 : 3; i > 0; --i ){
            std::cin >> tmpX >> tmpY;
            inputCoordinates.emplace_back(Point(tmpX, tmpY));
        }

        try{
            switch (mode) {
            case NParallelogram:
                tmpFigure = new Parallelogram(inputCoordinates[0], inputCoordinates[1], inputCoordinates[2]);
                break;
            case NRhombus:
                tmpFigure = new Rhombus(inputCoordinates[0], inputCoordinates[1], inputCoordinates[2]);
                break;
            case NRectangle:
                tmpFigure = new Rectangle(inputCoordinates[0], inputCoordinates[1], inputCoordinates[2]);
                break;
            case NSquare:
                tmpFigure = new Square(inputCoordinates[0], inputCoordinates[1]);
                break;
            default:
                break;
            }
            break;
        } catch(BadCoordinateException){
            std::cout << "Ввод не корректен, повторите ввод с правильными координатами: \n";
            continue;
        }
    }
    return tmpFigure;
}

int main(){
    std::vector<Figure*> figures;
    char cmd;
    do {
        cmd = 'n';
        std::cout << "=============================\n"
                     "'1' Параллелограмм \n"
                     "'2' Ромб \n"
                     "'3' Прямоугольник\n"
                     "'4' Квадрат\n"
                     "'n'' чтобы выйти\n"
                     "Введите желаемую команды: \n";
        std::cin >> cmd;

        if (cmd != 'n'){
            figures.emplace_back(getFigure(cmd));
        } else{
            break;
        }

        system("clear");
        for (auto figure : figures){
            std::cout << "Площадь фигуры = "   << figure->Area()
                      << " Периметр фигуры = " << figure->Perimeter() << std::endl;
        }
    } while (1);

    for (auto i : figures)
        delete i;
    return 0;
}

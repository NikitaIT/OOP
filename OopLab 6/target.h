#ifndef TARGET_H
#define TARGET_H

#include "point.h"
#include "figures.h"
#include "random.h"
#include <list>
#include <QtCore/qglobal.h>
#include <string>
#include <sstream>
template<typename T>
void debug(T t){
    std::ostringstream buff;
    buff<< t;
    qDebug(buff.str().c_str());
}

class Target : public Rectangle
{
public:
    Rectangle target;
    std::list<Figures*> ArrayofFigures;
    Random r;
    Target(){}
    Target(float x, float y, float widht, float height) : Rectangle(x, y, widht, height)
    {
        target = Rectangle(x, y, widht, height);
        ArrayofFigures = std::list<Figures*>();
        r = *new Random();
        area = -1;
    }

    void GenerateCoordinateonBorder( float &x, float &y)
    {
        switch (r.Next(1,5))
        {
        case 1:
            x = (float)(r.NextDouble() * (target.widht) + target.xLeftTop);
            y = target.yLeftTop;
            break;
        case 2:
            x = (float)(r.NextDouble() * (target.widht) + target.xLeftTop);
            y = target.yLeftTop + target.height;
            break;
        case 3:
            x = target.xLeftTop;
            y = (float)(r.NextDouble() * (target.height) + target.yLeftTop);
            break;
        case 4:
            x = target.xLeftTop + target.widht;
            y = (float)(r.NextDouble() * (target.height) + target.yLeftTop);
            break;
        default:
            x = 0;
            y = 0;
            break;
        }
    }
    //функция генерации фигур с размерами, распределенными по равномерному закону
    std::list<Figures *> GenerateFigures(int N)
    {
        auto list = *new std::list<Figures*>();
        for (int i = 0; i < N; i++)
        {
            Figures *fig;

            float x, y;
            GenerateCoordinateonBorder(x, y);
            auto s = r.Next(1,5);
            switch (s)
            {
                case 1:
                    fig = new Rectangle(x, y, r.Next((int)widht/4, (int)widht/2),r.Next((int)height/4, (int) height/2));
                    break;
                case 2:
                    fig = new Ellipse(x, y, r.Next((int)widht / 4, (int)widht / 2), r.Next((int)height / 4, (int)height / 2));
                    break;
                case 3:
                    fig =new Square(x, y, r.Next((int)widht / 4, (int)widht / 2));
                    break;
                case 4:
                    fig = new Circle(x, y, r.Next((int)widht / 4, (int)widht / 2));
                    break;
                default:
                    break;
            }
               fig->SetCenter(x, y);
               list.push_back(fig);

        }
        //debug(std::to_string(list.size()));
       // for(auto l:list){
        //    debug(std::string(l));
        //}
        ArrayofFigures = list;
        return list;
    }

    //вторая часть задания - нахождение свободной площади мишени

    //функция для определения площади методом монте карло
    float FreeAreaofTarget(int count)
    {
        if(count == 0)
            return area;
        int CountFree = 0;
        int CountnotFree = 0;
        for (int i = 0; i < count; i++)
        {
            bool ss = false;
            auto p = Point::GeneratePoint(new Point(xLeftTop, yLeftTop), new Point(xLeftTop + widht, yLeftTop + height), r);
            for (Figures * fig : ArrayofFigures){
                if(fig->InTarget(p->x, p->y)){
                    ss =true;
                    break;
                }
            }
            if ( ss )
            {
                CountnotFree++;
            }
            else
            {
                CountFree++;
            }
        }
        area = (float)CountnotFree / (float)count;
        return area;
    }
};


#endif // TARGET_H

#ifndef CALC_H
#define CALC_H

#include "target.h"
#include <string>
#include <sstream>
#include <memory>
class Calc{

public:
    struct config{
        float widht = 0;
        float height = 0;
        int figuresCount = 0;
        int iterationCount = 0;
        int regularScanW = 0;
        int regularScanH = 0;
        bool isRegularScan = false;
        bool isRandomScan = false;
    };
    config GetConf(){
        return conf;
    }
    Calc(){_t = new Target(1000, 1000, conf.widht, conf.height);}
    Calc(config c){
        SetTarget(c);
    }
    double CalculateArea(config c);
    float CalculateAreaSize(float area);
private:
    Target *_t;
    Calc::config conf;
    Calc *SetTarget(config c);
    double Scan(config c);
};


#endif // CALC_H

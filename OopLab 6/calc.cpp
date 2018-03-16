#include "calc.h"



double Calc::CalculateArea(Calc::config c){
    if(c.widht != conf.widht || c.height != conf.height || c.figuresCount != conf.figuresCount){
        return this->SetTarget(c)->CalculateArea(c);
    }
    return Scan(c);
}

float Calc::CalculateAreaSize(float area){ return _t->GetFreeArea(area);}

Calc *Calc::SetTarget(Calc::config c){
    conf = c;
    _t = new Target(1000, 1000, c.widht, c.height);
    _t->GenerateFigures(c.figuresCount);
    return this;
}

double Calc::Scan(Calc::config c){
    float area = 0,area1 = 0,area2 = 0;
    if(c.isRegularScan){
        area1 = _t->FreeAreaofTarget(c.regularScanW, c.regularScanH);
    }
    if(c.isRandomScan){
        area2 = _t->FreeAreaofTarget(c.iterationCount);
    }
    if(c.isRandomScan && c.isRegularScan){
        area = std::min(area1,area2);
    }
    if(area1 == 0)
        return area2;
    if(area2 == 0)
        return area1;
    if (area + 1 == 1){
        return 0;
    }
    return area;
}

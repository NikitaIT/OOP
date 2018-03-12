#ifndef RANDOM_H
#define RANDOM_H
#include <cstdlib>

class Random
{
public:
    Random(){}
    double NextDouble(){
        return ((double) std::rand() / (RAND_MAX));
    }
    int Next(int b, int e){
        return std::rand() % e + b;
    }
};

#endif // RANDOM_H

#ifndef RANDOM_H
#define RANDOM_H
#include <cstdlib>
#include <ctime>
class Random
{
public:
    Random(){std::srand(unsigned(std::time(0)));}
    double NextDouble(){
        return ((double) std::rand() / (RAND_MAX));
    }
    int Next(int b, int e){
        if(e == 0)
            return b;
        return std::rand() % e + b;
    }
};

#endif // RANDOM_H

#ifndef POINT
#define POINT

class Point{
private:
    double xCoordinate, yCoordinate;
public:
    Point(double x, double y){
        this->xCoordinate = x;
        this->yCoordinate = y;
    }
    double x() const{
        return this->xCoordinate;
    }
    double y() const{
        return this->yCoordinate;
    }
    Point& x(double newX){
        this->xCoordinate = newX;
        return *this;
    }
    Point& y(double newY){
        this->yCoordinate = newY;
        return *this;
    }
};

#endif // POINT


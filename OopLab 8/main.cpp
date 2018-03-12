#include <QCoreApplication>
#include "../Shared/include.h"
#include "polynom.h"

using namespace std;

class Manipulator{
public:
    template<typename T>
    static Polynom<T> CreateAndRun(){
        Polynom<T> p;
        Run<T>(p);
        return p;
    }
private:
    template<typename T>
    static void Run(Polynom<T> &p){
        std::cout<< typeid(T).name() << "polinom:";
        std::cout << std::endl << "c = ";
        std::cin >> p;
        std::cout << std::endl << "b = ";
        std::cin >> p;
        std::cout << std::endl << "a = ";
        std::cin >> p;
        std::cout << std::endl << "u type polinom like"<< std::endl;
        std::cout << p << std::endl;
    }

};

class AppStartup{
public:
    static void Main(QCoreApplication &app){

        auto dPoly = Manipulator::CreateAndRun<double_t>();
        auto cdPoly = Manipulator::CreateAndRun<complex<double_t>>();
        auto mPoly = Manipulator::CreateAndRun<Matrix>();
    }
private:
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    AppStartup::Main(app);
    return app.exec();
}


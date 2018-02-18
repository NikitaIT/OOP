#ifndef RADICAL_H
#define RADICAL_H
#include <cmath>
#include <cstdlib>
#include <sstream>
struct radical
{
  int radicand;

  radical(int _radicand = 0);
  std::string toString();

  int getPerfectSquare();
  bool isInteger();
};

class fraction
{
  private:
    int num;
    radical numRadical;
    int denum;

    bool isRadical;

    void reduce();

  public:
    fraction (int _num, int _denum);
    fraction (radical _num, int _denum);
    std::string toString();
};
#endif // RADICAL


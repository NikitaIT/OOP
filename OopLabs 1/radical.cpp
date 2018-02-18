#ifndef RADICAL
#define RADICAL
#include "radical.h"
#define ROOTSIGN ((char)0xAC + std::string("/"))


fraction::fraction (int _num, int _denum = 1)
{
  num = _num;
  denum = _denum;

  isRadical = false;

  reduce();
}

fraction::fraction (radical _num, int _denum = 1): numRadical(_num)
{
  denum = _denum;

  isRadical = true;

  reduce();
}

std::string fraction::toString()
{
  std::stringstream ss;
  if (denum == 0)
    ss << "NaN. Shouldn't be here.";
  else
  {
    if (!isRadical)
      ss << num;
    else
      ss << numRadical.toString();

    if (denum > 1)
      ss << '/' << denum;
  }
  return ss.str();
}

void fraction::reduce()
{
  int a, b;
  if (!isRadical)
  {
    a = abs(num);
    b = abs(denum);
  }
  else
  {
    a = abs(numRadical.getPerfectSquare());
    b = abs(denum);
  }

  if (a < b)
  {
    a ^= b;
    b ^= a;
    a ^= b;
  }
  while (a*b != 0)
  {
    int tmp = b;
    b = a%b;
    a = tmp;
  }

  int gcd = a + b;

  if (denum < 0)
    gcd *= -1;

  if (!isRadical)
    num /= gcd;
  else
    numRadical.radicand /= gcd*gcd;

  denum /= gcd;
}

radical::radical(int _radicand)
{
  radicand = _radicand;
}

std::string radical::toString()
{
  std::stringstream ss;
  if (radicand < 0)
  {
    ss << "i*";
    radicand *= -1;
  }

  if (radicand == 0)
    ss << 0;
  else
  {
    int perfectSquare = getPerfectSquare();
    if (perfectSquare != 1)
      ss << perfectSquare;

    perfectSquare *= perfectSquare;
    if (radicand != perfectSquare)
      ss << ROOTSIGN << radicand/perfectSquare;
  }
  return ss.str();
}

int radical::getPerfectSquare()
{
  int a = abs(radicand), square = 1;
  int maxDiv = floor(sqrt(a));

  for (int i = 2; i <= maxDiv; i++)
  {
    while (a % (i*i) == 0)
    {
      a /= i*i;
      square *= i;
    }
    maxDiv = floor(sqrt(a));
  }

  return square;
}

bool radical::isInteger()
{
  int s = getPerfectSquare();
  return (radicand == s*s);
}
#endif

#include "polynom.h"
#include <complex>
template <>
string Polynom<double>::ToString() const{
    auto s = stringstream();
    auto c = *this->Koefs;
    size_type i, n=RealLength();
    if (n != 0)
      {
        if (c[0] != 0)
          {
            s << c[0];
          }
        for (i = 1; i < c.size(); i++)
          {
            if (c[i] < 0)
              {
                if(c[i]!=-1)
                  s << c[i] << "X^" << i;
                else
                  s << "-" << "X^" << i;
              }
            else
              {
                if (c[i] != 0)
                  {
                    if(c[i] != 1)
                      s << "+" << c[i] << "X^" << i;
                    else
                      s<< "+" << "X^" << i;
                  }
              }
          }
        s << '\n';
      }
    else
      {
        s << 0;
      }
    return s.str();
  }
template <>
string Polynom<complex<double>>::ToString() const{
    auto s = stringstream();
    auto c = *this->Koefs;
    size_type i, n=RealLength();
    if (n != 0)
      {
        s << c[0];
        for (i = 1; i < c.size(); i++)
          {
            if (c[i].real() < 0)
              {
                if(c[i].real()!=-1 || c[i].imag()!=0)
                  s << c[i] << "X^" << i;
                else
                  s << "-" << "X^" << i;
              }
            else
              {
                if (c[i].real() != 0)
                  {
                    if(c[i].real() != 1 || c[i].imag()!=0)
                      s << "+" << c[i] << "X^" << i;
                    else
                      s<< "+" << "X^" << i;
                  }
              }
          }
        s << '\n';
      }
    else
      {
        s << 0;
      }
    return s.str();
  }
template <>
bool Polynom<double>::isDiscr(value_type discr) const{
  return value_type(discr) >= value_type(0);
}
template <>
bool Polynom<complex<double>>::isDiscr(value_type discr) const{
  return true;
}

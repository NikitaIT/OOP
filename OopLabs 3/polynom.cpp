#include "polynom.h"

/*

    start ToString

*/
template <>
string Polynom<double>::ToString(){
    auto s = stringstream();
    auto c = *this->Koefs;
    size_type i, n=realLength<value_type>();
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
string Polynom<complex<double>>::ToString(){
    auto s = stringstream();
    auto c = *this->Koefs;
    size_type i, n=realLength<value_type>();
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
string Polynom<Matrix>::ToString(){
  auto s = stringstream();
  auto c = *this->Koefs;
  size_type i, n=c.size();
  if (n != 0)
    {
      if (!(c[0] == *c[0].GetEqualScale(0)))
        {
          s << c[0].toString();
        }
      for (i = 1; i < c.size(); i++)
        {
            if (!(c[i] == *c[i].GetEqualScale(0)))
              {
                  if(!(c[i] == *c[i].GetEqualScale(1)))
                    s << "+" << c[i].toString() << "X^" << i;
                  else
                    s<< "+" << "X^" << i;
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
/*

    end ToString

    start isDiscr

*/

template <>
bool Polynom<double>::isDiscr(value_type discr){
  return value_type(discr) >= value_type(0);
}
template <>
bool Polynom<complex<double>>::isDiscr(value_type discr){
  return true;
}
template <>
bool Polynom<Matrix>::isDiscr(value_type discr){
    return true;
}
/*

    end isDiscr

*/


template <>
pair<std::complex<double>,std::complex<double>> *Polynom<std::complex<double>>::calculateRoots(){
    if(size() != 3)
      return NULL;

    auto koefs = *this->Koefs;
    auto a = koefs[2], b = koefs[1], c = koefs[0];

    if(a == value_type(0))
    {
        if (b != value_type(0))
          return  new pair<value_type,value_type>(value_type(-1.)*c/b,value_type(-1.)*c/b);
        else if (c == value_type(0))
           return NULL;//"Все коэффициенты равны нулю; x - любое число."
         else
           return NULL;//"Нет решений."
    }


    value_type discr = b*b - value_type(4)*a*c;
    if(isDiscr(discr))
    {
        return new pair<value_type,value_type>(
              ( value_type(-1)*b + sqrt(discr) ) / (value_type(2) * a),
              ( value_type(-1)*b - sqrt(discr) ) / (value_type(2) * a)
        );
    }
    return NULL;
  }

template <>
pair<Matrix, Matrix> *Polynom<Matrix>::calculateRoots() {
    if(size() != 3)
      return NULL;

    auto koefs = *this->Koefs;
    vector<complex<double>> a = koefs[0].diag_vec(), b = koefs[1].diag_vec(), c = koefs[2].diag_vec();
    Matrix result1(Matrix(a.size(),0));
    Matrix result2(Matrix(a.size(),0));
    Polynom<std::complex<double>> pln;
    for(size_t i = 0; i < a.size() ;i++){
        pln.Koefs->emplace_back(a[i]);
        pln.Koefs->emplace_back(b[i]);
        pln.Koefs->emplace_back(c[i]);
        auto roots = pln.calculateRoots();
        if(roots == NULL){
            return NULL;
        }
        result1(i,i) = roots->first;
        result2(i,i) = roots->second;
        pln.Koefs->clear();
    }

    return new pair<value_type,value_type>(
          result1,
          result2
    );
}

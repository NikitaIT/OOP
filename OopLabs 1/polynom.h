#ifndef POLYNOM_H
#define POLYNOM_H
#include<iomanip>
#include <vector>
#include <sstream>
#include <algorithm>
#include <complex>
#include "radical.h"
using namespace std;

typedef double number;

template<typename _Tp = number, typename _Alloc = std::allocator<_Tp> >
class Polynom
{
  typedef _Alloc                        		 allocator_type;
  typedef _Tp                                            value_type;
  typedef size_t					 size_type;

public:

  vector<_Tp,_Alloc>* Koefs;

  Polynom()
    :Koefs(new vector<_Tp,_Alloc>()) { }

  /**
   *  @brief  Creates a %Polynom with no elements.
   *  @param  __a  An allocator object.
   */
  Polynom(const allocator_type& __a)
    :Koefs( new vector<_Tp,_Alloc>( __a) ){}
  /**
   *  @brief  Creates a %vector with default constructed elements.
   *  @param  __n  The number of elements to initially create.
   *  @param  __a  An allocator.
   *
   *  This constructor fills the %vector with @a __n default
   *  constructed elements.
   */
  Polynom(size_type __n, const allocator_type& __a = allocator_type())
    :Koefs(new vector<_Tp,_Alloc>(__n, __a)){}

  /**
   *  @brief  Creates a %Polynom with copies of an exemplar element.
   *  @param  __n  The number of elements to initially create.
   *  @param  __value  An element to copy.
   *  @param  __a  An allocator.
   *
   *  This constructor fills the %Polynom with @a __n copies of @a __value.
   */
  Polynom(size_type __n, const value_type& __value, const allocator_type& __a = allocator_type())
    :Koefs(new vector<_Tp,_Alloc>(__n,__value, __a)){}

  ~Polynom()
  {
    vector<_Tp,_Alloc>().swap(*this->Koefs);
  }
  value_type operator[](size_type i) {return this->Koefs[i];}
  size_type size() {return this->Koefs->size();}

  value_type calculateValue(value_type x){

      return PolinomGorner(*this->Koefs,x);
  }

  static value_type PolinomGorner(vector<_Tp,_Alloc>  &a, value_type x)
  {
      int n = a.size() - 1;
      value_type y = a[n];
      for (size_type w = n - 1; w > 0; w--)
      {
          y = x*y + a[w];
      }
      return y;
  }
  pair<value_type,value_type> *calculateRoots(){
    if(size() != 3)
      return NULL;

    auto koefs = *this->Koefs;
    auto a = koefs[0], b = koefs[1], c = koefs[2];

    if(a == 0)
    {
        if (b != 0)
          return  new pair<value_type,value_type>(-1.*c/b,-1.*c/b);
        else if (c == 0)
           return NULL;//"Все коэффициенты равны нулю; x - любое число."
         else
           return NULL;//"Нет решений."
    }


    auto discr = b*b - 4*a*c;
    if(discr >= 0)
    {
        return new pair<value_type,value_type>(
              ( -1*b + sqrt(discr) ) / (2 * a),
              ( -1*b - sqrt(discr) ) / (2 * a)
        );
    }
    if (discr != 0)
    {
      /*
      radical dRoot (discr);

      if (dRoot.isInteger())
      {
         return new pair<value_type,value_type>(
               fraction(-b + sqrt(discr), 2*a).toString() ,
               fraction(-b - sqrt(discr), 2*a).toString()
         );
      }
      else
      {
        std::string rational = fraction(-b, 2*a).toString(),
                    irrational = fraction(radical(discriminant), 2*a).toString();
        if (rational == "0")
          return new pair<value_type,value_type>(
                irrational ,
                -irrational
          );
        else
          return new pair<value_type,value_type>(
                rational +" + " +irrational ,
                rational +" - " +irrational
          );
      }
      */
    }
    return NULL;
  }
  static string GetX(size_type i){
    return i==1
           ? "X+"
           : i==0
            ? "+"
            : "X^"+ to_string(i) ;
  }
  size_type realLength(){
    size_type n=0;
    for (size_type i = 0; i < (*this->Koefs).size(); i++)
      {
        if ((*this->Koefs)[i] != 0)
          n++;
      }
    return n;
  }
  string ToString(){
    auto s = stringstream();
    auto c = *this->Koefs;
    size_type i, n=realLength();
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
};

#endif // POLYNOM_H

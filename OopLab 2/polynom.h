#ifndef POLYNOM_H
#define POLYNOM_H
#include "../Shared/include.h"
using namespace std;

typedef complex<double> number;

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

    string ToString() const;
    bool isDiscr(value_type discr) const;

    value_type operator[](size_type i) {return this->Koefs[i];}
    size_type size() const {return this->Koefs->size();}

    value_type calculateValue(value_type x) const{

        return PolinomGorner(*this->Koefs,x);
    }

    static value_type PolinomGorner(vector<_Tp,_Alloc>  &a, value_type x)
    {
        int n = a.size() - 1;
        value_type y = a[n];

        for (size_type w = n; w > 0;w--)
        {
            y = x*y + a[w - 1];
        }
        return y;
    }

    static string GetX(size_type i){
        return i==1
                ? "X+"
                : i==0
                  ? "+"
                  : "X^"+ to_string(i) ;
    }


    size_type RealLength() const{
        size_type n=0;
        for (size_type i = 0; i < (*this->Koefs).size(); i++)
        {
            if ((*this->Koefs)[i] != value_type(0))
                n++;
        }
        return n;
    }
    pair<value_type,value_type> *calculateRoots() const{
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
};
#endif // POLYNOM_H

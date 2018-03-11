#ifndef POLYNOM_H
#define POLYNOM_H
#include "include.h"
#include "matriximpl.h"
#include "parse.h"
using namespace std;

template<typename _Tp = Matrix, typename _Alloc = std::allocator<_Tp> >
class Polynom
{
public:
    typedef _Alloc                        		 allocator_type;
    typedef _Tp                                            value_type;
    typedef size_t					 size_type;


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
    size_type size() const{return this->Koefs->size();}

    Matrix calculateValue(Matrix x) const{
        auto koefs = *this->Koefs;
        vector<complex<double>> a = koefs[0].diag_vec(), b = koefs[1].diag_vec(), c = koefs[2].diag_vec(), root = x.diag_vec();
        Matrix result1(Matrix(a.size(),0));
        Polynom<std::complex<double>> pln;
        for(size_t i = 0; i < a.size() ;i++){
            pln.Koefs->emplace_back(a[i]);
            pln.Koefs->emplace_back(b[i]);
            pln.Koefs->emplace_back(c[i]);
            result1(i,i) = pln.calculateValue(root[i]);
            pln.Koefs->clear();
        }
        return result1;
    }
    complex<double> calculateValue(complex<double> x) const{

        return PolinomGorner(*this->Koefs,x);
    }

    static value_type PolinomGorner(vector<Polynom::value_type,
                                    Polynom::allocator_type> &a,
                                    Polynom::value_type x)
    {
        int n = a.size() - 1;
        value_type y = a[n];

        for (size_type w = n; w > 0;w--)
        {
            y = x*y + a[w - 1];
        }
        return y;
    }
    bool isDiscr(value_type discr) const;

    pair<value_type, value_type> *calculateRoots() const;

    static string GetX(size_type i){
        return i==1
                ? "X+"
                : i==0
                  ? "+"
                  : "X^"+ to_string(i) ;
    }
    template<typename T>
    size_type realLength() const{
        size_type n=0;
        for (size_type i = 0; i < (*this->Koefs).size(); i++)
        {
            if ((*this->Koefs)[i] != T(0))
                n++;
        }
        return n;
    }
    string ToString() const;

    template <typename T>
    friend ostream &operator<<(ostream &, const Polynom<T> &);

    template <typename T>
    friend istream &operator>>(istream &, Polynom<T> &);

};
template <typename T>
ostream &operator<<(ostream &os, const Polynom<T> &dt)
{
    os << dt.ToString();
    auto roots = dt.calculateRoots();
    os << "roots:"<< std::endl;
    if(roots == NULL)
    {
        os <<"NaN";
        return os;
    }
    os << Parse::parse(roots->first).toStdString() << std::endl << Parse::parse(roots->second).toStdString();
    return os;
}
#endif // POLYNOM_H

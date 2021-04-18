#include <iostream>

class Rational
{
private:
    double numer, denom;
public:
    Rational()
    {
        this->numer = 0;
        this->denom = 0 ;
    }
    Rational(int a, int b)
    {
        this->numer = a;
        this->denom = b;
    }
    //RoFL __declspec(dllexport) static _Ret_valid_ int __stdcall gcd(_In_ _Satisfies_impl_(__Curr__ < INT32_MAX & __Curr__ > INT32_MIN) int a, _In_ int b)
    static int gcd(int a, int b)
    {
        if (a < 0)
        {
            a = -a;
        }
        if (b < 0)
        {
            b = -b;
        }
        if (a == b)
        {
            return a;
        }
        if (a == 0)
        {
            if (b == 0)
            {
                return 0;
            }
            else
            {
                return b;
            }
        }
        else if (b == 0)
        {
            if (a == 0)
            {
                return 0;
            }
            else
            {
                return a;
            }
        }
        else if (a > b)
        {
            long tmp = a;
            a = b;
            b = tmp;
        }
        return gcd(a, b - a);
    }
    bool operator== (Rational x)
    {
        if (this->denom == 0 && x.numer == 0)
        {
            return 0;
        }
        else
        {
            if ((this->numer / this->denom) == (x.numer / x.denom))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    char is_inf()
    {
        if (this->denom != 0)
        {
            return 0;
        }
        if (this->numer == 0)
        {
            return 0;
        }
        return this->numer > 0 ? 1 : -1;
    }
    Rational operator+(Rational x)
    {
        if ((this->denom == 0 && this->numer == 0) || (x.denom == 0 && x.numer==0))
        {
            return Rational(0, 0);
        }
        if (this->is_inf() || x.is_inf())
        {
            if (this->is_inf() && x.is_inf())
            {
                auto sign = this->is_inf() + x.is_inf();
                return (sign == 0 && !(this->numer + x.numer)) ? Rational(0, 0) : Rational(sign * 1, 0);
            }
            return this->is_inf() ? *this : x;
        }
        return Rational(this->numer * x.denom + this->denom * x.numer, this->denom * x.denom);
    }
    Rational operator-(Rational x)
    {
        if ((this->denom == 0 && this->numer == 0) || (x.denom == 0 && x.numer == 0))
        {
            return Rational(0, 0);
        }
        if (this->is_inf() || x.is_inf())
        {
            if (this->is_inf() && x.is_inf())
            {
                auto sign = this->is_inf() + -x.is_inf();
                return (sign == 0 && !(this->numer + x.numer)) ? Rational(0, 0) : Rational(sign * 1, 0);
            }
            return this->is_inf() ? *this : Rational(-x.numer,0);
        }
        return Rational(this->numer * x.denom - this->denom * x.numer, this->denom * x.denom);
    }
    Rational operator*(Rational x)
    {
        return Rational(this->numer * x.numer, this->denom * x.denom);
    }
    Rational operator/(Rational x)
    {
        if ((this->denom == 0 && this->numer == 0) || (x.denom == 0 && x.numer == 0))
        {
            return Rational(0, 0);
        }
        if (this->is_inf() || x.is_inf())
        {
            if (this->is_inf() && x.is_inf())
            {
                return Rational(0, 0);
            }
            return this->is_inf() ?
                ((double(x) >= 0 && (double(*this) >= 0)
                    || (double(x) < 0 && (double(*this) < 0))))
                ? Rational(1, 0) : Rational(-1, 0) : Rational(0, 1);
        }
        return Rational(this->numer * x.denom, this->denom * x.numer);
    }
    operator double()
    {
        return this->numer / this->denom;
    }
    operator bool()
    {
        if (this->denom != 0 && this->numer == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    int numerator()
    {
        return this->numer;
    }
    int denominator()
    {
        return this->denom;
    }
    bool isNaN()
    {
        return (this->numer == 0 && this->denom==0) ? 1 : 0;
    }
};

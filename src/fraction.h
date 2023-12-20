#ifndef __FRACTION_H
#define __FRACTION_H

#include <ostream>

class Fraction
{
private:
    int num;
    int denom;

    friend operator<<(std::ostream &os, Fraction &f);

public:
    Fraction();
    Fraction(int num, int denom);
    ~Fraction();

    void reduce();
    int gcd(int num, int denom);
};

Fraction::Fraction()
{
    num = 1;
    denom = 1;
}

Fraction::Fraction(int num, int denom)
{
    this->num = num;
    this->denom = denom;

    reduce();
}

Fraction::~Fraction()
{
}

void Fraction::reduce()
{
    int frac_gcd = gcd(num, denom);
    num = num / frac_gcd;
    denom = denom / frac_gcd;
}

int Fraction::gcd(int u, int v)
{
    if (v != 0)
        return gcd(v, u % v);
    else
        return u;
}

// overload <<
std::ostream &operator<<(std::ostream &os, const Fraction &f)
{
    // num and demon is not member function
    // so we cannot access the private members.
    // * we need to say that operator<< is the friend of class Fraction
    os << f.num << " / " << f.denom;
}

#endif
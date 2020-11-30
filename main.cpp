#include <iostream>
 
class Fraction
{
private:
	int m_numerator{ 0 };
	int m_denominator{ 1 };

    void reduce();
 
public:
	Fraction(int num = 0, int denom = 1): m_numerator{num}, m_denominator{denom}
    {
        reduce();
    }

    // greatest common denominator
    static int gcd(int a, int b) {
        return (b == 0) ? (a > 0 ? a : -a) : gcd(b, a % b);
    }

    friend Fraction operator*(const Fraction &f1, const Fraction &f2);
    // We can remove the two operators below, and the program will still work
    // (because of conversion of int to Fraction using the constructor Fraction(int, int))
    // However, it'll be slower, so it's better to implement overloaded variants
    friend Fraction operator*(const Fraction &f, int value);
    friend Fraction operator*(int value, const Fraction &f);
    
	void print() const { std::cout << m_numerator << '/' << m_denominator << '\n'; }
};

void Fraction::reduce() {
    if (m_numerator == 0)
    {
        return;
    }

    int gcdValue{ Fraction::gcd(m_numerator, m_denominator) };

    m_numerator /= gcdValue;
    m_denominator /= gcdValue;
}

Fraction operator*(const Fraction &f1, const Fraction &f2)
{
    Fraction fr{ f1.m_numerator * f2.m_numerator, f1.m_denominator * f2.m_denominator };

    fr.reduce();

    return fr;
}

Fraction operator*(const Fraction &f, int value)
{
    Fraction fr{ f.m_numerator * value, f.m_denominator };

    fr.reduce();

    return fr;
}

Fraction operator*(int value, const Fraction &f)
{
    return f * value;
}

int main()
{
	Fraction f1{2, 5};
    f1.print();
 
    Fraction f2{3, 8};
    f2.print();
 
    Fraction f3{ f1 * f2 };
    f3.print();
 
    Fraction f4{ f1 * 2 };
    f4.print();
 
    Fraction f5{ 2 * f2 };
    f5.print();
 
    // if we remove const from operator*(const Fraction &f1, const Fraction &f2),
    // this line won't work, because we're multiplying temporary Fraction objects,
    // and non-const references cannot bind to temporaries
    Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
    f6.print();

    Fraction f7{0, 6};
    f7.print();
 
	return 0;
}
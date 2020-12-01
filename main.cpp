#include <iostream>
#include <limits>
 
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

	friend std::ostream& operator<<(std::ostream &out, const Fraction &f);
	friend std::istream& operator>>(std::istream &in, Fraction &f);
};

void Fraction::reduce() {
    if (m_numerator == 0 || m_denominator == 0)
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

std::ostream& operator<<(std::ostream &out, const Fraction &f)
{
    out << f.m_numerator << '/' << f.m_denominator;

    return out;
}

std::istream& operator>>(std::istream &in, Fraction &f)
{
    in >> f.m_numerator;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '/');
    in >> f.m_denominator;

    f.reduce();

    return in;
}

int main()
{
	Fraction f1{2, 5};
    std::cout << f1 << '\n';
 
    Fraction f2{3, 8};
    std::cout << f2 << '\n';
 
    Fraction f3{ f1 * f2 };
    std::cout << f3 << '\n';
 
    Fraction f4{ f1 * 2 };
    std::cout << f4 << '\n';
 
    Fraction f5{ 2 * f2 };
    std::cout << f5 << '\n';
 
    // if we remove const from operator*(const Fraction &f1, const Fraction &f2),
    // this line won't work, because we're multiplying temporary Fraction objects,
    // and non-const references cannot bind to temporaries
    Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
    std::cout << f6 << '\n';

    Fraction f7{0, 6};
    std::cout << f7 << '\n';

    Fraction f8{};
    std::cout << "Enter fraction 1 (in x/y format): ";
    std::cin >> f8;

    Fraction f9{};
    std::cout << "Enter fraction 2: ";
    std::cin >> f9;

    std::cout << f8 << " * " << f9 << " is " << f8 * f9 << '\n';

	return 0;
}
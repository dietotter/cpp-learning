#include <iostream>
#include <stdexcept>
#include <exception>

class Fraction
{
private:
	int m_numerator{};
	int m_denominator{ 1 };

public:
	Fraction(int numerator = 0, int denominator = 1)
		: m_numerator{ numerator }, m_denominator{ denominator }
	{
		if (m_denominator == 0)
		{
			throw std::runtime_error("Invalid denominator");
		}
	}

	friend std::ostream& operator<<(std::ostream &out, const Fraction &fr);
};

std::ostream& operator<<(std::ostream &out, const Fraction &fr)
{
	out << fr.m_numerator << '/' << fr.m_denominator;

	return out;
}

int main()
{
	int numerator, denominator;
	
	std::cout << "Enter numerator: ";
	std::cin >> numerator;

	std::cout << "Enter denominator: ";
	std::cin >> denominator;

	try
	{
		Fraction fr{ numerator, denominator };

		std::cout << fr << '\n';
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << '\n';
	}

	return 0;
}
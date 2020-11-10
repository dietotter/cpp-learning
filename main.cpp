#include <iostream>
 
struct AdvertisingData
{
    int adsAmount;
    double clickedPercent;
    double averageProfit;
};

void printAdvertisingInfo(AdvertisingData advData)
{
    std::cout << "From "<< advData.adsAmount << " ads, "
        << advData.clickedPercent << "% of them were clicked, resulting in "
        << advData.averageProfit << " dollars earned from each.\nOverall profit: "
        << advData.adsAmount * advData.clickedPercent / 100 * advData.averageProfit << '\n';
}

struct Fraction
{
    int numerator;
    int denominator;
};

Fraction readFraction()
{
    std::cout << "Numerator: ";
    int numerator{};
    std::cin >> numerator;

    std::cout << "Denominator: ";
    int denominator{};
    std::cin >> denominator;

    return { numerator, denominator };
}

double multiplyFractions(Fraction firstFr, Fraction secondFr)
{
    Fraction resultingFraction { firstFr.numerator * secondFr.numerator, firstFr.denominator * secondFr.denominator };

    return static_cast<double>(resultingFraction.numerator) / resultingFraction.denominator;
}

int main()
{
    Fraction firstFraction{ readFraction() };
    Fraction secondFraction{ readFraction() };

    std::cout << "Multiplication of fractions result: " << multiplyFractions(firstFraction, secondFraction) << '\n';

    return 0;
}
#include "Average.h"
#include "IntArray.h"
#include "FixedPoint2.h"

#include <iostream>

IntArray fillArray()
{
	IntArray a(5);
 
	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;
 
	return a;
}

void testAddition()
{
	// h/t to reader Sharjeel Safdar for this function
	std::cout << std::boolalpha;
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 }) << '\n'; // both positive, no decimal overflow
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 }) << '\n'; // both positive, with decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }) << '\n'; // both negative, no decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }) << '\n'; // both negative, with decimal overflow
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 }) << '\n'; // second negative, no decimal overflow
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 }) << '\n'; // second negative, possible decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 }) << '\n'; // first negative, no decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 }) << '\n'; // first negative, possible decimal overflow
}

int main()
{
    // Average avg{};
	
	// avg += 4;
	// std::cout << avg << '\n'; // 4 / 1 = 4
	
	// avg += 8;
	// std::cout << avg << '\n'; // (4 + 8) / 2 = 6
 
	// avg += 24;
	// std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12
 
	// avg += -10;
	// std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5
 
	// (avg += 6) += 10; // 2 calls chained together
	// std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7
 
	// Average copy{ avg };
	// std::cout << copy << '\n';

    // IntArray a{ fillArray() };
	// std::cout << a << '\n';
 
	// auto &ref{ a }; // we're using this reference to avoid compiler self-assignment errors
	// a = ref;
 
	// IntArray b(1);
	// b = a;
 
	// std::cout << b << '\n';
    
    // FixedPoint2 a{ 34, 123 };
	// std::cout << a << '\n';
 
	// FixedPoint2 b{ -213, 8 };
	// std::cout << b << '\n';
 
	// FixedPoint2 c{ 2, -8 };
	// std::cout << c << '\n';
 
	// FixedPoint2 d{ -2, -108 };
	// std::cout << d << '\n';
 
	// FixedPoint2 e{ 0, -5 };
	// std::cout << e << '\n';
 
	// std::cout << static_cast<double>(e) << '\n';

    // FixedPoint2 a{ 0.01 };
	// std::cout << a << '\n';
 
	// FixedPoint2 b{ -0.01 };
	// std::cout << b << '\n';
 
	// FixedPoint2 c{ 5.01 }; // stored as 5.0099999... so we'll need to round this
	// std::cout << c << '\n';
 
	// FixedPoint2 d{ -5.129 }; // stored as -5.0099999... so we'll need to round this
	// std::cout << d << '\n';

    testAddition();
 
	FixedPoint2 a{ -0.48 };
	std::cout << a << '\n';
 
	std::cout << -a << '\n';
 
	std::cout << "Enter a number: "; // enter 5.678
	std::cin >> a;
	
	std::cout << "You entered: " << a << '\n';
 
	return 0;
}
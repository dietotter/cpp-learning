#include "Pair1.h"
#include "Pair.h"
#include "StringValuePair.h"

#include <iostream>

int main()
{
	Pair1<int> p1(5, 8);
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
 
	const Pair1<double> p2(2.3, 4.5);
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
 
	Pair<int, double> p3(5, 6.7);
	std::cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';
 
	const Pair<double, int> p4(2.3, 4);
	std::cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';
	
	StringValuePair<int> svp("Hello", 5);
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

	return 0;
}
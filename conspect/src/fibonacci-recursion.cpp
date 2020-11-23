#include <iostream>
#include <vector>
 
int fibonacci(int count)
{
	// We'll use a static std::vector to cache calculated results
	static std::vector<int> results{ 0, 1 };
 
	// If we've already seen this count, then use the cache'd result
	if (count < static_cast<int>(std::size(results)))
		return results[count];
	else
	{
		// Otherwise calculate the new result and add it
		results.push_back(fibonacci(count - 1) + fibonacci(count - 2));
		return results[count];
	}
}
 
// And a main program to display the first 13 Fibonacci numbers
int main()
{
    // The memoized version of this function will call fibonacci() 35 times,
    // instead of 1205 if fibonacci was made with just regular recursion
	for (int count = 0; count < 13; ++count)
		std::cout << fibonacci(count) << " ";
 
	return 0;
}
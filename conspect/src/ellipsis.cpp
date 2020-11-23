#include <iostream>
#include <cstdarg> // needed to use ellipsis
#include <string>
 
// The ellipsis must be the last parameter
// count is how many additional arguments we're passing
double findAverage(int count, ...)
{
    double sum = 0;
 
    // We access the ellipsis through a va_list, so let's declare one
    va_list list;
 
    // We initialize the va_list using va_start.  The first parameter is
    // the list to initialize.  The second parameter is the last non-ellipsis
    // parameter.
    va_start(list, count);
 
    // Loop through all the ellipsis arguments
    for (int arg=0; arg < count; ++arg)
         // We use va_arg to get parameters out of our ellipsis
         // The first parameter is the va_list we're using
         // The second parameter is the type of the parameter
         sum += va_arg(list, int);
 
    // Cleanup the va_list when we're done.
    va_end(list);
 
    return sum / count;
}

double findAverageUsingSentinel(int first, ...)
{
	// We have to deal with the first number specially
	double sum = first;
 
	// We access the ellipsis through a va_list, so let's declare one
	va_list list;
 
	// We initialize the va_list using va_start.  The first parameter is
	// the list to initialize.  The second parameter is the last non-ellipsis
	// parameter.
	va_start(list, first);
 
	int count = 1;
	// Loop indefinitely
	while (true)
	{
		// We use va_arg to get parameters out of our ellipsis
		// The first parameter is the va_list we're using
		// The second parameter is the type of the parameter
		int arg = va_arg(list, int);
 
		// If this parameter is our sentinel value, stop looping
		if (arg == -1)
			break;
 
		sum += arg;
		count++;
	}
 
	// Cleanup the va_list when we're done.
	va_end(list);
 
	return sum / count;
}

double findAverageUsingDecoder(std::string decoder, ...)
{
	double sum = 0;
 
	// We access the ellipsis through a va_list, so let's declare one
	va_list list;
 
	// We initialize the va_list using va_start.  The first parameter is
	// the list to initialize.  The second parameter is the last non-ellipsis
	// parameter.
	va_start(list, decoder);
 
	int count = 0;
	// Loop indefinitely
	while (true)
	{
		char codetype = decoder[count];
		switch (codetype)
		{
		default:
		case '\0':
			// Cleanup the va_list when we're done.
			va_end(list);
			return sum / count;
 
		case 'i':
			sum += va_arg(list, int);
			count++;
			break;
 
		case 'd':
			sum += va_arg(list, double);
			count++;
			break;
		}
	}
}

int main()
{
    std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n';
    std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n';

    std::cout << findAverageUsingSentinel(1, 2, 3, 4, 5, -1) << '\n';
	std::cout << findAverageUsingSentinel(1, 2, 3, 4, 5, 6, -1) << '\n';

    std::cout << findAverageUsingDecoder("iiiii", 1, 2, 3, 4, 5) << '\n';
	std::cout << findAverageUsingDecoder("iiiiii", 1, 2, 3, 4, 5, 6) << '\n';
	std::cout << findAverageUsingDecoder("iiddi", 1, 2, 3.5, 4.5, 5) << '\n';
}
#include <iostream>
#include <cassert>
#include <cstddef>
 
class IntArray
{
private:
	int *m_array{};
	int m_length{};
 
public:
	IntArray(int length) // constructor
	{
		assert(length > 0);
 
		m_array = new int[static_cast<std::size_t>(length)]{};
		m_length = length;
	}
 
	~IntArray() // destructor
	{
		// Dynamically delete the array we allocated earlier
		delete[] m_array;
	}
 
	void setValue(int index, int value) { m_array[index] = value; }
	int getValue(int index) { return m_array[index]; }
 
	int getLength() { return m_length; }
};
 
int main()
{
	IntArray ar(10); // allocate 10 integers
	for (int count{ 0 }; count < ar.getLength(); ++count)
		ar.setValue(count, count+1);
 
	std::cout << "The value of element 5 is: " << ar.getValue(5) << '\n';
 
	return 0;
} // ar is destroyed here, so the ~IntArray() destructor function is called here

// Note 1:
// IntArray class is example of implementing RAII pattern (Resource Acquisition Is Initialization)

// Note 2:
// If compiling this example and getting the error:
// error: 'class IntArray' has pointer data members [-Werror=effc++]|
// error:   but does not override 'IntArray(const IntArray&)' [-Werror=effc++]|
// error:   or 'operator=(const IntArray&)' [-Werror=effc++]|
// 
// Then I can either remove the “-Weffc++” flag from compile settings for this example,
// or I can add the following two lines to the class:
// IntArray(const IntArray&) = delete;
// IntArray& operator=(const IntArray&) = delete;
#include <cassert> // for assert()
#include <initializer_list> // for std::initializer_list
#include <iostream>
 
class IntArray
{
private:
	int m_length{};
	int *m_data{};
 
public:
	IntArray() = default;
 
	IntArray(int length) :
		m_length{ length },
		m_data{ new int[length]{} }
	{
 
	}
 
	IntArray(std::initializer_list<int> list) : // allow IntArray to be initialized via list initialization
		IntArray(static_cast<int>(list.size())) // use delegating constructor to set up initial array
	{
		// Now initialize our array from the list
		int count{ 0 };
		for (auto element : list)
		{
			m_data[count] = element;
			++count;
		}
	}
 
	~IntArray()
	{
		delete[] m_data;
		// we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
	}
 
	IntArray(const IntArray&) = delete; // to avoid shallow copies
	IntArray& operator=(const IntArray& list) = delete; // to avoid shallow copies
 
	int& operator[](int index)
	{
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}
 
	int getLength() const { return m_length; }
};
 
int main()
{
	IntArray array{ 5, 4, 3, 2, 1 }; // initializer list
	for (int count{ 0 }; count < array.getLength(); ++count)
		std::cout << array[count] << ' ';
 
	return 0;
}

// Notes about list constructor:

// On line 21: Note that we don’t pass the list by const reference.
// Much like std::string_view, std::initializer_list is very lightweight
// and copies tend to be cheaper than an indirection.

// On line 22: We delegate allocating memory for the IntArray to the other constructor
// via a delegating constructor (to reduce redundant code).
// This other constructor needs to know the length of the array,
// so we pass it list.size(), which contains the number of elements in the list.
// Note that list.size() returns a size_t (which is unsigned) so we need to cast to a signed int here.
// We use direct initialization, rather than brace initialization,
// because brace initialization prefers list constructors. Although the constructor would get resolved correctly,
// it’s safer to use direct initialization to initialize classes with list constructors if we don’t want to use the list constructor.

// The body of the constructor is reserved for copying the elements from the list into our IntArray class.
// For some inexplicable reason, std::initializer_list does not provide access to the elements of the list via subscripting (operator[]).
// However, there are easy ways to work around the lack of subscripts. The easiest way is to use a for-each loop here.
// The for-each loops steps through each element of the initialization list, and we can manually copy the elements into our internal array.
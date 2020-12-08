#include <iostream>
#include <string>
 
class Car
{
private:
	std::string m_name;
	int m_id;
 
public:
	Car(const std::string& name, int id)
		: m_name{ name }, m_id{ id }
	{
	}
 
	const std::string& getName() const { return m_name; }
	int getId() const { return m_id;  }
};
 
// Our CarLot is essentially just a static array of Cars and a lookup function to retrieve them.
// Because it's static, we don't need to allocate an object of type CarLot to use it
class CarLot
{
private:
	static Car s_carLot[4];
 
public:
	CarLot() = delete; // Ensure we don't try to create a CarLot
 
	static Car* getCar(int id)
	{
		for (int count{ 0 }; count < 4; ++count)
		{
			if (s_carLot[count].getId() == id)
			{
				return &(s_carLot[count]);
			}
		}
		
		return nullptr;
	}
};
 
Car CarLot::s_carLot[4]{ { "Prius", 4 }, { "Corolla", 17 }, { "Accord", 84 }, { "Matrix", 62 } };
 
class Driver
{
private:
	std::string m_name;
	int m_carId; // we're associated with the Car by ID rather than pointer
 
public:
	Driver(const std::string& name, int carId)
		: m_name{ name }, m_carId{ carId }
	{
	}
 
	const std::string& getName() const { return m_name; }
	int getCarId() const { return m_carId; }
};
 
int main()
{
	Driver d{ "Franz", 17 }; // Franz is driving the car with ID 17
 
	Car *car{ CarLot::getCar(d.getCarId()) }; // Get that car from the car lot
	
	if (car)
		std::cout << d.getName() << " is driving a " << car->getName() << '\n';
	else
		std::cout << d.getName() << " couldn't find his car\n";
 
	return 0;
}

// In this particular example, doing things this way is kind of silly,
// since getting the Car out of the CarLot requires an inefficient lookup
// (a pointer connecting the two is much faster). However,
// there are advantages to referencing things by a unique ID instead of a pointer.
// For example, you can reference things that are not currently in memory
// (maybe they’re in a file, or in a database, and can be loaded on demand).
// Also, pointers can take 4 or 8 bytes -- if space is
// at a premium and the number of unique objects is fairly low,
// referencing them by an 8-bit or 16-bit integer can save lots of memory.
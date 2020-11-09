#include <iostream>

int getNumber()
{
    int num{};

    std::cin >> num;

    return num;
}
 
int main()
{
    std::cout << "Enter an integer: ";
	int smaller{ getNumber() };

    std::cout << "Enter a larger one: ";
	int larger{ getNumber() };

    if (smaller > larger) {
        std::cout << "Swapping values...\n";
        
        int tempo{ smaller };
        smaller = larger;
        larger = tempo;
    } // tempo dies

    std::cout << "Smaller: " << smaller << '\n';
    std::cout << "Larger: " << larger << '\n';
 
	return 0;
} // smaller & larger die
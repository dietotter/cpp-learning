#include <bitset>
#include <iostream>
 
// "rotl" stands for "rotate left"
std::bitset<4> rotl(std::bitset<4> bits)
{
    std::bitset<4> lastBitBitset { bits >> 3 };

    return (bits << 1) | lastBitBitset;
}

int getNumber()
{
    int num{};

    std::cout << "0 to 255 pls: ";
    std::cin >> num;
    std::cout << "You entered: " << num << '\n';

    return num;
}

void convertToBinary(int num)
{
    int bit128{ (num < 128 ? 0 : (num -= 128, 1)) };
    int bit64{ (num < 64 ? 0 : (num -= 64, 1)) };
    int bit32{ (num < 32 ? 0 : (num -= 32, 1)) };
    int bit16{ (num < 16 ? 0 : (num -= 16, 1)) };
    int bit8{ (num < 8 ? 0 : (num -= 8, 1)) };
    int bit4{ (num < 4 ? 0 : (num -= 4, 1)) };
    int bit2{ (num < 2 ? 0 : (num -= 2, 1)) };
    int bit1{ (num < 1 ? 0 : 1) };

    std::cout << "Your number: " << bit128 << bit64 << bit32 << bit16 << bit8 << bit4 << bit2 << bit1;
}
 
int main()
{
	int num{getNumber()};
	convertToBinary(num);
 
	return 0;
}
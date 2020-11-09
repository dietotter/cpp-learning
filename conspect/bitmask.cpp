#include <cstdint>
#include <iostream>

int main()
{
    // C++14
    constexpr std::uint_fast8_t mask0{ 0b0000'0001 }; // represents bit 0
    constexpr std::uint_fast8_t mask1{ 0b0000'0010 }; // represents bit 1
    constexpr std::uint_fast8_t mask2{ 0b0000'0100 }; // represents bit 2 
    constexpr std::uint_fast8_t mask3{ 0b0000'1000 }; // represents bit 3
    constexpr std::uint_fast8_t mask4{ 0b0001'0000 }; // represents bit 4
    constexpr std::uint_fast8_t mask5{ 0b0010'0000 }; // represents bit 5
    constexpr std::uint_fast8_t mask6{ 0b0100'0000 }; // represents bit 6
    constexpr std::uint_fast8_t mask7{ 0b1000'0000 }; // represents bit 7

    // could also be implemented using std::bitset<8>

    std::uint_fast8_t flags{ 0b0000'0101 };

    // test if bit is on:
    std::cout << "Bit 1 is: " << ((flags & mask1) ? "on" : "off") << '\n';
    // to turn bit on:
    flags |= mask1;
    // to turn on multiple bits:
    flags |= (mask4 | mask5);
    // to reset a bit:
    flags &= ~mask1;
    // to flip a bit:
    flags ^= mask1;

    // how masks could be used
    constexpr std::uint_fast8_t isHungry{ 1 << 0 }; // 0000 0001 
    constexpr std::uint_fast8_t isSad{ 1 << 1 }; // 0000 0010
    constexpr std::uint_fast8_t isMad{ 1 << 2 }; // 0000 0100
    constexpr std::uint_fast8_t isHappy{ 1 << 3 }; // 0000 1000
    constexpr std::uint_fast8_t isLaughing{ 1 << 4 }; // 0001 0000
    constexpr std::uint_fast8_t isAsleep{ 1 << 5 }; // 0010 0000
    constexpr std::uint_fast8_t isDead{ 1 << 6 }; // 0100 0000
    constexpr std::uint_fast8_t isCrying{ 1 << 7 }; // 1000 0000

    std::uint_fast8_t me{};
    me |= isSad | isMad; // make myself sad and mad

    std::cout << "Am I sad? " << static_cast<bool>(me & isSad) << '\n';

    return 0;
}
#include <iostream>
#include <string>
#include <string_view>

void useString()
{
    // 4 copies are created

    char text[]{ "hello" }; // 1. initial literal "hello"; 2. text[] copies it for itself
    std::string str{ text }; // 3. copy for std::string str
    std::string more{ str }; // 4. copy for more

    std::cout << text << ' ' << str << ' ' << more << '\n';
}

void useStringView()
{
    std::string_view text{ "hello" }; // view the text "hello", which is stored in the binary
    std::string_view str{ text }; // view of the same "hello"
    std::string_view more{ str }; // view of the same "hello"

    std::cout << text << ' ' << str << ' ' << more << '\n';

    // ===================
    // Functions of std::string_view
    std::string_view str2{ "Trains are fast!" };
    
    std::cout << str2.length() << '\n'; // 16
    std::cout << str2.substr(0, str2.find(' ')) << '\n'; // Trains
    std::cout << (str2 == "Trains are fast!") << '\n'; // 1
 
    // Since C++20
    std::cout << str2.starts_with("Boats") << '\n'; // 0
    std::cout << str2.ends_with("fast!") << '\n'; // 1

    // ===================
    // Because std::string_view doesn’t create a copy of the string,
    // if we change the viewed string, the changes are reflected in the std::string_view.
    char arr[]{ "Gold" };
    std::string_view str{ arr };
 
    // Change 'd' to 'f' in arr
    arr[3] = 'f';
 
    std::cout << str << '\n'; // Golf

    // ===================
    // We can change the visibility of string_view (without changing the underlying string)
    std::string_view str{ "Peach" };
 
    // Ignore the first characters.
    str.remove_prefix(1); // "each"
 
    // Ignore the last 2 characters.
    str.remove_suffix(2); // "ea"
    // once you change the visibility area, you can't go back (though there are tricks)

    // ===================
    // Because std::string view is a relatively recent feature,
    // it isn't implemented as well as it could be:
    std::string s{ "hello" };
    std::string_view v{ "world" };
 
    // Doesn't work
    std::cout << (s + v) << '\n';
    std::cout << (v + s) << '\n';
 
    // Potentially unsafe, or not what we want, because we're treating
    // the std::string_view as a C-style string.
    std::cout << (s + v.data()) << '\n';
    std::cout << (v.data() + s) << '\n';
 
    // Ok, but ugly and wasteful because we have to construct a new std::string.
    std::cout << (s + std::string{ v }) << '\n';
    std::cout << (std::string{ v } + s) << '\n';
    std::cout << (s + static_cast<std::string>(v)) << '\n';
    std::cout << (static_cast<std::string>(v) + s) << '\n';
}

int main()
{
  
 
  return 0;
}
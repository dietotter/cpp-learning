namespace StudentNames
{
    enum StudentNames
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        wendy, // 5
        max_students // 6
    };
}   // we use this instead of enum class,
    // as with enum class we would need to do static_cast<int> when using enum values for array purposes
 
int main()
{
    int testScores[StudentNames::max_students]{}; // allocate 6 integers
    testScores[StudentNames::stan] = 76;
 
    return 0;
}
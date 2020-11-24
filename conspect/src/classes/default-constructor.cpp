class Date
{
private:
    // Note: No initializations at member declarations
    int m_year;
    int m_month;
    int m_day;
 
public:
    // Explicitly defaulted constructor
    Date() = default;
};
 
class Date2
{
private:
    // Note: No initializations at member declarations
    int m_year;
    int m_month;
    int m_day;
 
public:
    // Empty user-provided constructor
    Date2() {};
};
 
int main()
{
    Date today{}; // today is 0, 0, 0
    Date2 tomorrow{}; // tomorrows's members are uninitialized
 
    return 0;
}
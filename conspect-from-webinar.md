- Итераторы ведут себя как поинтеры (?поэтому не обязательно всегда писать класс итератора?)
- Список инициализации инициализируется в том порядке, в котором переменные объявлены в классе:

        class Asd
        {
            int m_kek;
            int m_lol;
        
        public:
            Asd(int kek, int lol)
                : m_lol(lol), m_kek(m_lol + kek)
                // won't work, because m_lol is not initialized yet when m_kek is being initialized
            {
            }

        };

- Rule of five: если один из 5 resource-management functions (copy/move constructors, copy/move assignment operators, destructor) имеет нетривиальную имплементацию, другие тоже должны ее иметь
https://en.cppreference.com/w/cpp/language/rule_of_three
https://www.fluentcpp.com/2019/04/23/the-rule-of-zero-zero-constructor-zero-calorie/
https://cpppatterns.com/patterns/rule-of-five.html
- Github лектора: https://github.com/oyefremov?tab=repositories
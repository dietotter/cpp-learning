#include "MonsterGenerator.h"

#include <cstdlib>

Monster MonsterGenerator::generateMonster()
{
	static constexpr std::array s_names{
		"Boner", "Loner", "Vasya", "Kek", "Lol", "Asd"
	};
	static constexpr std::array s_roars{
		"*rrr*", "*hahaha*", "*rofl*", "*m-m-m*", "*slava Ukraini*", "*heroyam slava*"
	};

	Monster::Type type{ getRandomNumber(0, static_cast<int>(Monster::Type::maxTypes)) };
	auto name{
		s_names[static_cast<std::size_t>(getRandomNumber(0, 5))]
	};
	auto roar{
		s_roars[static_cast<std::size_t>(getRandomNumber(0, 5))]
	};
	int hp{ getRandomNumber(1, 100) };

    return { type, name, roar, hp };
}
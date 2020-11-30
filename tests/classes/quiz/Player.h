#pragma once

#include "Deck.h"

class Player
{
private:
    int m_score{ 0 };

public:
    Player& drawCard(Deck &deck);
    bool isBust();

    int score() const { return m_score; };
};
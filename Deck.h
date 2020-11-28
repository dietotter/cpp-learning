#pragma once

#include "Card.h"

#include <array>

class Deck
{
public:
    using deck_type = std::array<Card, 52>;
    using index_type = deck_type::size_type;

private:
    index_type m_cardIndex{ 0 };
    deck_type m_deck{};

public:
    Deck();

    void print() const;
    void shuffle();
    const Card& dealCard();
};
#include "Deck.h"

#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
#include <cassert>

Deck::Deck()
{
    index_type card{ 0 };
    
    auto suits{ static_cast<index_type>(Card::CardSuit::maxSuits) };
    auto ranks{ static_cast<index_type>(Card::CardRank::maxRanks) };
    
    for (index_type suit{ 0 }; suit < suits; ++suit)
    {
        for (index_type rank{ 0 }; rank < ranks; ++rank)
        {
            m_deck[card].suit(static_cast<Card::CardSuit>(suit));
            m_deck[card].rank(static_cast<Card::CardRank>(rank));
            ++card;
        }
    }
}

void Deck::print() const
{
    for (const auto& card : m_deck)
    {
        card.print();
        std::cout << ' ';
    }
    
    std::cout << '\n';
}

void Deck::shuffle()
{
    static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    
    std::shuffle(m_deck.begin(), m_deck.end(), mt);
    m_cardIndex = 0;
}

const Card& Deck::dealCard()
{
    assert(m_cardIndex < m_deck.size());
    
    return m_deck[m_cardIndex++];
}
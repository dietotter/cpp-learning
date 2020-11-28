#include "Card.h"

#include <iostream>
#include <cassert>

Card::Card(CardRank rank, CardSuit suit): m_rank{ rank }, m_suit{ suit }
{
}

void Card::print() const
{
    switch (m_rank)
    {
    case Card::CardRank::two:
        std::cout << '2';
        break;
    case Card::CardRank::three:
        std::cout << '3';
        break;
    case Card::CardRank::four:
        std::cout << '4';
        break;
    case Card::CardRank::five:
        std::cout << '5';
        break;
    case Card::CardRank::six:
        std::cout << '6';
        break;
    case Card::CardRank::seven:
        std::cout << '7';
        break;
    case Card::CardRank::eight:
        std::cout << '8';
        break;
    case Card::CardRank::nine:
        std::cout << '9';
        break;
    case Card::CardRank::ten:
        std::cout << 'T';
        break;
    case Card::CardRank::jack:
        std::cout << 'J';
        break;
    case Card::CardRank::queen:
        std::cout << 'Q';
        break;
    case Card::CardRank::king:
        std::cout << 'K';
        break;
    case Card::CardRank::ace:
        std::cout << 'A';
        break;
    default:
        std::cout << '?';
        break;
    }
 
    switch (m_suit)
    {
    case Card::CardSuit::clubs:
        std::cout << 'C';
        break;
    case Card::CardSuit::diamonds:
        std::cout << 'D';
        break;
    case Card::CardSuit::hearts:
        std::cout << 'H';
        break;
    case Card::CardSuit::spades:
        std::cout << 'S';
        break;
    default:
        std::cout << '?';
        break;
    }
}

int Card::getValue() const
{
    if (m_rank <= Card::CardRank::ten)
    {
        return (static_cast<int>(m_rank) + 2);
    }
    
    switch (m_rank)
    {
    case Card::CardRank::jack:
    case Card::CardRank::queen:
    case Card::CardRank::king:
        return 10;
    case Card::CardRank::ace:
        return 11;
    default:
        assert(false && "should never happen");
        return 0;
    }
}
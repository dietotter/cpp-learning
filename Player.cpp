#include "Player.h"
#include "config.h"

Player& Player::drawCard(Deck &deck)
{
    m_score += deck.dealCard().getValue();

    return *this;
}

bool Player::isBust()
{
    return m_score > config::maximumScore;
}
#pragma once

#include "quest6.h"

namespace quest7 {

    enum class BlackjackWinner
    {
        player, dealer, draw
    };

    inline constexpr int blackjackMaxScore{ 21 };
    inline constexpr int dealerMinScore{ 17 };
    inline constexpr int aceMaxValue{ 11 };
    inline constexpr int aceMinMaxDifference{ 10 };

    BlackjackWinner playBlackjack(const quest6::card_deck_t &deck);

}
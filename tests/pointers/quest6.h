#pragma once

#include <array>

namespace quest6 {

    enum class CardRank
    {
        two,
        three,
        four,
        five,
        six, 
        seven,
        eight,
        nine,
        ten,
        jack,
        queen,
        king,
        ace,

        maxRanks
    };

    enum class CardSuit
    {
        clubs,
        diamonds,
        hearts,
        spades,

        maxSuits
    };

    struct Card
    {
        CardRank rank{};
        CardSuit suit{};
    };

    inline constexpr int deckSize{ 52 };

    using card_deck_t = std::array<Card, deckSize>;
    using deck_index_t = card_deck_t::size_type;

    void printCard(const Card &card);
    int getCardValue(const Card &card);
    card_deck_t getShuffledDeck();

}
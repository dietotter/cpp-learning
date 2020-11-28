#pragma once

class Card
{
public:
    enum class CardSuit
    {
        clubs,
        diamonds,
        hearts,
        spades,

        maxSuits
    };

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

private:
    CardRank m_rank{};
    CardSuit m_suit{};

public:
    Card(CardRank rank = CardRank::two, CardSuit suit = CardSuit::clubs);

    void print() const;
    int getValue() const;
    CardRank rank() const { return m_rank; }
    CardSuit suit() const { return m_suit; }
    void rank(CardRank rank) { m_rank = rank; }
    void suit(CardSuit suit) { m_suit = suit; }
};
#include "quest6.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <random>

namespace quest6 {

    void printCard(const Card &card)
    {
        std::string cardCode{};

        switch(card.rank)
        {
            case CardRank::two:
                cardCode += '2';
                break;
            case CardRank::three:
                cardCode += '3';
                break;
            case CardRank::four:
                cardCode += '4';
                break;
            case CardRank::five:
                cardCode += '5';
                break;
            case CardRank::six:
                cardCode += '6';
                break;
            case CardRank::seven:
                cardCode += '7';
                break;
            case CardRank::eight:
                cardCode += '8';
                break;
            case CardRank::nine:
                cardCode += '9';
                break;
            case CardRank::ten:
                cardCode += 'T';
                break;
            case CardRank::jack:
                cardCode += 'J';
                break;
            case CardRank::queen:
                cardCode += 'Q';
                break;
            case CardRank::king:
                cardCode += 'K';
                break;
            case CardRank::ace:
                cardCode += 'A';
                break;
            default:
                std::cout << "?";
                break;
        }

        switch (card.suit)
        {
            case CardSuit::clubs:
                cardCode += 'C';
                break;
            case CardSuit::diamonds:
                cardCode += 'D';
                break;
            case CardSuit::hearts:
                cardCode += 'H';
                break;
            case CardSuit::spades:
                cardCode += 'S';
                break;
            default:
                std::cout << "?";
                break;
        }

        std::cout << cardCode;
    }

    card_deck_t createDeck()
    {
        card_deck_t deck{};

        deck_index_t cardIndex{ 0 };

        for (int rank{ 0 }; rank < static_cast<int>(CardRank::maxRanks); ++rank)
        {
            for (int suit{ 0 }; suit < static_cast<int>(CardSuit::maxSuits); ++suit)
            {
                deck[cardIndex].rank = static_cast<CardRank>(rank);
                deck[cardIndex].suit = static_cast<CardSuit>(suit);
                ++cardIndex;
            }
        }

        return deck;
    }

    void printDeck(const card_deck_t &deck)
    {
        for(const auto &card : deck)
        {
            printCard(card);
            std::cout << ' ';
        }

        std::cout << '\n';
    }

    void shuffleDeck(card_deck_t &deck)
    {
        static std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

        std::shuffle(deck.begin(), deck.end(), mersenne);
    }

    int getCardValue(const Card &card)
    {
        if (card.rank <= CardRank::ten)
        {
            return static_cast<int>(card.rank) + 2;
        }

        switch(card.rank)
        {
            case CardRank::ten:
            case CardRank::jack:
            case CardRank::queen:
            case CardRank::king:
                return 10;
            case CardRank::ace:
                return 11;
            default:
                return 0;
        }
    }

    card_deck_t getShuffledDeck()
    {
        card_deck_t deck{ createDeck() };

        shuffleDeck(deck);

        printDeck(deck);

        return deck;
    }

}
#include "quest6.h"
#include "quest7.h"

#include <iostream>
#include <vector>

namespace quest7 {

    using game_hand_t = std::vector<quest6::Card>;

    quest6::Card getNextCard(const quest6::card_deck_t &deck, quest6::deck_index_t &index)
    {
        return deck[index++];
    }

    void printScore(int score)
    {
        std::cout << "\nYour score: " << score << '\n';
    }

    void printDealersScore(int score)
    {
        std::cout << "\nDealer's score: " << score << '\n';
    }

    bool askIfHits()
    {
        char usersAnswer{};

        while (true)
        {
            std::cout << "Hit? (y\\n) ";
            std::cin >> usersAnswer;

            switch (usersAnswer)
            {
                case 'y':
                    return true;
                case 'n':
                    return false;
                default:
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Incorrect response.\n";
            }
        }
    }

    void recalculateScore(int &score, int valueToAdd, int &acesAsElevens)
    {
        // If the next card value makes the score exceed the maximum blackjack score,
        // we check if there are aces in the calculated score, and change one (or more) of their values
        // from ace maximum (usually 11) to ace minimum (usually 1)

        score += valueToAdd;

        if (valueToAdd == aceMaxValue)
        {
            ++acesAsElevens;
        }

        while (score > blackjackMaxScore && acesAsElevens > 0)
        {
            score -= aceMinMaxDifference;
            --acesAsElevens;
        }
    }

    // This should be decomposed into smaller functions (I was just lazy)
    BlackjackWinner playBlackjack(const quest6::card_deck_t &deck)
    {
        // Initialize deck index and dealer's and player's hands
        quest6::deck_index_t index{ 0 };
        game_hand_t dealersHand{ getNextCard(deck, index) };
        game_hand_t playersHand{ getNextCard(deck, index), getNextCard(deck, index) };

        // In these variables we'll keep track of how much aces that player and dealer have hit count as 11 in their scores
        int playersAcesAsElevens{ 0 };
        int dealersAcesAsElevens{ 0 };

        // start keeping track of dealer's score
        int dealersScore{ 0 };
        recalculateScore(dealersScore, quest6::getCardValue(dealersHand[0]), dealersAcesAsElevens);

        // Print what dealer's starting hand looks like
        std::cout << "Dealer's starting hand is ";
        quest6::printCard(dealersHand[0]);
        printDealersScore(dealersScore);

        // start keeping track of player's score
        int playersScore{ 0 };
        recalculateScore(playersScore, quest6::getCardValue(playersHand[0]), playersAcesAsElevens);
        recalculateScore(playersScore, quest6::getCardValue(playersHand[1]), playersAcesAsElevens);

        // Print what user's starting hand looks like
        std::cout << "Your starting hand is ";
        quest6::printCard(playersHand[0]);
        std::cout << ' ';
        quest6::printCard(playersHand[1]);
        printScore(playersScore);
        
        // Player starts playing the game
        quest6::deck_index_t playersIndex{ 1 };
        bool doesPlayerHit{ askIfHits() };

        // Ask for hits until the user says "no"
        while (doesPlayerHit)
        {
            // Add next card to player's hand and recalculate user's total
            playersHand.push_back(getNextCard(deck, index));
            recalculateScore(playersScore, quest6::getCardValue(playersHand[++playersIndex]), playersAcesAsElevens);
            
            // Print what user has hit
            std::cout << "You hit ";
            quest6::printCard(playersHand[playersIndex]);
            printScore(playersScore);

            if (playersScore > blackjackMaxScore)
            {
                std::cout << "You lost (your score is > 21)\n";
                return BlackjackWinner::dealer;
            }

            doesPlayerHit = askIfHits();
        }

        // Dealer starts playing
        quest6::deck_index_t dealersIndex{ 0 };

        // Takes hits until his score is dealer's minimal score (usually 17)
        while (dealersScore < dealerMinScore)
        {
            // Add next card to dealer's hand and recalculate dealer's total
            dealersHand.push_back(getNextCard(deck, index));
            recalculateScore(dealersScore, quest6::getCardValue(dealersHand[++dealersIndex]), dealersAcesAsElevens);

            // Print what dealer has hit
            std::cout << "Dealer hits ";
            quest6::printCard(dealersHand[dealersIndex]);
            printDealersScore(dealersScore);
            
            if (dealersScore > blackjackMaxScore)
            {
                std::cout << "You won (dealer's score is > 21)\n";
                return BlackjackWinner::player;
            }
        }

        std::cout << "Dealer's score is " << dealersScore << '\n';

        if (dealersScore > playersScore)
        {
            std::cout << "You lost. Dealer's score is larger than yours\n";
            return BlackjackWinner::dealer;
        }
        else if (dealersScore == playersScore)
        {
            std::cout << "Draw! Your score is equal to dealer's\n";
            return BlackjackWinner::draw;
        }

        std::cout << "You won! Your score is larger than dealer's\n";
        return BlackjackWinner::player;
    }

}
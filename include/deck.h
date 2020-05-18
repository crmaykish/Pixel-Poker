#ifndef DECK_H
#define DECK_H

#include <vector>
#include <set>
#include "card.h"

// A collection of cards
class Deck
{
    private:
        std::vector<Card> cards;
        void AddNewCardAt(Card card, int index);
    public:
        Deck();
        ~Deck();

        // Statuses
        void Shuffle();
        bool IsEmpty();
        int Size();
        Card& CardAt(int index);

        // Deck manipulation
        void AddNewCard(Card card);
        void MoveTopCards(Deck& destinationDeck, int count = 1);
        void MoveCardAt(Deck& destinationDeck, int sourceIndex);
        void MoveTopCardTo(Deck& destinationDeck, int destinationIndex);

        // Deck conditions
        std::set<int> IsJacksOrBetter();
        std::set<int> IsTwoPair();
        std::set<int> IsThreeOfAKind();
        std::set<int> IsStraight();
        std::set<int> IsFlush();
        std::set<int> IsFullHouse();
        std::set<int> IsFourOfAKind();
        std::set<int> IsStraightFlush();
        std::set<int> IsRoyalFlush();
};


#endif
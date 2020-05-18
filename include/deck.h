#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"

// A collection of cards
class Deck
{
    private:
    protected:
        std::vector<PlayingCard> cards;
        void AddCardAt(PlayingCard card, int index);
    public:
        // Statuses
        void Shuffle();
        bool IsEmpty();
        int Size();
        PlayingCard& CardAt(int index);

        // Deck manipulation
        void AddCard(PlayingCard card);
        void MoveTopCards(Deck& destinationDeck, int count = 1);
        void MoveCardAt(Deck& destinationDeck, int sourceIndex);
        void MoveTopCardTo(Deck& destinationDeck, int destinationIndex);
};


#endif
#ifndef DECK_H
#define DECK_H

#include <vector>
#include "pp_card.h"

// A collection of cards
class Deck
{
    private:
    protected:
        std::vector<PlayingCard> cards;
        void AddCardAt(PlayingCard card, int index);
    public:
        Deck(bool standardDeck = false, bool shuffled = false);
        void Shuffle();
        void Clear();
        bool IsEmpty();
        int Size();
        PlayingCard& CardAt(int index);
        void AddCard(PlayingCard card);
        void MoveTopCards(Deck& destinationDeck, int count = 1);
        void MoveCardAt(Deck& destinationDeck, int sourceIndex);
        void MoveTopCardTo(Deck& destinationDeck, int destinationIndex);
};


#endif
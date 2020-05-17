#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <map>
#include <vector>

enum CARD_SUIT {HEART, DIAMOND, CLUB, SPADE};
enum CARD_VALUE {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};

// Logical representation of a playing card
class Card
{
    private:
        CARD_SUIT Suit;
        CARD_VALUE Value;
        static std::map<CARD_SUIT, std::string> SuitMap;
        static std::map<CARD_VALUE, std::string> ValueMap;
        
    public:
        Card(CARD_SUIT suit, CARD_VALUE value);
        ~Card();
        
        CARD_SUIT GetSuit();
        CARD_VALUE GetValue();
        
        std::string HumanReadable();
};

// A collection of cards
class Deck
{
    private:
        std::vector<Card> cards;
        void AddNewCardAt(Card card, int index);
    public:
        Deck();
        ~Deck();
        void Shuffle();
        bool IsEmpty();
        int Size();

        Card& CardAt(int index);

        void AddNewCard(Card card);
        void MoveTopCards(Deck& destinationDeck, int count = 1);
        void MoveCardAt(Deck& destinationDeck, int sourceIndex);
        void MoveTopCardTo(Deck& destinationDeck, int destinationIndex);
};

#endif
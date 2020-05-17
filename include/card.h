#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <map>
#include <vector>
#include <set>

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

        bool operator<(const Card &c)
        {
            return Value < c.Value;
        }
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
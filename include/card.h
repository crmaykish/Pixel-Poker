#ifndef CARD_H
#define CARD_H

// #include <iostream>
// #include <vector>
#include <map>

enum CARD_SUIT {HEART, DIAMOND, CLUB, SPADE};
enum CARD_VALUE {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};

// Logical representation of a playing card
class Card
{
    private:
        CARD_SUIT Suit;
        CARD_VALUE Value;
        
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

#endif
#include <string>
#include <algorithm>
#include "card.h"

std::map<CARD_SUIT, std::string> Card::SuitMap;
std::map<CARD_VALUE, std::string> Card::ValueMap;

std::string Card::HumanReadable()
{
    return ValueMap.at(Value) + " of " + SuitMap.at(Suit);
}

Card::Card(CARD_SUIT suit, CARD_VALUE value)
{
    Suit = suit;
    Value = value;

    if (SuitMap.size() == 0)
    {
        SuitMap.insert({HEART, "Hearts"});
        SuitMap.insert({DIAMOND, "Diamonds"});
        SuitMap.insert({CLUB, "Clubs"});
        SuitMap.insert({SPADE, "Spades"});
    }

    if (ValueMap.size() == 0)
    {
        ValueMap.insert({TWO, "Two"});
        ValueMap.insert({THREE, "Three"});
        ValueMap.insert({FOUR, "Four"});
        ValueMap.insert({FIVE, "Five"});
        ValueMap.insert({SIX, "Six"});
        ValueMap.insert({SEVEN, "Seven"});
        ValueMap.insert({EIGHT, "Eight"});
        ValueMap.insert({NINE, "Nine"});
        ValueMap.insert({TEN, "Ten"});
        ValueMap.insert({JACK, "Jack"});
        ValueMap.insert({QUEEN, "Queen"});
        ValueMap.insert({KING, "King"});
        ValueMap.insert({ACE, "Ace"});
    }
}

Card::~Card()
{

}

CARD_SUIT Card::GetSuit()
{
    return Suit;
}

CARD_VALUE Card::GetValue()
{
    return Value;
}

Deck::Deck()
{

}

Deck::~Deck()
{

}

void Deck::Shuffle()
{
    std::random_shuffle(cards.begin(), cards.end());
}

bool Deck::IsEmpty()
{
    return cards.empty();
}

int Deck::Size()
{
    return cards.size();
}

void Deck::AddCard(Card card)
{
    cards.push_back(card);
}

void Deck::DrawCard(Deck& targetDeck, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (!IsEmpty())
        {
            targetDeck.AddCard(cards.back());
            cards.pop_back();
        }
    }
}

Card& Deck::CardAt(int index)
{
    return cards.at(index);
}
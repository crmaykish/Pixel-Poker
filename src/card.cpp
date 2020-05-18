#include <string>
#include <algorithm>
#include "card.h"

std::map<CARD_SUIT, std::string> SuitMap;
std::map<CARD_VALUE, std::string> ValueMap;

Card::Card(CARD_SUIT suit, CARD_VALUE value)
{
    Suit = suit;
    Value = value;
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

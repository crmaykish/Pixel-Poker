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

void Deck::AddNewCard(Card card)
{
    cards.push_back(card);
}

void Deck::AddNewCardAt(Card card, int index)
{
    cards.insert(cards.begin() + index, card);
}

void Deck::MoveTopCards(Deck& destinationDeck, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (!IsEmpty())
        {
            destinationDeck.AddNewCard(cards.back());
            cards.pop_back();
        }
    }
}

void Deck::MoveCardAt(Deck& targetDeck, int index)
{
    targetDeck.AddNewCard(cards.at(index));
    cards.erase(cards.begin() + index);
}

void Deck::MoveTopCardTo(Deck& destinationDeck, int destinationIndex)
{
    destinationDeck.AddNewCardAt(cards.back(), destinationIndex);
    cards.pop_back();
}

Card& Deck::CardAt(int index)
{
    return cards.at(index);
}

std::vector<int> Deck::IsJacksOrBetter()
{
    std::vector<int> result;

    for (int i = 0; i < cards.size(); i++)
    {
        if (CardAt(i).GetValue() >= JACK){
            for (int j = i + 1; j < cards.size(); j++)
            {
                if (CardAt(i).GetValue() == CardAt(j).GetValue())
                {
                    result.push_back(i);
                    result.push_back(j);
                }
            }
        }
    }

    return result;
}

std::vector<int> Deck::IsTwoPair()
{
    std::vector<int> result;

    for (int i = 0; i < cards.size(); i++)
    {
        for (int j = i + 1; j < cards.size(); j++)
        {
            if (CardAt(i).GetValue() == CardAt(j).GetValue())
            {
                // TODO: broken - this will add duplicates and mess up the count
                result.push_back(i);
                result.push_back(j);
            }
        }
    }

    if (!result.size() == 4)
    {
        result.clear();
    }

    return result;

}

std::vector<int> Deck::IsThreeOfAKind()
{
    std::vector<int> result;


    return result;
}

std::vector<int> Deck::IsFourOfAKind()
{
    std::vector<int> result;


    return result;
}
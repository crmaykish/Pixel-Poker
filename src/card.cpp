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

std::set<int> Deck::IsJacksOrBetter()
{
    std::set<int> result;

    for (int i = 0; i < cards.size(); i++)
    {
        if (CardAt(i).GetValue() >= JACK){
            for (int j = i + 1; j < cards.size(); j++)
            {
                if (CardAt(i).GetValue() == CardAt(j).GetValue())
                {
                    result.insert(i);
                    result.insert(j);
                }
            }
        }
    }

    return result;
}

std::set<int> Deck::IsTwoPair()
{
    std::set<int> result;

    for (int i = 0; i < cards.size(); i++)
    {
        for (int j = i + 1; j < cards.size(); j++)
        {
            if (CardAt(i).GetValue() == CardAt(j).GetValue())
            {
                result.insert(i);
                result.insert(j);
            }
        }
    }

    if (result.size() < 4)
    {
        result.clear();
    }

    return result;
}

std::set<int> Deck::IsThreeOfAKind()
{
    std::set<int> result;

    for (int i = 0; i < cards.size(); i++)
    {
        for (int j = i + 1; j < cards.size(); j++)
        {
            if (cards.at(i).GetValue() == cards.at(j).GetValue())
            {
                // Add both indexes to the set
                result.insert(i);
                result.insert(j);
            }
        }
        
        if (result.size() < 3)
        {
            result.clear();
        }
    }

    return result;
}

std::set<int> Deck::IsStraight()
{
    bool straight = true;

    // copy the hand and sort it
    std::vector<Card> handCopy = std::vector<Card>(cards);
    std::sort(handCopy.begin(), handCopy.end());

    for (int i = 0; i < handCopy.size() - 1; i++)
    {
        if ((handCopy.at(i + 1).GetValue() - handCopy.at(i).GetValue()) != 1)
        {
            // not a straight
            straight = false;
            break;
        }
    }

    std::set<int> result;

    if (straight)
    {
        result.insert(0);
        result.insert(1);
        result.insert(2);
        result.insert(3);
        result.insert(4);
    }

    return result;
}

std::set<int> Deck::IsFlush()
{
    bool flush = true;

    for (int i = 1; i < cards.size(); i++)
    {
        if (cards.at(i).GetSuit() != cards.at(0).GetSuit())
        {
            flush = false;
            break;
        }
    }

    std::set<int> result;

    if (flush)
    {
        result.insert(0);
        result.insert(1);
        result.insert(2);
        result.insert(3);
        result.insert(4);
    }

    return result;
}

// TODO: This is disgusting
std::set<int> Deck::IsFullHouse()
{
    // TODO: if the hand is 3 of a kind and the remainder is a pair


    // TODO: this doesn't work

    std::set<int> result = IsThreeOfAKind();

    if (result.size() > 0)
    {
        // it's at least three of a kind

        // is there a pair with a different value?
        int firstIndex = *result.begin();

        CARD_SUIT threesSuit = cards.at(firstIndex).GetSuit();

        bool pair = false;

        for (int i = 0; i < cards.size(); i++)
        {
            if (CardAt(i).GetSuit() != threesSuit){
                for (int j = i + 1; j < cards.size(); j++)
                {
                    if (CardAt(i).GetValue() == CardAt(j).GetValue())
                    {
                        pair = true;
                    }
                }
            }
        }

        if (pair)
        {
            result.insert(0);
            result.insert(1);
            result.insert(2);
            result.insert(3);
            result.insert(4);
        }
    }
    else
    {
        result.clear();
    }
    
    return result;
}

std::set<int> Deck::IsFourOfAKind()
{
    std::set<int> result;

    for (int i = 0; i < cards.size(); i++)
    {
        for (int j = i + 1; j < cards.size(); j++)
        {
            if (cards.at(i).GetValue() == cards.at(j).GetValue())
            {
                // Add both indexes to the set
                result.insert(i);
                result.insert(j);
            }
        }
        
        if (result.size() < 4)
        {
            result.clear();
        }
    }

    return result;
}

std::set<int> Deck::IsStraightFlush()
{
    std::set<int> result;

    std::set<int> straightResult = IsStraight();
    std::set<int> flushResult = IsFlush();

    if(straightResult.size() > 0 && flushResult.size() > 0)
    {
        return straightResult;
    }

    return result;
}

std::set<int> Deck::IsRoyalFlush()
{
    std::set<int> result;

    std::set<int> straightFlushResult = IsStraightFlush();

    if (straightFlushResult.size() > 0)
    {
        std::vector<Card> handCopy = std::vector<Card>(cards);
        std::sort(handCopy.begin(), handCopy.end());

        if (handCopy.at(0).GetValue() == TEN)
        {
            return straightFlushResult;
        }
    }

    return result;
}
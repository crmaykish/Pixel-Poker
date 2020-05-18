#include <set>
#include <algorithm>
#include "poker_hand.h"

std::set<int> PokerHand::IsJacksOrBetter()
{
    std::set<int> result;

    for (int i = 0; i < cards.size(); i++)
    {
        if (CardAt(i).Value >= JACK){
            for (int j = i + 1; j < cards.size(); j++)
            {
                if (CardAt(i).Value == CardAt(j).Value)
                {
                    result.insert(i);
                    result.insert(j);
                }
            }
        }
    }

    return result;
}

std::set<int> PokerHand::IsTwoPair()
{
    std::set<int> result;

    for (int i = 0; i < cards.size(); i++)
    {
        for (int j = i + 1; j < cards.size(); j++)
        {
            if (CardAt(i).Value == CardAt(j).Value)
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

std::set<int> PokerHand::IsThreeOfAKind()
{
    std::set<int> result;

    for (int i = 0; i < cards.size(); i++)
    {
        for (int j = i + 1; j < cards.size(); j++)
        {
            if (cards.at(i).Value == cards.at(j).Value)
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

std::set<int> PokerHand::IsStraight()
{
    bool straight = true;

    // copy the hand and sort it
    std::vector<PlayingCard> handCopy = std::vector<PlayingCard>(cards);
    std::sort(handCopy.begin(), handCopy.end());

    for (int i = 0; i < handCopy.size() - 1; i++)
    {
        if ((handCopy.at(i + 1).Value - handCopy.at(i).Value) != 1)
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

std::set<int> PokerHand::IsFlush()
{
    bool flush = true;

    for (int i = 1; i < cards.size(); i++)
    {
        if (cards.at(i).Suit != cards.at(0).Suit)
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
std::set<int> PokerHand::IsFullHouse()
{
    // TODO: if the hand is 3 of a kind and the remainder is a pair


    // TODO: this doesn't work

    std::set<int> result = IsThreeOfAKind();

    if (result.size() > 0)
    {
        // it's at least three of a kind

        // is there a pair with a different value?
        int firstIndex = *result.begin();

        PlayingCardValue threesValue = cards.at(firstIndex).Value;

        bool pair = false;

        for (int i = 0; i < cards.size(); i++)
        {
            if (CardAt(i).Value != threesValue){
                for (int j = i + 1; j < cards.size(); j++)
                {
                    if (CardAt(i).Value == CardAt(j).Value)
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
        else 
        {
            result.clear();
        }
    }
    else
    {
        result.clear();
    }
    
    return result;
}

std::set<int> PokerHand::IsFourOfAKind()
{
    std::set<int> result;

    for (int i = 0; i < cards.size(); i++)
    {
        for (int j = i + 1; j < cards.size(); j++)
        {
            if (cards.at(i).Value == cards.at(j).Value)
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

std::set<int> PokerHand::IsStraightFlush()
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

std::set<int> PokerHand::IsRoyalFlush()
{
    std::set<int> result;

    std::set<int> straightFlushResult = IsStraightFlush();

    if (straightFlushResult.size() > 0)
    {
        std::vector<PlayingCard> handCopy = std::vector<PlayingCard>(cards);
        std::sort(handCopy.begin(), handCopy.end());

        if (handCopy.at(0).Value == TEN)
        {
            return straightFlushResult;
        }
    }

    return result;
}
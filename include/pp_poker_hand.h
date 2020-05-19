#ifndef PP_POKER_HAND_H
#define PP_POKER_HAND_H

#include <set>
#include "pp_deck.h"

class PokerHand : public Deck
{
    private:
    public:
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
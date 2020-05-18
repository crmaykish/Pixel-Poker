#include "gtest/gtest.h"
#include "poker_hand.h"

TEST(PokerHandTest, FullHousePassTest)
{
    PokerHand d = PokerHand();

    d.AddCard({HEART, TWO});
    d.AddCard({DIAMOND, TWO});
    d.AddCard({SPADE, TWO});
    d.AddCard({CLUB, THREE});
    d.AddCard({DIAMOND, THREE});

    EXPECT_EQ(5, d.IsFullHouse().size());
}

TEST(PokerHandTest, FullHouseFailTest)
{
    PokerHand d = PokerHand();

    d.AddCard({HEART, TWO});
    d.AddCard({DIAMOND, TWO});
    d.AddCard({SPADE, TWO});
    d.AddCard({CLUB, THREE});
    d.AddCard({DIAMOND, FOUR});

    EXPECT_EQ(0, d.IsFullHouse().size());
}
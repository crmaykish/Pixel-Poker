#include "gtest/gtest.h"
#include "card.h"

TEST(CardTest, ConstructorTest)
{
    Card c = Card(HEART, QUEEN);

    EXPECT_EQ (HEART, c.GetSuit());
    EXPECT_EQ (QUEEN, c.GetValue());
}

#include "gtest/gtest.h"
#include "deck.h"

TEST(DeckTest, FullHousePassTest)
{
    Deck d = Deck();

    d.AddNewCard(Card(HEART, TWO));
    d.AddNewCard(Card(DIAMOND, TWO));
    d.AddNewCard(Card(SPADE, TWO));
    d.AddNewCard(Card(CLUB, THREE));
    d.AddNewCard(Card(DIAMOND, THREE));

    EXPECT_EQ(5, d.IsFullHouse().size());
}

TEST(DeckTest, FullHouseFailTest)
{
    Deck d = Deck();

    d.AddNewCard(Card(HEART, TWO));
    d.AddNewCard(Card(DIAMOND, TWO));
    d.AddNewCard(Card(SPADE, TWO));
    d.AddNewCard(Card(CLUB, THREE));
    d.AddNewCard(Card(DIAMOND, FOUR));

    EXPECT_EQ(0, d.IsFullHouse().size());
}
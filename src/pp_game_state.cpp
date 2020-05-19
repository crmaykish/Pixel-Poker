#include "pp_game_state.h"

void GameState::Init()
{
    srand((unsigned int)time(0));
}

void GameState::Update()
{
}

void GameState::Destroy()
{
}

void GameState::CheckWinnings()
{
    const int LOSE = 0;
    const int JACKS_OR_BETTER = 1;
    const int TWO_PAIR = 2;
    const int THREE_OF_A_KIND = 3;
    const int STRAIGHT = 4;
    const int FLUSH = 6;
    const int FULL_HOUSE = 9;
    const int FOUR_OF_A_KIND = 25;
    const int STRAIGHT_FLUSH = 50;
    const int ROYAL_FLUSH = 250;

    // Royal Flush
    State.WinningCards = State.PlayerHand.IsRoyalFlush();

    if (State.WinningCards.size() > 0)
    {
    }

    // Straight Flush
    State.WinningCards = State.PlayerHand.IsStraightFlush();

    if (State.WinningCards.size() > 0)
    {
    }

    // Four of a Kind
    State.WinningCards = State.PlayerHand.IsFourOfAKind();

    if (State.WinningCards.size() > 0)
    {
    }

    // Full House
    State.WinningCards = State.PlayerHand.IsFullHouse();

    if (State.WinningCards.size() > 0)
    {
    }

    // Flush
    State.WinningCards = State.PlayerHand.IsFlush();

    if (State.WinningCards.size() > 0)
    {
    }

    // Straight
    State.WinningCards = State.PlayerHand.IsStraight();

    if (State.WinningCards.size() > 0)
    {
    }

    // Three of a Kind
    State.WinningCards = State.PlayerHand.IsThreeOfAKind();

    if (State.WinningCards.size() > 0)
    {
    }

    // Two Pair
    State.WinningCards = State.PlayerHand.IsTwoPair();

    if (State.WinningCards.size() > 0)
    {
    }

    // Jacks or Better
    State.WinningCards = State.PlayerHand.IsJacksOrBetter();

    if (State.WinningCards.size() > 0)
    {
    }
}
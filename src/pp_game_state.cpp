#include "pp_game_state.h"

void GameState::Init()
{
    srand((unsigned int)time(0));
}

// PRINCIPLE IDEA: UI elements update themselves and the game state updates itself
// Everything should be communicated through setting and handling flags

void GameState::Update()
{
    switch (PokerState)
    {
    case POKER_INIT:
        StateHandlerInit();
        break;
    case POKER_WAIT_FOR_BET:
        StateHandlerWaitForBet();
        break;
    case POKER_PLACE_BET:
        StateHandlerPlaceBet();
        break;
    case POKER_SELECT_CARDS:
        StateHandlerSelectCards();
        break;
    case POKER_DEAL:
        StateHandlerDeal();
        break;
    case POKER_GAME_OVER:
        StateHandlerGameOver();
        break;
    default:
        break;
    }
}

void GameState::Destroy()
{
}

void GameState::StateHandlerInit()
{
    // Reset cards and decks
    SourceDeck = Deck(true, true);
    PlayerHand.Clear();
    PlayerDiscard.Clear();

    ClearCardFlags();

    PokerState = POKER_WAIT_FOR_BET;
}

void GameState::StateHandlerWaitForBet()
{
    if (BetButtonPressed)
    {
        BetButtonPressed = false;
        PokerState = POKER_PLACE_BET;
    }
}

void GameState::StateHandlerPlaceBet()
{
    LastBet = 10;

    PlayerCoins -= LastBet;

    // Deal cards to the player
    SourceDeck.MoveTopCards(PlayerHand, PLAYER_HAND_SIZE);

    PokerState = POKER_SELECT_CARDS;
}

void GameState::StateHandlerSelectCards()
{
    // When a card is clicked, toggle its selected status
    for (int i = 0; i < PLAYER_HAND_SIZE; i++)
    {
        if (CardFlags[i].Clicked)
        {
            // toggle selected
            CardFlags[i].Selected = !CardFlags[i].Selected;

            CardFlags[i].Clicked = false;
        }
    }

    // Wait for the player to select cards to hold
    if (DealButtonPressed)
    {
        DealButtonPressed = false;
        PokerState = POKER_DEAL;
    }
}

void GameState::StateHandlerDeal()
{
    ClearCardFlags();

    // Discard non-held cards

    // Replace any discards with draws from the deck

    // Check the final hand and award winnings
    CheckWinnings();

    PokerState = POKER_GAME_OVER;
}

void GameState::StateHandlerGameOver()
{
    // Wait for player to start another round
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
    std::set WinningCards = PlayerHand.IsRoyalFlush();

    if (WinningCards.size() > 0)
    {
    }

    // Straight Flush
    WinningCards = PlayerHand.IsStraightFlush();

    if (WinningCards.size() > 0)
    {
    }

    // Four of a Kind
    WinningCards = PlayerHand.IsFourOfAKind();

    if (WinningCards.size() > 0)
    {
    }

    // Full House
    WinningCards = PlayerHand.IsFullHouse();

    if (WinningCards.size() > 0)
    {
    }

    // Flush
    WinningCards = PlayerHand.IsFlush();

    if (WinningCards.size() > 0)
    {
    }

    // Straight
    WinningCards = PlayerHand.IsStraight();

    if (WinningCards.size() > 0)
    {
    }

    // Three of a Kind
    WinningCards = PlayerHand.IsThreeOfAKind();

    if (WinningCards.size() > 0)
    {
    }

    // Two Pair
    WinningCards = PlayerHand.IsTwoPair();

    if (WinningCards.size() > 0)
    {
    }

    // Jacks or Better
    WinningCards = PlayerHand.IsJacksOrBetter();

    if (WinningCards.size() > 0)
    {
    }
}

void GameState::ClearCardFlags()
{
    for (int i = 0; i < PLAYER_HAND_SIZE; i++)
    {
        CardFlags[i].Clicked = false;
        CardFlags[i].Selected = false;
        CardFlags[i].Winning = false;
    }
}
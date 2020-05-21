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

    // Reset bet and win flags
    PlayerBet = BET_NONE;
    ActualBet = 0;
    Win = LOSE;
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
    if (PlayerCoins >= PlayerBet)
    {
        ActualBet = PlayerBet;
    } else {
        ActualBet = PlayerCoins;
    }

    PlayerCoins -= ActualBet;

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
    for (int i = 0; i < PLAYER_HAND_SIZE; i++)
    {
        if (!CardFlags[i].Selected)
        {
            // Replace any non-selected cards with cards from the draw pile
            PlayerHand.MoveCardAt(PlayerDiscard, i);
            SourceDeck.MoveTopCardTo(PlayerHand, i);
        }
    }

    ClearCardFlags();

    // Check the final hand and award winnings
    Win = CheckWinnings();
    PlayerCoins += (ActualBet * Win);

    for (auto w : WinningCards)
    {
        CardFlags[w].Winning = true;
    }

    PokerState = POKER_GAME_OVER;
}

void GameState::StateHandlerGameOver()
{
    // Wait for player to start another round
    if (DealButtonPressed)
    {
        ClearCardFlags();

        DealButtonPressed = false;
        PokerState = POKER_INIT;
    }
}

WinType GameState::CheckWinnings()
{
    // Royal Flush
    WinningCards = PlayerHand.IsRoyalFlush();

    if (WinningCards.size() > 0)
    {
        return ROYAL_FLUSH;
    }

    // Straight Flush
    WinningCards = PlayerHand.IsStraightFlush();

    if (WinningCards.size() > 0)
    {
        return STRAIGHT_FLUSH;
    }

    // Four of a Kind
    WinningCards = PlayerHand.IsFourOfAKind();

    if (WinningCards.size() > 0)
    {
        return FOUR_OF_A_KIND;
    }

    // Full House
    WinningCards = PlayerHand.IsFullHouse();

    if (WinningCards.size() > 0)
    {
        return FULL_HOUSE;
    }

    // Flush
    WinningCards = PlayerHand.IsFlush();

    if (WinningCards.size() > 0)
    {
        return FLUSH;
    }

    // Straight
    WinningCards = PlayerHand.IsStraight();

    if (WinningCards.size() > 0)
    {
        return STRAIGHT;
    }

    // Three of a Kind
    WinningCards = PlayerHand.IsThreeOfAKind();

    if (WinningCards.size() > 0)
    {
        return THREE_OF_A_KIND;
    }

    // Two Pair
    WinningCards = PlayerHand.IsTwoPair();

    if (WinningCards.size() > 0)
    {
        return TWO_PAIR;
    }

    // Jacks or Better
    WinningCards = PlayerHand.IsJacksOrBetter();

    if (WinningCards.size() > 0)
    {
        return JACKS_OR_BETTER;
    }

    return LOSE;
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
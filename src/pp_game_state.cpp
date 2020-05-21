#include "pp_game_state.h"
#include "pp_logger.h"

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

    Win = LOSE;
    LastWinAmount = 0;
    ResetFlag = false;

    Command::HandleCommandList(NewGameCommands);

    // If the bet has already been selected, jump to placing the bet, else wait for a bet
    if (ActualBet > 0)
    {
        PokerState = POKER_PLACE_BET;
    }
    else
    {
        PokerState = POKER_WAIT_FOR_BET;
    }
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
    }
    else
    {
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
    LastWinAmount = ActualBet * Win;
    PlayerCoins += LastWinAmount;

    // Flag the winning cards in the hand
    for (auto w : WinningCards)
    {
        CardFlags[w].Winning = true;
    }

    // Track hand statistics
    Stats.HandsPlayed++;
    Stats.TotalCoinsBet += ActualBet;
    Stats.TotalCoinsWon += (ActualBet * Win);

    if (Win != LOSE)
    {
        Stats.HandsWon++;
        Stats.CurrentWinningStreak++;

        if (Stats.CurrentWinningStreak > Stats.LongestWinningStreak)
        {
            Stats.LongestWinningStreak = Stats.CurrentWinningStreak;
        }

        if (PlayerCoins > Stats.MostCoins)
        {
            Stats.MostCoins = PlayerCoins;
        }
    }
    else
    {
        Stats.CurrentWinningStreak = 0;
    }

    Log("---");
    Log("Hands Won " + std::to_string(Stats.HandsWon) + " / " + std::to_string(Stats.HandsPlayed));
    Log("Coins Bet: " + std::to_string(Stats.TotalCoinsBet));
    Log("Coins Won: " + std::to_string(Stats.TotalCoinsWon));
    Log("Most Coins: " + std::to_string(Stats.MostCoins));
    Log("Current Streak: " + std::to_string(Stats.CurrentWinningStreak));
    Log("Longest Winning Streak: " + std::to_string(Stats.LongestWinningStreak));
    Log("---");

    PokerState = POKER_GAME_OVER;

    if (Win)
    {
        Command::HandleCommandList(WinCommands);
    }
    else
    {
        Command::HandleCommandList(LoseCommands);
    }
}

void GameState::StateHandlerGameOver()
{
    if (DealButtonPressed)
    {
        // rebuy
        if (PlayerCoins == 0)
        {
            PlayerCoins = DEFAULT_PLAYER_COINS;
            ResetFlag = true;
        }
        else {
            PokerState = POKER_INIT;
        }

        DealButtonPressed = false;
    }

    else if (BetButtonPressed)
    {
        BetButtonPressed = false;

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

void GameState::RegisterNewGameCommand(Command *command)
{
    NewGameCommands.push_back(command);
}

void GameState::RegisterWinCommand(Command *command)
{
    WinCommands.push_back(command);
}

void GameState::RegisterLoseGameCommand(Command *command)
{
    LoseCommands.push_back(command);
}
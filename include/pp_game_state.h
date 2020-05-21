#ifndef PP_GAME_STATE_H
#define PP_GAME_STATE_H

#include <set>
#include <vector>
#include "pp_poker_hand.h"
#include "pp_point.h"
#include "pp_command.h"

/**
 * @brief Number of cards in a poker hand
 */
const int PLAYER_HAND_SIZE = 5;

enum BetOptions
{
    BET_NONE = 0,
    BET_ONE = 1,
    BET_FIVE = 5,
    BET_TEN = 10,
    BET_MAX = 50
};

enum WinType
{
    LOSE = 0,
    JACKS_OR_BETTER = 1,
    TWO_PAIR = 2,
    THREE_OF_A_KIND = 3,
    STRAIGHT = 4,
    FLUSH = 6,
    FULL_HOUSE = 9,
    FOUR_OF_A_KIND = 25,
    STRAIGHT_FLUSH = 50,
    ROYAL_FLUSH = 250
};

enum PokerGameState
{
    POKER_INIT,
    POKER_WAIT_FOR_BET,
    POKER_PLACE_BET,
    POKER_SELECT_CARDS,
    POKER_DEAL,
    POKER_GAME_OVER
};

struct GameStats
{
    uint32_t HandsPlayed = 0;
    uint32_t HandsWon = 0;
    uint32_t TotalCoinsBet = 0;
    uint32_t TotalCoinsWon = 0;
    uint32_t MostCoins = 0;
    uint32_t CurrentWinningStreak = 0;
    uint32_t LongestWinningStreak = 0;
};

struct MouseState
{
    Point DownPos;
    Point UpPos;
    Point CurrentPos;
    bool Clicked;
};

struct CardFlag
{
    bool Clicked;
    bool Selected;
    bool Winning;
};

class GameState
{
private:
    std::vector<Command *> NewGameCommands;
    std::vector<Command *> WinCommands;
    std::vector<Command *> LoseCommands;

    void StateHandlerInit();
    void StateHandlerWaitForBet();
    void StateHandlerPlaceBet();
    void StateHandlerSelectCards();
    void StateHandlerDeal();
    void StateHandlerGameOver();

    WinType CheckWinnings();
    void ClearCardFlags();

public:
    // Game State
    PokerGameState PokerState;
    CardFlag CardFlags[PLAYER_HAND_SIZE];
    Deck SourceDeck;
    Deck PlayerDiscard;
    PokerHand PlayerHand;
    uint32_t PlayerCoins = 100;
    WinType Win;
    uint32_t LastWinAmount;
    BetOptions PlayerBet;
    uint32_t ActualBet;
    GameStats Stats;

    // TODO: find a better way to represent winning card selection
    std::set<int> WinningCards;

    // Flags
    // Could think of these as action pending flags to make them more generic
    bool BetButtonPressed;
    bool DealButtonPressed;

    // User
    MouseState Mouse;

    void Init();
    void Update();
    void Destroy();

    void RegisterNewGameCommand(Command *command);
    void RegisterWinCommand(Command *command);
    void RegisterLoseGameCommand(Command *command);
};

#endif

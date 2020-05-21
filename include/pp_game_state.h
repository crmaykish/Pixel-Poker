#ifndef PP_GAME_STATE_H
#define PP_GAME_STATE_H

#include <set>
#include "pp_poker_hand.h"
#include "pp_point.h"

/**
 * @brief Number of cards in a poker hand
 */
const int PLAYER_HAND_SIZE = 5;

enum BetOptions
{
    BET_ONE = 1,
    BET_FIVE = 5,
    BET_TEN = 10,
    BET_MAX = 50
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
    void StateHandlerInit();
    void StateHandlerWaitForBet();
    void StateHandlerPlaceBet();
    void StateHandlerSelectCards();
    void StateHandlerDeal();
    void StateHandlerGameOver();

    int CheckWinnings();
    void ClearCardFlags();
public:
    // Game State
    PokerGameState PokerState;
    CardFlag CardFlags[PLAYER_HAND_SIZE];
    Deck SourceDeck;
    Deck PlayerDiscard;
    PokerHand PlayerHand;
    int PlayerCoins = 100;
    int WinAmount;  // TODO: make this an enum like the bet options, maybe combine it with the winning cards
    BetOptions PlayerBet;

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
};

#endif

#ifndef PP_GAME_STATE_H
#define PP_GAME_STATE_H

#include <set>
#include "pp_poker_hand.h"
#include "pp_point.h"

/**
 * @brief Number of cards in a poker hand
 */
const int PLAYER_HAND_SIZE = 5;

struct MouseState
{
    Point DownPos;
    Point UpPos;
    Point CurrentPos;
    bool Clicked;
};

struct GameStateObject
{
    MouseState Mouse;

    bool SelectedCards[PLAYER_HAND_SIZE];
    std::set<int> WinningCards;
    
    Deck SourceDeck;
    Deck PlayerDiscard;
    PokerHand PlayerHand;

    int TotalCoins;
    int LastBet;
    int LastWinnings;
};

class GameState
{
    private:
        void CheckWinnings();
    public:
        GameStateObject State;

        void Init();
        void Update();
        void Destroy();
        
};

#endif

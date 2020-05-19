#ifndef PP_COMMAND_H
#define PP_COMMAND_H

#include <iostream>
#include "pp_game_state.h"

class GameCommand
{
public:
    virtual void Execute(GameState &gameState) = 0;
};

/**
 * @brief Command to signal a bet has been placed
 */
class BetCommand : public GameCommand
{
public:
    void Execute(GameState &gameState)
    {
        std::cout << "BET" << std::endl;
    }
};

/**
 * @brief Command to signal a deal of cards
 */
class DealCommand : public GameCommand
{
public:
    void Execute(GameState &gameState)
    {
        std::cout << "DEAL" << std::endl;
    }
};

#endif
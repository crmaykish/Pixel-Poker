#ifndef PP_COMMAND_H
#define PP_COMMAND_H

#include <iostream>
#include <string>
#include "pp_game_state.h"
#include "pp_asset_manager.h"

// TODO: execute() probably doesn't need to take in gamestate. pass that in through the constructor
// along with whatever else we need
// that way any element can update based on anything else

// TODO: these are basically just event handlers tied to different things
// try to keep it clear when they are causes vs effects

// for example: don't do the heavy lifting in these commands
// just use them to set flags or text state and let the main update loop
// do the real game logic

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
        gameState.BetButtonPressed = true;
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
        gameState.DealButtonPressed = true;
    }
};

class UpdateCoinTextCommand : public GameCommand
{
private:
    std::string *textPointer;

public:
    UpdateCoinTextCommand(std::string *TextTarget)
    {
        textPointer = TextTarget;
    }

    void Execute(GameState &gameState)
    {
        *textPointer = "COINS: " + std::to_string(gameState.PlayerCoins);
    }
};

class CardClickedCommand : public GameCommand
{
private:
    int index;

public:
    CardClickedCommand(int i)
    {
        index = i;
    }

    void Execute(GameState &gameState)
    {
        gameState.CardFlags[index].Clicked = true;
        std::cout << "CARD CLICKED: " << index << std::endl;
    }
};

#endif
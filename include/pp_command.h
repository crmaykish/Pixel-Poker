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

// RenderCommand

class Command
{
public:
    virtual void Execute() = 0;
};

class RenderCommand : public Command
{
protected:
    Renderer *Render;

public:
    RenderCommand(Renderer *render)
    {
        Render = render;
    }
};

// GameCommand

class GameCommand : public Command
{
protected:
    GameState *Game;

public:
    GameCommand(GameState *game)
    {
        Game = game;
    }
};

/**
 * @brief Command to signal a bet has been placed
 */
class BetCommand : public GameCommand
{
public:
    BetCommand(GameState *game) : GameCommand(game) {}

    void Execute()
    {
        std::cout << "BET" << std::endl;
        Game->BetButtonPressed = true;
    }
};

/**
 * @brief Command to signal a deal of cards
 */
class DealCommand : public GameCommand
{
public:
    DealCommand(GameState *game) : GameCommand(game) {}

    void Execute()
    {
        std::cout << "DEAL" << std::endl;
        Game->DealButtonPressed = true;
    }
};

class UpdateCoinTextCommand : public GameCommand
{
private:
    std::string *Text;

public:
    UpdateCoinTextCommand(GameState *game) : GameCommand(game) {}

    void Execute()
    {
        if (Text != NULL)
        {
            *Text = "COINS: " + std::to_string(Game->PlayerCoins);
        }
    }

    void SetText(std::string *text)
    {
        Text = text;
    }
};

class CardClickedCommand : public GameCommand
{
private:
    int CardIndex;

public:
    CardClickedCommand(GameState *game) : GameCommand(game) {}

    void Execute()
    {
        Game->CardFlags[CardIndex].Clicked = true;
        std::cout << "CARD CLICKED: " << CardIndex << std::endl;
    }

    void SetCardIndex(int cardIndex)
    {
        CardIndex = cardIndex;
    }
};

#endif
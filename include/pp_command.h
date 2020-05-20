#ifndef PP_COMMAND_H
#define PP_COMMAND_H

#include <iostream>
#include <string>
#include "pp_game_state.h"
#include "pp_asset_manager.h"
#include "pp_logger.h"

// Command

class Command
{
public:
    virtual void Execute() = 0;
};

// RenderCommand

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
        Log("BET button pressed");
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
        Log("Deal button pressed");
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
        Log("CARD CLICKED: " + std::to_string(CardIndex));
        Game->CardFlags[CardIndex].Clicked = true;
    }

    void SetCardIndex(int cardIndex)
    {
        CardIndex = cardIndex;
    }
};

#endif
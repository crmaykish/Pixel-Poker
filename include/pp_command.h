#ifndef PP_COMMAND_H
#define PP_COMMAND_H

#include <iostream>
#include <string>
#include "pp_game_state.h"
#include "pp_asset_manager.h"
#include "pp_logger.h"

#pragma region Base Commands

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

#pragma endregion

#pragma region Update Commands

class UpdateTextCommand : public GameCommand
{
protected:
    std::string *Text;

public:
    virtual std::string GetNewText() = 0;

    UpdateTextCommand(GameState *game, std::string *text) : GameCommand(game)
    {
        Text = text;
    }

    void Execute()
    {
        if (Text != NULL)
        {
            *Text = GetNewText();
        }
    }
};

class UpdateCoinTextCommand : public UpdateTextCommand
{
public:
    UpdateCoinTextCommand(GameState *game, std::string *text) : UpdateTextCommand(game, text)
    {
        Text = text;
    }

    std::string GetNewText()
    {
        return "COINS: " + std::to_string(Game->PlayerCoins);
    }
};

class UpdateDealButtonTextCommand : public UpdateTextCommand
{
public:
    UpdateDealButtonTextCommand(GameState *game, std::string *text) : UpdateTextCommand(game, text)
    {
        Text = text;
    }

    std::string GetNewText()
    {
        return (Game->PokerState == POKER_GAME_OVER) ? "PLAY AGAIN" : "DEAL";
    }
};

// TODO: this is insane - running an command function every frame to look up a static text value
// fix this with a static text UI element
class UpdateStaticTextCommand : public UpdateTextCommand
{
public:
    UpdateStaticTextCommand(GameState *game, std::string *text) : UpdateTextCommand(game, text)
    {
        Text = text;
    }

    std::string GetNewText()
    {
        return *Text;
    }
};

#pragma endregion

#pragma region Button Click Handlers

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

#pragma endregion

#endif
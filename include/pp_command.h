#ifndef PP_COMMAND_H
#define PP_COMMAND_H

#include "pp_renderer.h"
#include "pp_game_state.h"

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
    RenderCommand(Renderer *render);
};

class GameCommand : public Command
{
protected:
    GameState *Game;

public:
    GameCommand(GameState *game);
};

#endif // PP_COMMAND_H

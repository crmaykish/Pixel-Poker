#ifndef PP_COMMAND_H
#define PP_COMMAND_H

#include "pp_renderer.h"
#include "pp_game_state.h"
#include "pp_sound_player.h"

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

class SoundCommand : public Command
{
protected:
    SoundPlayer Sounds;

public:
    SoundCommand(SoundPlayer *sounds);
}

#endif // PP_COMMAND_H

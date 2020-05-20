#include "pp_command.h"

RenderCommand::RenderCommand(Renderer *render)
{
    Render = render;
}

GameCommand::GameCommand(GameState *game)
{
    Game = game;
}


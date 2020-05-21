#ifndef PP_GAME_COMMAND_H
#define PP_GAME_COMMAND_H

#include "pp_command.h"
#include "pp_game_state.h"

class GameCommand : public Command
{
protected:
    GameState *Game;

public:
    GameCommand(GameState *game);
};

#endif // PP_GAME_COMMAND_H

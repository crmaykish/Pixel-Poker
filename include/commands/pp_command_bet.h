#ifndef PP_COMMAND_BET_H
#define PP_COMMAND_BET_H

#include "pp_command.h"
#include "pp_game_state.h"

class BetCommand : public GameCommand
{
public:
    BetCommand(GameState *game);
    void Execute();
};

#endif // PP_COMMAND_BET_H

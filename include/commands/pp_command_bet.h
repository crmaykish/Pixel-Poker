#ifndef PP_COMMAND_BET_H
#define PP_COMMAND_BET_H

#include "pp_command.h"
#include "pp_game_state.h"

class BetCommand : public GameCommand
{
private:
    BetOptions BetOption;

public:
    BetCommand(GameState *game, BetOptions betOption);
    void Execute();
};

#endif // PP_COMMAND_BET_H

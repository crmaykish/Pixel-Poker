#ifndef PP_COMMAND_UPDATE_BET_BUTTON_H
#define PP_COMMAND_UPDATE_BET_BUTTON_H

#include "pp_game_command.h"
#include "pp_interface.h"

class UpdateBetButtonCommand : public GameCommand
{
protected:
    InterfaceButton *UpdateTarget;
    BetOptions BetOption;

public:
    UpdateBetButtonCommand(GameState *game, InterfaceButton *updateTarget, BetOptions betOption);
    void Execute();
};

#endif // PP_COMMAND_UPDATE_BET_BUTTON_H

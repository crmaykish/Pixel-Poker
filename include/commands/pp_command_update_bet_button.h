#ifndef PP_COMMAND_UPDATE_BET_BUTTON_H
#define PP_COMMAND_UPDATE_BET_BUTTON_H

#include "pp_command.h"
#include "pp_interface.h"

class UpdateBetButtonCommand : public GameCommand
{
protected:
    InterfaceButton *UpdateTarget;

public:
    UpdateBetButtonCommand(GameState *game, InterfaceButton *updateTarget);
    void Execute();
};

#endif // PP_COMMAND_UPDATE_BET_BUTTON_H

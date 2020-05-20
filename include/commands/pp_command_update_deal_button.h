#ifndef PP_COMMAND_UPDATE_DEAL_BUTTON_H
#define PP_COMMAND_UPDATE_DEAL_BUTTON_H

#include "pp_command.h"
#include "pp_interface.h"

class UpdateDealButtonCommand : public GameCommand
{
protected:
    InterfaceButton *UpdateTarget;

public:
    UpdateDealButtonCommand(GameState *game, InterfaceButton *updateTarget);
    void Execute();
};

#endif // PP_COMMAND_UPDATE_DEAL_BUTTON_H

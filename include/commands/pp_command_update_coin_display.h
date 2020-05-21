#ifndef PP_COMMAND_UPDATE_COIN_DISPLAY_H
#define PP_COMMAND_UPDATE_COIN_DISPLAY_H

#include "pp_game_command.h"
#include "pp_interface.h"

class UpdateCoinDisplayCommand : public GameCommand
{
protected:
    InterfaceText *UpdateTarget;

public:
    UpdateCoinDisplayCommand(GameState *game, InterfaceText *updateTarget);
    void Execute();
};

#endif // PP_COMMAND_UPDATE_COIN_DISPLAY_H

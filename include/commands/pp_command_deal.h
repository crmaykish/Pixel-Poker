#ifndef PP_COMMAND_DEAL_H
#define PP_COMMAND_DEAL_H

#include "pp_command.h"

class DealCommand : public GameCommand
{
public:
    DealCommand(GameState *game);
    void Execute();
};

#endif // PP_COMMAND_DEAL_H

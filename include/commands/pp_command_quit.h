#ifndef PP_COMMAND_QUIT_H
#define PP_COMMAND_QUIT_H

#include "pp_command.h"

class QuitCommand : public Command
{
public:
    void Execute();
};

#endif // PP_COMMAND_QUIT_H

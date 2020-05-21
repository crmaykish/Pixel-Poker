//TODO: include guard

#include "pp_command.h"
#include "pp_interface.h"

class UpdateMessagesCommand : public GameCommand
{
protected:
    InterfaceText *UpdateTarget;

public:
    UpdateMessagesCommand(GameState *game, InterfaceText *updateTarget);
    void Execute();
};

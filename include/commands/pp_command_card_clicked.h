#ifndef PP_COMMAND_CARD_CLICKED_H
#define PP_COMMAND_CARD_CLICKED_H

#include "pp_command_deal.h"
#include "pp_interface.h"

class CardClickedCommand : public GameCommand
{
private:
    InterfacePlayingCard *UpdateTarget;

public:
    CardClickedCommand(GameState *game, InterfacePlayingCard *updateTarget);
    void Execute();
};

#endif // PP_COMMAND_CARD_CLICKED_H

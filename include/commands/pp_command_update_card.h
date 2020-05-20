#ifndef PP_COMMAND_UPDATE_PLAYING_CARD_H
#define PP_COMMAND_UPDATE_PLAYING_CARD_H

#include "pp_command.h"
#include "pp_interface.h"

class UpdatePlayingCardCommand : public GameCommand
{
protected:
    InterfacePlayingCard *UpdateTarget;

public:
    UpdatePlayingCardCommand(GameState *game, InterfacePlayingCard *updateTarget);
    void Execute();
};

#endif // PP_COMMAND_UPDATE_PLAYING_CARD_H

#include "pp_command_update_card.h"

UpdatePlayingCardCommand::UpdatePlayingCardCommand(GameState *game, InterfacePlayingCard *updateTarget) : GameCommand(game) {
    UpdateTarget = updateTarget;
}

void UpdatePlayingCardCommand::Execute()
{
}
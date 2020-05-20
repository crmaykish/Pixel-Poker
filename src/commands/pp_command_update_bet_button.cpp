#include "pp_command_update_bet_button.h"

UpdateBetButtonCommand::UpdateBetButtonCommand(GameState *game, InterfaceButton *updateTarget) : GameCommand(game) {
    UpdateTarget = updateTarget;
}

void UpdateBetButtonCommand::Execute()
{
    if (Game->PokerState == POKER_WAIT_FOR_BET)
    {
        UpdateTarget->Enable();
    }
    else
    {
        UpdateTarget->Disable();
    }
}
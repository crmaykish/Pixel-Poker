#include "pp_command_update_bet_button.h"

UpdateBetButtonCommand::UpdateBetButtonCommand(GameState *game, InterfaceButton *updateTarget, BetOptions betOption) : GameCommand(game)
{
    UpdateTarget = updateTarget;
    BetOption = betOption;
}

void UpdateBetButtonCommand::Execute()
{
    if (Game->PokerState == POKER_WAIT_FOR_BET && Game->PlayerCoins >= BetOption)
    {
        UpdateTarget->Enable();
    }
    else
    {
        UpdateTarget->Disable();
    }
}
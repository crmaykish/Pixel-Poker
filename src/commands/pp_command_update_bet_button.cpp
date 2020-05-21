#include "pp_command_update_bet_button.h"

UpdateBetButtonCommand::UpdateBetButtonCommand(GameState *game, InterfaceButton *updateTarget, BetOptions betOption) : GameCommand(game)
{
    UpdateTarget = updateTarget;
    BetOption = betOption;
}

void UpdateBetButtonCommand::Execute()
{
    UpdateTarget->Disable();

    if (Game->PokerState == POKER_WAIT_FOR_BET || Game->PokerState == POKER_GAME_OVER)
    {
        if ((BetOption == BET_MAX && Game->PlayerCoins > 0) ||
            (Game->PlayerCoins >= BetOption))
        {
            UpdateTarget->Enable();
        }
    }
    
}
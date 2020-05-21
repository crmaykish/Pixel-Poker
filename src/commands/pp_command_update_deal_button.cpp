#include "pp_command_update_deal_button.h"

UpdateDealButtonCommand::UpdateDealButtonCommand(GameState *game, InterfaceButton *updateTarget) : GameCommand(game)
{
    UpdateTarget = updateTarget;
}

void UpdateDealButtonCommand::Execute()
{
    switch (Game->PokerState)
    {
    case POKER_SELECT_CARDS:

        UpdateTarget->Enable();
        break;
    case POKER_GAME_OVER:

        UpdateTarget->Enable();

        if (Game->PlayerCoins == 0)
        {
            UpdateTarget->SetText("REBUY");
        }
        else
        {
            UpdateTarget->SetText("REPEAT BET");

            if (Game->PlayerCoins < Game->ActualBet || Game->ResetFlag)
            {
                UpdateTarget->Disable();
            }
        }
        
        break;
    default:
        UpdateTarget->SetText("DEAL");
        UpdateTarget->Disable();
        break;
    }
}
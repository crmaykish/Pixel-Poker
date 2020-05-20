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
        UpdateTarget->SetText("PLAY AGAIN");
        UpdateTarget->Enable();
        break;
    default:
        UpdateTarget->SetText("DEAL");
        UpdateTarget->Disable();
        break;
    }
}
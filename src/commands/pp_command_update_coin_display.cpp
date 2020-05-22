#include "pp_command_update_coin_display.h"

UpdateCoinDisplayCommand::UpdateCoinDisplayCommand(GameState *game, InterfaceText *updateTarget) : GameCommand(game)
{
    // GameCommand(game);
    UpdateTarget = updateTarget;
}

void UpdateCoinDisplayCommand::Execute()
{
    UpdateTarget->SetText(std::to_string(Game->PlayerCoins));
}
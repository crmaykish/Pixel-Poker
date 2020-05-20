#include "pp_command_bet.h"
#include "pp_logger.h"

BetCommand::BetCommand(GameState *game) : GameCommand(game) {

}

void BetCommand::Execute()
{
    // Log("BET button pressed");
    Game->BetButtonPressed = true;
}
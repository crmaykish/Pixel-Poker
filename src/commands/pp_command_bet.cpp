#include "pp_command_bet.h"
#include "pp_logger.h"

BetCommand::BetCommand(GameState *game, BetOptions betOption) : GameCommand(game) {
    BetOption = betOption;
}

void BetCommand::Execute()
{
    Log("Bet button pressed: " + std::to_string(BetOption), LOG_INFO);
    Game->PlayerBet = BetOption;
    Game->BetButtonPressed = true;
}
#include "pp_command_bet.h"
#include "pp_logger.h"

BetCommand::BetCommand(GameState *game, SoundPlayer *sounds, BetOptions betOption) : GameCommand(game)
{
    Sounds = sounds;
    BetOption = betOption;
}

void BetCommand::Execute()
{
    Log("Bet button pressed: " + std::to_string(BetOption), LOG_INFO);

    Sounds->PlaySound(ASSET_SOUND_BUTTON_0);

    Game->PlayerBet = BetOption;
    Game->BetButtonPressed = true;
}
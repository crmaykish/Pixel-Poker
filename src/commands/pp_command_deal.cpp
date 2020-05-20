#include "pp_command_deal.h"
#include "pp_logger.h"

DealCommand::DealCommand(GameState *game) : GameCommand(game)
{

}

void DealCommand::Execute()
{
    Log("Deal button pressed");
    Game->DealButtonPressed = true;
}
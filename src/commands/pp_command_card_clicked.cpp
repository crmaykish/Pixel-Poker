#include "pp_command_card_clicked.h"
#include "pp_logger.h"

CardClickedCommand::CardClickedCommand(GameState *game, InterfacePlayingCard *updateTarget) : GameCommand(game)
{
    UpdateTarget = updateTarget;
}

void CardClickedCommand::Execute()
{
    int index = UpdateTarget->GetIndexInHand();
    Log("CARD CLICKED: " + std::to_string(index));
    Game->CardFlags[index].Clicked = true;
}
#include "pp_command_update_messages.h"

UpdateMessagesCommand::UpdateMessagesCommand(GameState *game, InterfaceText *updateTarget) : GameCommand(game)
{
    // GameCommand(game);
    UpdateTarget = updateTarget;
}

void UpdateMessagesCommand::Execute()
{
    std::string txt;

    if (Game->PokerState == POKER_WAIT_FOR_BET)
    {
        txt = "PLACE YOUR BET";
    }
    else if (Game->PokerState == POKER_SELECT_CARDS)
    {
        txt = "SELECT CARDS TO HOLD";
    }
    else if (Game->PokerState == POKER_GAME_OVER)
    {
        switch (Game->Win)
        {
        case ROYAL_FLUSH:
            txt = "ROYAL FLUSH";
            break;
        case STRAIGHT_FLUSH:
            txt = "STRAIGHT FLUSH";
            break;
        case FOUR_OF_A_KIND:
            txt = "FOUR OF A KIND";
            break;
        case FULL_HOUSE:
            txt = "FULL HOUSE";
            break;
        case STRAIGHT:
            txt = "STRAIGHT";
            break;
        case FLUSH:
            txt = "FLUSH";
            break;
        case THREE_OF_A_KIND:
            txt = "THREE OF A KIND";
            break;
        case TWO_PAIR:
            txt = "TWO PAIR";
            break;
        case JACKS_OR_BETTER:
            txt = "JACKS OR BETTER";
            break;

        default:
            txt = "NO WINNER";
        }

        if (Game->Win != LOSE)
        {
            txt += " WIN " + std::to_string(Game->Win * Game->PlayerBet);
        }
    }

    UpdateTarget->SetText(txt);
}
#ifndef PP_COMMAND_BET_H
#define PP_COMMAND_BET_H

#include "pp_command.h"
#include "pp_game_state.h"
#include "pp_sound_player.h"

class BetCommand : public GameCommand
{
private:
    SoundPlayer *Sounds;
    BetOptions BetOption;

public:
    BetCommand(GameState *game, SoundPlayer *sounds, BetOptions betOption);
    void Execute();
};

#endif // PP_COMMAND_BET_H

#ifndef PP_COMMAND_PLAY_SOUND_H
#define PP_COMMAND_PLAY_SOUND_H

#include "pp_command.h"
#include "SDL2/SDL_mixer.h"

class PlaySoundCommand : public SoundCommand
{
protected:
    std::string SoundKey;

public:
    PlaySoundCommand(std::string soundKey);
}

#endif // PP_COMMAND_PLAY_SOUND_H

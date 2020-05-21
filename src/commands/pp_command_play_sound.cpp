#include "pp_command_play_sound.h"

PlaySoundCommand::PlaySoundCommand(SoundPlayer *sounds, std::string soundKey) : SoundCommand(sounds)
{
        SoundKey = soundKey;
}

void PlaySoundCommand::Execute()
{
    Sounds->PlaySound(SoundKey);
}
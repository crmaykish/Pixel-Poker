#include "pp_sound_player.h"

void SoundPlayer::Init()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void SoundPlayer::SetAssetManager(AssetManager *assets)
{
    Assets = assets;
}

void SoundPlayer::PlaySound(std::string soundKey)
{
    Mix_PlayChannel(-1, Assets->GetSound(soundKey), 0);
}
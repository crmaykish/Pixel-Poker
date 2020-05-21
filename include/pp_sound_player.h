#ifndef PP_SOUND_PLAYER_H
#define PP_SOUND_PLAYER_H

#include "pp_asset_manager.h"

class SoundPlayer
{
private:
    AssetManager *Assets;

public:
    void Init();
    void SetAssetManager(AssetManager *assets);
    void PlaySound(std::string soundKey);
};

#endif // PP_SOUND_PLAYER_H

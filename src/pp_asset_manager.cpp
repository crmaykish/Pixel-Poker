#include "pp_asset_manager.h"

void AssetManager::SetRenderer(Renderer *ren)
{
    renderer = ren;
}

std::string AssetManager::GetText(std::string key)
{
    return NULL;
}

SDL_Texture *AssetManager::GetTexture(std::string key)
{
    // TODO: does no caching, always loads from a file
    SDL_Texture *t = NULL;

    if (t == NULL)
    {
        // Attempt to load texture from file
        t = renderer->LoadTexture(MEDIA_PATH + key);
    }

    return t;
}

TTF_Font *AssetManager::GetFont(std::string key)
{
    // std::string fontPath = FONT_PATH + FONT_NAME;
    // Font = TTF_OpenFont(fontPath.c_str(), FONT_SIZE);

    // TTF_SetFontStyle(Font, TTF_STYLE_BOLD);

    return NULL;
}
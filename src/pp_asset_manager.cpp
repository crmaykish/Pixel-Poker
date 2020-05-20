#include "pp_asset_manager.h"
#include "pp_logger.h"

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
        t = renderer->LoadTexture(IMAGES_PATH + key);

    }

    return t;
}

TTF_Font *AssetManager::GetFont(std::string key)
{
    // TODO: does no caching, always loads from a file
    TTF_Font *f = NULL;

    if (f == NULL)
    {
        f = renderer->LoadFont(FONTS_PATH + key);
    }

    return f;
}
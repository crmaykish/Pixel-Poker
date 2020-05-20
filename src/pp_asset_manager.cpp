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
    SDL_Texture *t = NULL;

    // Check for the texture in the cache

    try
    {
        t = textureMap.at(key);
    }
    catch (...)
    {
    }

    // If the texture was not found in the cache, load it from file and cache it
    if (t == NULL)
    {
        Log("Loading texture: " + key, LOG_INFO);
        t = renderer->LoadTexture(IMAGES_PATH + key);

        if (t == NULL)
        {
            Log("Failed to load texture: " + key, LOG_ERROR);
        }

        textureMap.insert({key, t});
    }

    return t;
}

TTF_Font *AssetManager::GetFont(std::string key)
{
    // TODO: does no caching, always loads from a file
    TTF_Font *f = NULL;

    try
    {
        f = fontMap.at(key);
    }
    catch (...)
    {
    }

    if (f == NULL)
    {
        Log("Loading font: " + key, LOG_INFO);
        f = renderer->LoadFont(FONTS_PATH + key);

        if (f == NULL)
        {
            Log("Failed to load font: " + key, LOG_ERROR);
        }

        fontMap.insert({key, f});
    }

    return f;
}
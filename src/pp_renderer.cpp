#include "pp_renderer.h"
#include "pp_game_state.h"

void Renderer::Init(Settings settings)
{
    // TODO: error checking

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    // Create an SDL Window
    SDLWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(),
                                 0, 0,
                                 settings.Resolution.w, settings.Resolution.h,
                                 settings.Resolution.fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);

    // Create an SDL renderer and attach it to the window
    SDLRenderer = SDL_CreateRenderer(SDLWindow,
                                     -1,
                                     SDL_RENDERER_ACCELERATED);

    // Set the SDL blend mode to BLEND
    SDL_SetRenderDrawBlendMode(SDLRenderer, SDL_BLENDMODE_BLEND);

    // Open the SDL window
    SDL_ShowWindow(SDLWindow);
}

void Renderer::Sleep()
{
    SDL_Delay(1000 / 60);
}

void Renderer::RenderTexture(SDL_Texture *tex, SDL_Rect *rect)
{
    SDL_RenderCopy(SDLRenderer, tex, NULL, rect);
}

void Renderer::RenderText(std::string text, TTF_Font *font, SDL_Color color, SDL_Rect *rect)
{
    SDL_Surface *s = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture *t = SDL_CreateTextureFromSurface(SDLRenderer, s);

    SDL_RenderCopy(SDLRenderer, t, NULL, rect);

    SDL_FreeSurface(s);
    SDL_DestroyTexture(t);
}

void Renderer::RenderRectangle(SDL_Color color, SDL_Rect *rect)
{
    SDL_SetRenderDrawColor(SDLRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(SDLRenderer, rect);
}

SDL_Texture *Renderer::LoadTexture(std::string fileName)
{
    return IMG_LoadTexture(SDLRenderer, fileName.c_str());
}

TTF_Font *Renderer::LoadFont(std::string fileName)
{
    TTF_Font *f = TTF_OpenFont(fileName.c_str(), 256);

    return f;
}

Mix_Chunk *Renderer::LoadSound(std::string fileName)
{
    return Mix_LoadWAV(fileName.c_str());
}

Mix_Music *Renderer::Mix_LoadMUS(std::string fileName)
{
    // TODO
}

void Renderer::Clear()
{
    SDL_RenderClear(SDLRenderer);
}

void Renderer::Present()
{
    SDL_RenderPresent(SDLRenderer);
}

void Renderer::Destroy()
{
    SDL_DestroyRenderer(SDLRenderer);
    SDL_DestroyWindow(SDLWindow);
    SDL_Quit();
}
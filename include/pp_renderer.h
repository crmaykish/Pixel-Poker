#ifndef PP_RENDERER_H
#define PP_RENDERER_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "pp_settings.h"

const std::string WINDOW_TITLE = "Pixel Poker";

// This should be a thin layer between game code and SDL calls
class Renderer
{
private:
    SDL_Window *SDLWindow;
    SDL_Renderer *SDLRenderer;

public:
    void Init(Settings settings);
    void Destroy();

    void Sleep();

    void RenderTexture(SDL_Texture *tex, SDL_Rect *rect);
    void RenderText(std::string text, TTF_Font *font, SDL_Color color, SDL_Rect *rect);
    void RenderRectangle(SDL_Color color, SDL_Rect *rect);

    void Clear();
    void Present();

    SDL_Texture *LoadTexture(std::string fileName);
    TTF_Font *LoadFont(std::string fileName);
    Mix_Chunk *LoadSound(std::string fileName);
    Mix_Music *Mix_LoadMUS(std::string fileName);

};

#endif
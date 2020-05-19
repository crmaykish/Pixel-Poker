#include "pp_renderer.h"
#include "pp_game_state.h"

// void RenderText(SDL_Renderer *Renderer, std::string Text, const SDL_Rect *Rect)
// {
//     SDL_Surface *s;
//     SDL_Texture *t;

//     SDL_Color c = {0xFF, 0x00, 0x00};

//     s = TTF_RenderText_Solid(Font, Text.c_str(), c);
//     t = SDL_CreateTextureFromSurface(Renderer, s);
//     SDL_RenderCopy(Renderer, t, NULL, Rect);
//     SDL_FreeSurface(s);
//     SDL_DestroyTexture(t);
// }

void Renderer::HandleInput(GameState &gameState)
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            // TODO: Clean up properly before killing the application
            exit(0);
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            // Set mouse clicked flag
            gameState.State.MouseClicked = true;
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            // Clear mouse clicked flag
            gameState.State.MouseClicked = false;
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
            // continuously capture mouse position
            SDL_GetMouseState(&gameState.State.MousePosition.position[0], &gameState.State.MousePosition.position[1]);
        }
    }
}

void Renderer::Init()
{
    // TODO: error checking

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    // Create an SDL Window
    SDLWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(),
                                 0, 0,
                                 WINDOW_W_PIXELS, WINDOW_H_PIXELS,
                                 SDL_WINDOW_SHOWN);

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

void Renderer::RenderText(std::string text, TTF_Font *font, SDL_Color *color, SDL_Rect *rect)
{
    SDL_Surface *s = TTF_RenderText_Solid(font, text.c_str(), *color);
    SDL_Texture *t = SDL_CreateTextureFromSurface(SDLRenderer, s);

    SDL_RenderCopy(SDLRenderer, t, NULL, rect);

    SDL_FreeSurface(s);
    SDL_DestroyTexture(t);
}

SDL_Texture *Renderer::LoadTexture(std::string fileName)
{
    return IMG_LoadTexture(SDLRenderer, fileName.c_str());
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
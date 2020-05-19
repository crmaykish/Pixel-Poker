#include "pp_renderer.h"
#include "pp_game_state.h"

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
            gameState.State.Mouse.Clicked = true;
            SDL_GetMouseState(&gameState.State.Mouse.DownPos.position[0], &gameState.State.Mouse.DownPos.position[1]);
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            // Clear mouse clicked flag
            gameState.State.Mouse.Clicked = false;
            SDL_GetMouseState(&gameState.State.Mouse.UpPos.position[0], &gameState.State.Mouse.UpPos.position[1]);
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
            // continuously capture mouse position
            SDL_GetMouseState(&gameState.State.Mouse.CurrentPos.position[0], &gameState.State.Mouse.CurrentPos.position[1]);
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

void Renderer::RenderText(std::string text, TTF_Font *font, SDL_Color color, SDL_Rect *rect)
{
    SDL_Surface *s = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *t = SDL_CreateTextureFromSurface(SDLRenderer, s);

    SDL_RenderCopy(SDLRenderer, t, NULL, rect);

    SDL_FreeSurface(s);
    SDL_DestroyTexture(t);
}

SDL_Texture *Renderer::LoadTexture(std::string fileName)
{
    return IMG_LoadTexture(SDLRenderer, fileName.c_str());
}

TTF_Font *Renderer::LoadFont(std::string fileName)
{
    return TTF_OpenFont(fileName.c_str(), DEFAULT_FONT_SIZE);
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
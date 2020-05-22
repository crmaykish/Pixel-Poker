#include <SDL2/SDL.h>
#include "pp_input.h"
#include "pp_game_state.h"

void Input::HandleInput(GameState &gameState)
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            // TODO: Clean up properly before killing the application
            exit(0);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                // TODO: another exit hack
                exit(0);
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            // Set mouse clicked flag
            gameState.Mouse.Clicked = true;
            SDL_GetMouseState(&gameState.Mouse.DownPos.position[0], &gameState.Mouse.DownPos.position[1]);
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            // Clear mouse clicked flag
            gameState.Mouse.Clicked = false;
            SDL_GetMouseState(&gameState.Mouse.UpPos.position[0], &gameState.Mouse.UpPos.position[1]);
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
            // continuously capture mouse position
            SDL_GetMouseState(&gameState.Mouse.CurrentPos.position[0], &gameState.Mouse.CurrentPos.position[1]);
        }
    }
}
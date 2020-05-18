#ifndef PP_INTERFACE_H
#define PP_INTERFACE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "pp_game_state.h"

class InterfaceElement
{
    protected:
        SDL_Rect rect;
        SDL_Texture *tex;
        TTF_Font *font;
    public:
        virtual void Update(GameState& game);
        virtual void Render(GameState& game, Renderer& renderer);
};

class InterfaceButton : public InterfaceElement
{
    private:
        bool pressed;

    public:
        void Update(GameState& game)
        {
            pressed = PointInRect(&game.State.LastClickedPosition, &rect);
        }

        void Render(GameState& game, Renderer& renderer)
        {
            // TODO: tell the renderer how to draw this
        }
};

#endif
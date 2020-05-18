#ifndef PP_INTERFACE_H
#define PP_INTERFACE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class InterfaceElement
{
    protected:
        SDL_Rect rect;
        SDL_Texture *tex;
        TTF_Font *font;
    public:
        virtual void Update(Game& game);
        virtual void Render(Game& game, Renderer& renderer);
};

class InterfaceButton : public InterfaceElement
{
    private:
        bool pressed;

    public:
        void Update(Game& game)
        {
            pressed = PointInRect(&game.LastClickedPosition, &rect);
        }

        void Render(Game& game, Renderer& renderer)
        {
            // TODO: tell the renderer how to draw this
        }
};

#endif
#include "pp_interface.h"

// InterfaceElement

void InterfaceElement::SetRect(int x, int y, int w, int h)
{
    rect = {x, y, w, h};
}

// InterfaceButton

InterfaceButton::InterfaceButton(bool act, bool vis)
{
    active = act;
    visible = vis;

    pressed = false;
}

void InterfaceButton::Update(GameState &game)
{
    if (active)
    {
        pressed = game.State.MouseClicked && PointInRect(&game.State.MousePosition, &rect);

        if (pressed)
        {
            int i = 0;
        }
    }
}

void InterfaceButton::Render(GameState &game, Renderer &renderer)
{
    // TODO: do we need the game state in here? Update() should prep everything before rendering

    // Use the renderer to draw this button
    if (visible)
    {
        renderer.RenderTexture(GetTexture(), &rect);
    }
}

void InterfaceButton::Destroy()
{
}

void InterfaceButton::SetTexturePressed(SDL_Texture *tex)
{
    texPressed = tex;
}

void InterfaceButton::SetTextureUnpressed(SDL_Texture *tex)
{
    texUnpressed = tex;
}

SDL_Texture *InterfaceButton::GetTexture()
{
    return (pressed ? texPressed : texUnpressed);
}
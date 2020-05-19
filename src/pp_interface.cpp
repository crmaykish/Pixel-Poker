#include "pp_interface.h"

// InterfaceElement

void InterfaceElement::SetRect(int x, int y, int w, int h)
{
    rect = {x, y, w, h};
}

// InterfaceStaticImage

void InterfaceStaticImage::Update(GameState &game)
{
}

void InterfaceStaticImage::Render(GameState &game, Renderer &renderer)
{
    renderer.RenderTexture(texture, &rect);
}

void InterfaceStaticImage::Destroy()
{
}

void InterfaceStaticImage::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

// InterfaceText

InterfaceText::InterfaceText(bool act, bool vis)
{
    active = act;
    visible = vis;
}

void InterfaceText::Update(GameState &game)
{
    if (updateCommand != NULL)
    {
        updateCommand->Execute(game);
    }
}

void InterfaceText::Render(GameState &game, Renderer &renderer)
{
    renderer.RenderText(text, font, {0xFF, 0xFF, 0xFF, 0xFF}, &rect);
}

void InterfaceText::SetUpdateCommand(GameCommand *com)
{
    updateCommand = com;
}

std::string *InterfaceText::GetText()
{
    return &text;
}

void InterfaceText::SetText(std::string t)
{
    text = t;
}

void InterfaceText::SetFont(TTF_Font *f)
{
    font = f;
}

void InterfaceText::Destroy()
{
}

// InterfaceButton

InterfaceButton::InterfaceButton(bool act, bool vis)
{
    active = act;
    visible = vis;

    currentlyPressed = false;
    previouslyPressed = false;
}

void InterfaceButton::Update(GameState &game)
{
    // TODO: based on game state, update this button appropriately

    if (active)
    {
        previouslyPressed = currentlyPressed;

        bool mouseClicked = game.State.Mouse.Clicked;
        bool clickedButton = PointInRect(&game.State.Mouse.DownPos, &rect);
        bool releasedButton = PointInRect(&game.State.Mouse.UpPos, &rect);

        currentlyPressed = mouseClicked && clickedButton;

        if (previouslyPressed && !currentlyPressed && releasedButton)
        {
            if (command != NULL)
            {
                command->Execute(game);
            }
        }
    }
    else
    {
        // TODO: reset the button to a safe state
    }
}

void InterfaceButton::Render(GameState &game, Renderer &renderer)
{
    // TODO: do we need the game state in here? Update() should prep everything before rendering

    // Use the renderer to draw this button
    if (visible)
    {
        renderer.RenderTexture(GetTexture(), &rect);
        renderer.RenderText(text, font, {0xFF, 0xFF, 0xFF, 0xFF}, &rect);
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
    return (currentlyPressed ? texPressed : texUnpressed);
}

void InterfaceButton::SetText(std::string t)
{
    text = t;
}

void InterfaceButton::SetFont(TTF_Font *f)
{
    font = f;
}

void InterfaceButton::SetCommand(GameCommand *com)
{
    command = com;
}
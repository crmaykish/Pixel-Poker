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

void InterfaceStaticImage::Render(Renderer &renderer)
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

void InterfaceText::Render(Renderer &renderer)
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

        bool mouseClicked = game.Mouse.Clicked;
        bool clickedButton = PointInRect(&game.Mouse.DownPos, &rect);
        bool releasedButton = PointInRect(&game.Mouse.UpPos, &rect);

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

void InterfaceButton::Render(Renderer &renderer)
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

// InterfacePlayingCard

void InterfacePlayingCard::SetIndex(int i)
{
    index = i;
}

void InterfacePlayingCard::Update(GameState &game)
{
    InterfaceButton::Update(game);

    // Check for visbility / highlighted / etc
    // Need to store rendering flags in the class

    // what kind of card is this?
    if (!game.PlayerHand.IsEmpty())
    {
        card = game.PlayerHand.CardAt(index);

        highlight = game.CardFlags[index].Selected;

        winning = game.CardFlags[index].Winning;

        visible = true;
    }
    else
    {
        visible = false;

        // TODO: card is invisible, reset it to a safe state
    }
    
}

void InterfacePlayingCard::Render(Renderer &renderer)
{
    if (visible)
    {
        // TODO: this looks terrible
        renderer.RenderTexture(assetManager->GetTexture(assetManager->CardFileName(&card)), &rect);

        if (highlight)
        {
            renderer.RenderRectangle({0x00, 0x00, 0xFF, 0x50}, &rect);
        }
        
        if (winning)
        {
            renderer.RenderRectangle({0x00, 0xFF, 0x00, 0x50}, &rect);
        }
    }
}
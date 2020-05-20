#include "pp_interface.h"
#include "pp_logger.h"
#include "pp_asset_manager.h"

// InterfaceElement

InterfaceElement::InterfaceElement(AssetManager *assetManager)
{
    Assets = assetManager;
}

void InterfaceElement::SetRectangle(int x, int y, int w, int h)
{
    Rectangle = {x, y, w, h};
}

void InterfaceElement::SetUpdateCommand(GameCommand *updateCommand)
{
    UpdateCommand = updateCommand;
}

void InterfaceElement::SetPreRenderCommand(GameCommand *preRenderCommand)
{
    PreRenderCommand = preRenderCommand;
}

// InterfaceStaticImage

void InterfaceStaticImage::Update(GameState &game)
{
    if (UpdateCommand != NULL)
    {
        UpdateCommand->Execute();
    }
}

void InterfaceStaticImage::Render(Renderer &renderer)
{
    if (PreRenderCommand != NULL)
    {
        PreRenderCommand->Execute();
    }

    SDL_Texture *tex = Assets->GetTexture(TextureKey);

    if (tex == NULL)
    {
        Log(TextureKey + " is NULL", LOG_WARNING);
    }
    else
    {
        renderer.RenderTexture(tex, &Rectangle);
    }
}

void InterfaceStaticImage::Destroy() {}

void InterfaceStaticImage::SetTextureKey(std::string textureKey)
{
    TextureKey = textureKey;
}

// InterfaceText

void InterfaceText::Update(GameState &game)
{
    if (UpdateCommand != NULL)
    {
        UpdateCommand->Execute();
    }
}

void InterfaceText::Render(Renderer &renderer)
{
    if (PreRenderCommand != NULL)
    {
        PreRenderCommand->Execute();
    }

    renderer.RenderText(Text,
                        Assets->GetFont(FontKey),
                        {0xFF, 0xFF, 0xFF, 0xFF},
                        &Rectangle);
}

void InterfaceText::Destroy() {}

void InterfaceText::SetFontKey(std::string fontKey)
{
    FontKey = fontKey;
}

void InterfaceText::SetText(std::string text)
{
    Text = text;
}

std::string *InterfaceText::GetText()
{
    return &Text;
}

// InterfaceButton

void InterfaceButton::Update(GameState &game)
{
    if (Enabled)
    {
        bool mouseClicked = game.Mouse.Clicked;

        ClickedPreviously = ClickedCurrently;
        ClickedCurrently = mouseClicked && PointInRect(&game.Mouse.DownPos, &Rectangle);

        if (ClickedPreviously && !ClickedCurrently && PointInRect(&game.Mouse.UpPos, &Rectangle))
        {
            if (ClickedCommand != NULL)
            {
                ClickedCommand->Execute();
            }
        }
    }

    if (UpdateCommand != NULL)
    {
        UpdateCommand->Execute();
    }
}

void InterfaceButton::Render(Renderer &renderer)
{
    if (PreRenderCommand != NULL)
    {
        PreRenderCommand->Execute();
    }

    SDL_Texture *t = Assets->GetTexture(ClickedCurrently ? DownTextureKey : UpTextureKey);

    renderer.RenderTexture(t, &Rectangle);

    if (!Text.empty())
    {
        renderer.RenderText(Text, Assets->GetFont(FontKey), {0xFF, 0xFF, 0xFF, 0xFF}, &Rectangle);
    }

    if (!Enabled)
    {
        renderer.RenderRectangle({0x00, 0x00, 0x00, 0x50}, &Rectangle);
    }
}

void InterfaceButton::Destroy() {}

void InterfaceButton::SetClickedCommand(GameCommand *clickedCommand)
{
    ClickedCommand = clickedCommand;
}

void InterfaceButton::SetUpTextureKey(std::string upTextureKey)
{
    UpTextureKey = upTextureKey;
}

void InterfaceButton::SetDownTextureKey(std::string downTextureKey)
{
    DownTextureKey = downTextureKey;
}

// InterfacePlayingCard

void InterfacePlayingCard::SetIndexInHand(int i)
{
    IndexInHand = i;
}

int InterfacePlayingCard::GetIndexInHand()
{
    return IndexInHand;
}

void InterfacePlayingCard::Update(GameState &game)
{
    InterfaceButton::Update(game);

    // Check for visbility / highlighted / etc
    // Need to store rendering flags in the class

    // what kind of card is this?
    if (!game.PlayerHand.IsEmpty())
    {
        Card = game.PlayerHand.CardAt(IndexInHand);

        Highlighted = game.CardFlags[IndexInHand].Selected;

        Winning = game.CardFlags[IndexInHand].Winning;
    }
}

void InterfacePlayingCard::Render(Renderer &renderer)
{
    if (PreRenderCommand != NULL)
    {
        PreRenderCommand->Execute();
    }

    renderer.RenderTexture(Assets->GetTexture(Assets->CardFileName(&Card)), &Rectangle);

    if (Highlighted)
    {
        renderer.RenderRectangle({0x00, 0x00, 0xFF, 0x50}, &Rectangle);
    }

    if (Winning)
    {
        renderer.RenderRectangle({0x00, 0xFF, 0x00, 0x50}, &Rectangle);
    }
}
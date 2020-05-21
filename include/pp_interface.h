#ifndef PP_INTERFACE_H
#define PP_INTERFACE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "pp_game_state.h"
#include "pp_renderer.h"
#include "pp_command.h"
#include "pp_interface.h"
#include "pp_asset_manager.h"

// TODO: might be possible to remove the dependency on SDL and push it all to the renderer
// Just hold on to a texture key and use a generic position struct

// InterfaceElement

class InterfaceElement
{
protected:
    // State
    SDL_Rect Rectangle;
    bool Visible = true;

    // Behavior
    // TODO: may need an array of commands to register an element as multiple things
    Command *UpdateCommand = NULL; // TODO: might need pre and post update commands
    Command *PreRenderCommand = NULL;

    // Assets
    AssetManager *Assets = NULL; // TODO: this never gets set anywhere

public:
    // Virtual Methods
    virtual void Update(GameState &game) = 0;
    virtual void Render(Renderer &renderer) = 0;
    virtual void Destroy() = 0;

    // Base Methods
    InterfaceElement(AssetManager *assetManager);
    void SetRectangle(int x, int y, int w, int h);
    void SetUpdateCommand(GameCommand *updateCommand);
    void SetPreRenderCommand(GameCommand *preRenderCommand);
};

// InterfaceStaticImage

class InterfaceStaticImage : public InterfaceElement
{
private:
    std::string TextureKey;

public:
    InterfaceStaticImage(AssetManager *assetManager) : InterfaceElement(assetManager) {}
    void Update(GameState &game);
    void Render(Renderer &renderer);
    void Destroy();

    void SetTextureKey(std::string textureKey);
};

// InterfaceText

class InterfaceText : public InterfaceElement
{
protected:
    std::string Text;
    std::string FontKey;

public:
    InterfaceText(AssetManager *assetManager) : InterfaceElement(assetManager) {}
    void Update(GameState &game);
    void Render(Renderer &renderer);
    void Destroy();
    void SetFontKey(std::string fontKey);
    void SetText(std::string text);
    std::string *GetText();
};

// InterfaceButton

class InterfaceButton : public InterfaceText
{
protected:
    bool ClickedPreviously = false;
    bool ClickedCurrently = false;

    bool Enabled = false;

    std::string UpTextureKey;
    std::string DownTextureKey;
    std::string DownSoundKey;

    std::vector<Command*> ClickedCommands;

public:
    InterfaceButton(AssetManager *assetManager) : InterfaceText(assetManager) {}
    void Update(GameState &game);
    void Render(Renderer &renderer);
    void Destroy();

    void RegisterClickedCommand(Command *clickedCommand);
    void SetUpTextureKey(std::string upTextureKey);
    void SetDownTextureKey(std::string downTextureKey);
    void SetDownSoundKey(std::string downSoundKey);

    void Enable()
    {
        Enabled = true;
    }

    void Disable()
    {
        Enabled = false;
    }
};

// InterfacePlayingCard

// TODO: this is not exactly a button. Rethink this class hierarchy

class InterfacePlayingCard : public InterfaceButton
{
protected:
    // Externally controlled state
    int IndexInHand;

    // Internal state
    bool Highlighted = false;
    bool Winning = false;
    PlayingCard Card; // TODO: find a way to avoid storing the card object?

public:
    InterfacePlayingCard(AssetManager *assetManager) : InterfaceButton(assetManager) {}
    void Update(GameState &game);
    void Render(Renderer &renderer);

    void SetIndexInHand(int index);
    int GetIndexInHand();
};

#endif
#ifndef PP_INTERFACE_H
#define PP_INTERFACE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "pp_game_state.h"
#include "pp_renderer.h"
#include "pp_command.h"

// TODO: might be possible to remove the dependency on SDL and push it all to the renderer
// Just hold on to a texture key and use a generic position struct

class InterfaceElement
{
protected:
    SDL_Rect rect;
    bool active;
    bool visible;

public:
    virtual void Update(GameState &game) = 0;
    virtual void Render(GameState &game, Renderer &renderer) = 0;
    virtual void Destroy() = 0;
    void SetRect(int x, int y, int w, int h);
};

class InterfaceStaticImage : public InterfaceElement
{
private:
    SDL_Texture *texture;

public:
    void Update(GameState &game);
    void Render(GameState &game, Renderer &renderer);
    void SetTexture(SDL_Texture *tex);
    void Destroy();
};

class InterfaceButton : public InterfaceElement
{
private:
    bool previouslyPressed;
    bool currentlyPressed;
    GameCommand *command;
    SDL_Texture *texPressed;
    SDL_Texture *texUnpressed;
    std::string text;
    TTF_Font *font;

protected:
    SDL_Texture *GetTexture();

public:
    InterfaceButton(bool act = true, bool vis = true);
    void Update(GameState &game);
    void Render(GameState &game, Renderer &renderer);
    void SetTexturePressed(SDL_Texture *tex);
    void SetTextureUnpressed(SDL_Texture *tex);
    void SetText(std::string t);
    void SetCommand(GameCommand *com);
    void SetFont(TTF_Font *f);
    void Destroy();
};

#endif
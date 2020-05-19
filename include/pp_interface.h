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

class InterfaceButton : public InterfaceElement
{
private:
    bool pressed;
    SDL_Texture *texPressed;
    SDL_Texture *texUnpressed;
    GameCommand *command;

protected:
    SDL_Texture *GetTexture();

public:
    InterfaceButton(bool act = true, bool vis = true);
    void Update(GameState &game);
    void Render(GameState &game, Renderer &renderer);
    void SetTexturePressed(SDL_Texture *tex);
    void SetTextureUnpressed(SDL_Texture *tex);
    void SetCommand(GameCommand *com);
    void Destroy();
};

#endif
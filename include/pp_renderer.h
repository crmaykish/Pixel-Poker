#ifndef PP_RENDERER_H
#define PP_RENDERER_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

const std::string WINDOW_TITLE = "PIXEL POKER";

const int DEFAULT_FONT_SIZE = 32;

const int WINDOW_W_PIXELS = 1280;
const int WINDOW_H_PIXELS = 800;

const int CARD_SCALING = 4;
const int CARD_W_PIXELS = 62 * CARD_SCALING;
const int CARD_H_PIXELS = 84 * CARD_SCALING;
const int CARD_GAP_PIXELS = 6;

const int COIN_SCALING = 4;
const int COIN_W_PIXELS = 16;
const int COIN_H_PIXELS = 16;

const int DEAL_BUTTON_SCALING = 2;
const int DEAL_BUTTON_W_PIXELS = 320 * DEAL_BUTTON_SCALING;
const int DEAL_BUTTON_H_PIXELS = 64 * DEAL_BUTTON_SCALING;
const int DEAL_BUTTON_GAP = 6;

const int MAX_HAND_SIZE = 5;

const int offset_x = (WINDOW_W_PIXELS / 2) - ((MAX_HAND_SIZE * CARD_W_PIXELS) / 2) - (CARD_GAP_PIXELS * (MAX_HAND_SIZE - 1) / 2);
const int offset_y = WINDOW_H_PIXELS / 2 - CARD_H_PIXELS / 2;

const int deal_button_offset_x = WINDOW_W_PIXELS - DEAL_BUTTON_W_PIXELS - DEAL_BUTTON_GAP;
const int deal_button_offset_y = WINDOW_H_PIXELS - DEAL_BUTTON_H_PIXELS - DEAL_BUTTON_GAP;

const SDL_Rect ButtonRect = {deal_button_offset_x, deal_button_offset_y, DEAL_BUTTON_W_PIXELS, DEAL_BUTTON_H_PIXELS};
const SDL_Rect StatusMessageRect = {8, WINDOW_H_PIXELS - 64, WINDOW_W_PIXELS / 4, 64};
const SDL_Rect CoinMessageRect = {8 + COIN_W_PIXELS * COIN_SCALING, 8, WINDOW_W_PIXELS / 8, 64};

// This should be a thin layer between game code and SDL calls
class Renderer
{
private:
    SDL_Window *SDLWindow;
    SDL_Renderer *SDLRenderer;

public:
    void Init();
    void Destroy();

    void Sleep();

    void RenderTexture(SDL_Texture *tex, SDL_Rect *rect);
    void RenderText(std::string text, TTF_Font *font, SDL_Color color, SDL_Rect *rect);
    void RenderRectangle(SDL_Color color, SDL_Rect *rect);

    void Clear();
    void Present();

    SDL_Texture *LoadTexture(std::string fileName);
    TTF_Font *LoadFont(std::string fileName);
    Mix_Chunk *LoadSound(std::string fileName);
    Mix_Music *Mix_LoadMUS(std::string fileName);

};

#endif
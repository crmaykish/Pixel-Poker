#ifndef PP_ASSET_MANAGER_H
#define PP_ASSET_MANAGER_H

#include <string>
#include <map>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "pp_renderer.h"

const std::string ASSETS_PATH = "assets/";
const std::string IMAGES_PATH = ASSETS_PATH + "images/";
const std::string FONTS_PATH = ASSETS_PATH + "fonts/";
const std::string SOUNDS_PATH = ASSETS_PATH + "sounds/";

//TODO: find a better way to key assets instead of file names
const std::string ASSET_IMAGE_BG_0 = "bg.png";
const std::string ASSET_IMAGE_BTN_UP_0 = "deal_button.png";
const std::string ASSET_FONT_MONO_0 = "FreeMono.ttf";
const std::string ASSET_SOUND_WIN_0 = "winning_hand.wav";
const std::string ASSET_SOUND_LOSE_0 = "losing_hand.wav";
const std::string ASSET_SOUND_BUTTON_0 = "button_press.wav";
const std::string ASSET_SOUND_CARD_CLICK_0 = "card_click.wav";

class AssetManager
{
private:
    std::map<std::string, std::string> textMap;
    std::map<std::string, SDL_Texture *> textureMap;
    std::map<std::string, TTF_Font *> fontMap;
    std::map<std::string, Mix_Chunk *> soundMap;

    Renderer *renderer;

public:
    void SetRenderer(Renderer *r);
    std::string GetText(std::string key);
    SDL_Texture *GetTexture(std::string key);
    TTF_Font *GetFont(std::string key);
    Mix_Chunk *GetSound(std::string key);

    // TODO: doesn't really belong in asset manager, make a class for the equivalent of SoundRenderer?
    void PlaySound(std::string key);

    // TODO: clean up this mess
    std::string CardFileName(PlayingCard *p)
    {
        std::string fileName = "card_";

        if (p->Value == ACE)
        {
            fileName += "1";
        }
        else
        {
            fileName += std::to_string(p->Value);
        }

        if (p->Suit == HEART)
        {
            fileName += "_heart";
        }
        else if (p->Suit == DIAMOND)
        {
            fileName += "_diamond";
        }
        else if (p->Suit == CLUB)
        {
            fileName += "_clover";
        }
        else if (p->Suit == SPADE)
        {
            fileName += "_spade";
        }

        fileName += ".png";

        return fileName;
    }
};

#endif
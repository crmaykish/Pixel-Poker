#ifndef PP_ASSET_MANAGER_H
#define PP_ASSET_MANAGER_H

#include <string>
#include <map>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "pp_renderer.h"

const std::string ASSETS_PATH = "assets/";
const std::string IMAGES_PATH = ASSETS_PATH + "images/";
const std::string FONTS_PATH = ASSETS_PATH + "fonts/";

//TODO: find a better way to key assets instead of file names
const std::string ASSET_IMAGE_BG_0 = "bg.png";
const std::string ASSET_IMAGE_BTN_UP_0 = "deal_button.png";
const std::string ASSET_FONT_MONO_0 = "FreeMono.ttf";

class AssetManager
{
private:
    std::map<std::string, std::string> textMap;
    std::map<std::string, SDL_Texture *> textureMap;
    std::map<std::string, TTF_Font *> fontMap;

    Renderer *renderer;

public:
    void SetRenderer(Renderer *r);
    std::string GetText(std::string key);
    SDL_Texture *GetTexture(std::string key);
    TTF_Font *GetFont(std::string key);

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
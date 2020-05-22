#ifndef PP_ASSET_MANAGER_H
#define PP_ASSET_MANAGER_H

#include <string>
#include <map>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "pp_renderer.h"
#include "pp_card.h"

const std::string ASSETS_PATH = "assets/";
const std::string IMAGES_PATH = ASSETS_PATH + "images/";
const std::string FONTS_PATH = ASSETS_PATH + "fonts/";
const std::string SOUNDS_PATH = ASSETS_PATH + "sounds/";

//TODO: find a better way to key assets instead of file names
const std::string ASSET_IMAGE_BG_0 = "background/background.png";
const std::string ASSET_IMAGE_CHIP_0 = "ui/chip.png";
const std::string ASSET_IMAGE_BTN_UP_0 = "ui/button_blue_unpressed.png";
const std::string ASSET_IMAGE_BTN_DOWN_0 = "ui/button_blue_pressed.png";
const std::string ASSET_IMAGE_BTN_UP_1 = "ui/button_big_blue_unpressed.png";
const std::string ASSET_IMAGE_BTN_DOWN_1 = "ui/button_big_blue_pressed.png";
const std::string ASSET_IMAGE_BTN_UP_2 = "ui/button_red_unpressed.png";
const std::string ASSET_IMAGE_BTN_DOWN_2 = "ui/button_red_pressed.png";
const std::string ASSET_FONT_MONO_0 = "expressway rg.ttf";
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
        std::string fileName = "cards/";

        if (p->Value == ACE)
        {
            fileName += "Ace";
        }
        else if (p->Value == TWO)
        {
            fileName += "Two";
        }
        else if (p->Value == THREE)
        {
            fileName += "Three";
        }
        else if (p->Value == FOUR)
        {
            fileName += "Four";
        }
        else if (p->Value == FIVE)
        {
            fileName += "Five";
        }
        else if (p->Value == SIX)
        {
            fileName += "Six";
        }
        else if (p->Value == SEVEN)
        {
            fileName += "Seven";
        }
        else if (p->Value == EIGHT)
        {
            fileName += "Eight";
        }
        else if (p->Value == NINE)
        {
            fileName += "Nine";
        }
        else if (p->Value == TEN)
        {
            fileName += "Ten";
        }
        else if (p->Value == JACK)
        {
            fileName += "Jack";
        }
        else if (p->Value == QUEEN)
        {
            fileName += "Queen";
        }
        else if (p->Value == KING)
        {
            fileName += "King";
        }

        fileName += " of ";

        if (p->Suit == HEART)
        {
            fileName += "Hearts";
        }
        else if (p->Suit == DIAMOND)
        {
            fileName += "Diamonds";
        }
        else if (p->Suit == CLUB)
        {
            fileName += "Clubs";
        }
        else if (p->Suit == SPADE)
        {
            fileName += "Spades";
        }

        fileName += ".png";

        return fileName;
    }
};

#endif
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "card.h"

const std::string MEDIA_PATH = "/home/colin/nas/projects/cpp_games/pixel_poker/media/images/";

const int WINDOW_W_PIXELS = 1280;
const int WINDOW_H_PIXELS = 800;

const int CARD_SCALING = 4;
const int CARD_W_PIXELS = 62 * CARD_SCALING;
const int CARD_H_PIXELS = 84 * CARD_SCALING;
const int CARD_GAP_PIXELS = 6;

const int COIN_SCALING = 4;
const int COIN_W_PIXELS = 16;
const int COIN_H_PIXELS = 16;

const int MAX_HAND_SIZE = 5;

typedef enum
{
    GAME_STATE_PLAYING,
    GAME_STATE_EXIT
 } GameState;

typedef struct
{
    GameState State;

    SDL_Window *GraphicsWindow;
    SDL_Renderer *GraphicsRenderer;
    SDL_Texture *BackgroundTexture;
    SDL_Texture *CoinTexture;

    Deck SourceDeck;
    Deck PlayerHand;
    Deck PlayerDiscard;
    
    uint8_t CoinImageIndex = 0;

    bool SelectedCards[MAX_HAND_SIZE];

} GameObject;

void PixelPoker_Init(GameObject *GameObject);
void PixelPoker_Update(GameObject *GameObject);
void PixelPoker_Render(GameObject *GameObject);
void PixelPoker_Close(GameObject *GameObject);

void CreateDeck(Deck& deck);
void DrawCard(Deck& source, Deck& target, int count = 1);

void RenderHand(SDL_Renderer *Renderer, Deck& hand);

std::map<CARD_SUIT, std::map<CARD_VALUE, std::string>> CardTextureMap;

int main()
{
    GameObject GameObject;

    PixelPoker_Init(&GameObject);

    while (GameObject.State != GAME_STATE_EXIT)
    {
        PixelPoker_Update(&GameObject);
        PixelPoker_Render(&GameObject);
    }

    PixelPoker_Close(&GameObject);

    return 0;
}

void PixelPoker_Init(GameObject *GameObject)
{
    srand((unsigned int)time(0));

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    // Create a window
    GameObject->GraphicsWindow = SDL_CreateWindow("PIXEL POKER", 0, 0, WINDOW_W_PIXELS, WINDOW_H_PIXELS, SDL_WINDOW_SHOWN);

    // Create a renderer
    GameObject->GraphicsRenderer = SDL_CreateRenderer(GameObject->GraphicsWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(GameObject->GraphicsRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Load background texture
    std::string bgImagePath = MEDIA_PATH + "bg.png";
    GameObject->BackgroundTexture = IMG_LoadTexture(GameObject->GraphicsRenderer, bgImagePath.c_str());

    // Load the coin texture
    std::string coinImagePath = MEDIA_PATH + "coin.png";
    GameObject->CoinTexture = IMG_LoadTexture(GameObject->GraphicsRenderer, coinImagePath.c_str());

    // Load the card textures
    std::map<CARD_VALUE, std::string> heartTextures;
    heartTextures.insert({ACE, "card_1_heart.png"});
    heartTextures.insert({TWO, "card_2_heart.png"});
    heartTextures.insert({THREE, "card_3_heart.png"});
    heartTextures.insert({FOUR, "card_4_heart.png"});
    heartTextures.insert({FIVE, "card_5_heart.png"});
    heartTextures.insert({SIX, "card_6_heart.png"});
    heartTextures.insert({SEVEN, "card_7_heart.png"});
    heartTextures.insert({EIGHT, "card_8_heart.png"});
    heartTextures.insert({NINE, "card_9_heart.png"});
    heartTextures.insert({TEN, "card_10_heart.png"});
    heartTextures.insert({JACK, "card_11_heart.png"});
    heartTextures.insert({QUEEN, "card_12_heart.png"});
    heartTextures.insert({KING, "card_13_heart.png"});
    CardTextureMap.insert({HEART, heartTextures});

    std::map<CARD_VALUE, std::string> diamondTextures;
    diamondTextures.insert({ACE, "card_1_diamond.png"});
    diamondTextures.insert({TWO, "card_2_diamond.png"});
    diamondTextures.insert({THREE, "card_3_diamond.png"});
    diamondTextures.insert({FOUR, "card_4_diamond.png"});
    diamondTextures.insert({FIVE, "card_5_diamond.png"});
    diamondTextures.insert({SIX, "card_6_diamond.png"});
    diamondTextures.insert({SEVEN, "card_7_diamond.png"});
    diamondTextures.insert({EIGHT, "card_8_diamond.png"});
    diamondTextures.insert({NINE, "card_9_diamond.png"});
    diamondTextures.insert({TEN, "card_10_diamond.png"});
    diamondTextures.insert({JACK, "card_11_diamond.png"});
    diamondTextures.insert({QUEEN, "card_12_diamond.png"});
    diamondTextures.insert({KING, "card_13_diamond.png"});
    CardTextureMap.insert({DIAMOND, diamondTextures});

    std::map<CARD_VALUE, std::string> cloverTextures;
    cloverTextures.insert({ACE, "card_1_clover.png"});
    cloverTextures.insert({TWO, "card_2_clover.png"});
    cloverTextures.insert({THREE, "card_3_clover.png"});
    cloverTextures.insert({FOUR, "card_4_clover.png"});
    cloverTextures.insert({FIVE, "card_5_clover.png"});
    cloverTextures.insert({SIX, "card_6_clover.png"});
    cloverTextures.insert({SEVEN, "card_7_clover.png"});
    cloverTextures.insert({EIGHT, "card_8_clover.png"});
    cloverTextures.insert({NINE, "card_9_clover.png"});
    cloverTextures.insert({TEN, "card_10_clover.png"});
    cloverTextures.insert({JACK, "card_11_clover.png"});
    cloverTextures.insert({QUEEN, "card_12_clover.png"});
    cloverTextures.insert({KING, "card_13_clover.png"});
    CardTextureMap.insert({CLUB, cloverTextures});

    std::map<CARD_VALUE, std::string> spadeTextures;
    spadeTextures.insert({ACE, "card_1_spade.png"});
    spadeTextures.insert({TWO, "card_2_spade.png"});
    spadeTextures.insert({THREE, "card_3_spade.png"});
    spadeTextures.insert({FOUR, "card_4_spade.png"});
    spadeTextures.insert({FIVE, "card_5_spade.png"});
    spadeTextures.insert({SIX, "card_6_spade.png"});
    spadeTextures.insert({SEVEN, "card_7_spade.png"});
    spadeTextures.insert({EIGHT, "card_8_spade.png"});
    spadeTextures.insert({NINE, "card_9_spade.png"});
    spadeTextures.insert({TEN, "card_10_spade.png"});
    spadeTextures.insert({JACK, "card_11_spade.png"});
    spadeTextures.insert({QUEEN, "card_12_spade.png"});
    spadeTextures.insert({KING, "card_13_spade.png"});
    CardTextureMap.insert({SPADE, spadeTextures});

    // GameObject->State = GAME_STATE_MENU;
    GameObject->State = GAME_STATE_PLAYING;
}

void PixelPoker_Update(GameObject *GameObject)
{
    SDL_Event event;

    switch (GameObject->State)
    {
    case GAME_STATE_PLAYING:
        // Create the deck if empty
        CreateDeck(GameObject->SourceDeck);
        
        // If player hand is empty, fill draw from the deck to fill it
        if (GameObject->PlayerHand.IsEmpty())
        {
            // DrawCard(GameObject->SourceDeck, GameObject->PlayerHand, MAX_HAND_SIZE);
            GameObject->SourceDeck.DrawCard(GameObject->PlayerHand, MAX_HAND_SIZE);
        }

        GameObject->CoinImageIndex++;

        break;

    default:
        break;
    }

    // User Input
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            GameObject->State = GAME_STATE_EXIT;
        }
        
        // TODO: mouse input

    }
}

void PixelPoker_Render(GameObject *GameObject)
{
    SDL_RenderClear(GameObject->GraphicsRenderer);

    // Render the background image
    SDL_RenderCopy(GameObject->GraphicsRenderer, GameObject->BackgroundTexture, NULL, NULL);

    // Render the player's hand
    RenderHand(GameObject->GraphicsRenderer, GameObject->PlayerHand);

    // Render selected cards
    SDL_SetRenderDrawBlendMode(GameObject->GraphicsRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(GameObject->GraphicsRenderer, 0xFF, 0x00, 0x00, 0x50);

    for (int i = 0; i < MAX_HAND_SIZE; i++)
    {
        if (GameObject->SelectedCards[i])
        {
            SDL_Rect selectionRect = {10, 10, 200, 200};
            SDL_RenderFillRect(GameObject->GraphicsRenderer, &selectionRect);
        }
    }

    // Render coin total
    // TODO: Really crude animation
    SDL_Rect coinSrcRect = {((GameObject->CoinImageIndex % 32) / 8) * COIN_W_PIXELS, 0, COIN_W_PIXELS, COIN_H_PIXELS};
    SDL_Rect coinDestRect = {10, 10, COIN_W_PIXELS * COIN_SCALING, COIN_H_PIXELS * COIN_SCALING};
    SDL_RenderCopy(GameObject->GraphicsRenderer, GameObject->CoinTexture, &coinSrcRect, &coinDestRect);

    SDL_RenderPresent(GameObject->GraphicsRenderer);

    SDL_Delay(1000 / 60);
}

void PixelPoker_Close(GameObject *GameObject)
{
    // TODO: destroy everything

    SDL_DestroyWindow(GameObject->GraphicsWindow);
    SDL_Quit();
}

void CreateDeck(Deck& deck)
{
    if (deck.IsEmpty())
    {
        deck.AddCard(Card(HEART, ACE));
        deck.AddCard(Card(HEART, TWO));
        deck.AddCard(Card(HEART, THREE));
        deck.AddCard(Card(HEART, FOUR));
        deck.AddCard(Card(HEART, FIVE));
        deck.AddCard(Card(HEART, SIX));
        deck.AddCard(Card(HEART, SEVEN));
        deck.AddCard(Card(HEART, EIGHT));
        deck.AddCard(Card(HEART, NINE));
        deck.AddCard(Card(HEART, TEN));
        deck.AddCard(Card(HEART, JACK));
        deck.AddCard(Card(HEART, QUEEN));
        deck.AddCard(Card(HEART, KING));
        deck.AddCard(Card(DIAMOND, ACE));
        deck.AddCard(Card(DIAMOND, TWO));
        deck.AddCard(Card(DIAMOND, THREE));
        deck.AddCard(Card(DIAMOND, FOUR));
        deck.AddCard(Card(DIAMOND, FIVE));
        deck.AddCard(Card(DIAMOND, SIX));
        deck.AddCard(Card(DIAMOND, SEVEN));
        deck.AddCard(Card(DIAMOND, EIGHT));
        deck.AddCard(Card(DIAMOND, NINE));
        deck.AddCard(Card(DIAMOND, TEN));
        deck.AddCard(Card(DIAMOND, JACK));
        deck.AddCard(Card(DIAMOND, QUEEN));
        deck.AddCard(Card(DIAMOND, KING));
        deck.AddCard(Card(CLUB, ACE));
        deck.AddCard(Card(CLUB, TWO));
        deck.AddCard(Card(CLUB, THREE));
        deck.AddCard(Card(CLUB, FOUR));
        deck.AddCard(Card(CLUB, FIVE));
        deck.AddCard(Card(CLUB, SIX));
        deck.AddCard(Card(CLUB, SEVEN));
        deck.AddCard(Card(CLUB, EIGHT));
        deck.AddCard(Card(CLUB, NINE));
        deck.AddCard(Card(CLUB, TEN));
        deck.AddCard(Card(CLUB, JACK));
        deck.AddCard(Card(CLUB, QUEEN));
        deck.AddCard(Card(CLUB, KING));
        deck.AddCard(Card(SPADE, ACE));
        deck.AddCard(Card(SPADE, TWO));
        deck.AddCard(Card(SPADE, THREE));
        deck.AddCard(Card(SPADE, FOUR));
        deck.AddCard(Card(SPADE, FIVE));
        deck.AddCard(Card(SPADE, SIX));
        deck.AddCard(Card(SPADE, SEVEN));
        deck.AddCard(Card(SPADE, EIGHT));
        deck.AddCard(Card(SPADE, NINE));
        deck.AddCard(Card(SPADE, TEN));
        deck.AddCard(Card(SPADE, JACK));
        deck.AddCard(Card(SPADE, QUEEN));
        deck.AddCard(Card(SPADE, KING));

        deck.Shuffle();
    }
}

void RenderHand(SDL_Renderer *Renderer, Deck& hand)
{
    for (int i = 0; i < hand.Size(); i++)
    {
        int offset_x = (WINDOW_W_PIXELS / 2) - ((MAX_HAND_SIZE * CARD_W_PIXELS) / 2) - (CARD_GAP_PIXELS * (MAX_HAND_SIZE - 1) / 2);
        int offset_y = WINDOW_H_PIXELS / 2 - CARD_H_PIXELS / 2;
        SDL_Rect r = {offset_x + (i * CARD_W_PIXELS) + (i * CARD_GAP_PIXELS), offset_y, CARD_W_PIXELS, CARD_H_PIXELS};
        
        Card c = hand.CardAt(i);
        
        std::map<CARD_VALUE, std::string> valueStrings = CardTextureMap.at(c.GetSuit());

        std::string texturePath = MEDIA_PATH + valueStrings.at(c.GetValue());

        // TODO: this is loading the texture on every iteration. That's bad.
        // Cache these textures as they are loaded or load them all up front
        SDL_Texture *t = IMG_LoadTexture(Renderer, texturePath.c_str());
        SDL_RenderCopy(Renderer, t, NULL, &r);
        SDL_DestroyTexture(t);
    }
}
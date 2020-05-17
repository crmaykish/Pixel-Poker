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
const int CARD_GAP_PIXELS = 8;

const int MAX_HAND_SIZE = 5;

typedef std::vector<Card> Deck;

typedef enum
{
    GAME_STATE_LOADING,
    GAME_STATE_MENU,
    GAME_STATE_PLAYING,
    GAME_STATE_FINISHED,
    GAME_STATE_EXIT
 } GameState;

typedef struct
{
    GameState State;

    SDL_Window *GraphicsWindow;
    SDL_Renderer *GraphicsRenderer;
    SDL_Texture *BackgroundTexture;

    Deck SourceDeck;
    Deck PlayerHand;
    Deck PlayerDiscard;
    
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
    GameObject->State = GAME_STATE_LOADING;

    srand((unsigned int)time(0));

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    // Create a window
    GameObject->GraphicsWindow = SDL_CreateWindow("PIXEL POKER", 0, 0, WINDOW_W_PIXELS, WINDOW_H_PIXELS, SDL_WINDOW_SHOWN);

    // Create a renderer
    GameObject->GraphicsRenderer = SDL_CreateRenderer(GameObject->GraphicsWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(GameObject->GraphicsRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Load background texture
    std::string bgImagePath = MEDIA_PATH + "bg.jpg";
    GameObject->BackgroundTexture = IMG_LoadTexture(GameObject->GraphicsRenderer, bgImagePath.c_str());

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
    case GAME_STATE_MENU:
        /* code */
        break;
    
    case GAME_STATE_PLAYING:
        // Create the deck if empty
        CreateDeck(GameObject->SourceDeck);
        
        // If player hands are empty, draw into them
        if (GameObject->PlayerHand.empty())
        {
            DrawCard(GameObject->SourceDeck, GameObject->PlayerHand, MAX_HAND_SIZE);
        }

        break;

    case GAME_STATE_FINISHED:
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
    if (deck.empty())
    {
        deck.push_back(Card(HEART, ACE));
        deck.push_back(Card(HEART, TWO));
        deck.push_back(Card(HEART, THREE));
        deck.push_back(Card(HEART, FOUR));
        deck.push_back(Card(HEART, FIVE));
        deck.push_back(Card(HEART, SIX));
        deck.push_back(Card(HEART, SEVEN));
        deck.push_back(Card(HEART, EIGHT));
        deck.push_back(Card(HEART, NINE));
        deck.push_back(Card(HEART, TEN));
        deck.push_back(Card(HEART, JACK));
        deck.push_back(Card(HEART, QUEEN));
        deck.push_back(Card(HEART, KING));
        deck.push_back(Card(DIAMOND, ACE));
        deck.push_back(Card(DIAMOND, TWO));
        deck.push_back(Card(DIAMOND, THREE));
        deck.push_back(Card(DIAMOND, FOUR));
        deck.push_back(Card(DIAMOND, FIVE));
        deck.push_back(Card(DIAMOND, SIX));
        deck.push_back(Card(DIAMOND, SEVEN));
        deck.push_back(Card(DIAMOND, EIGHT));
        deck.push_back(Card(DIAMOND, NINE));
        deck.push_back(Card(DIAMOND, TEN));
        deck.push_back(Card(DIAMOND, JACK));
        deck.push_back(Card(DIAMOND, QUEEN));
        deck.push_back(Card(DIAMOND, KING));
        deck.push_back(Card(CLUB, ACE));
        deck.push_back(Card(CLUB, TWO));
        deck.push_back(Card(CLUB, THREE));
        deck.push_back(Card(CLUB, FOUR));
        deck.push_back(Card(CLUB, FIVE));
        deck.push_back(Card(CLUB, SIX));
        deck.push_back(Card(CLUB, SEVEN));
        deck.push_back(Card(CLUB, EIGHT));
        deck.push_back(Card(CLUB, NINE));
        deck.push_back(Card(CLUB, TEN));
        deck.push_back(Card(CLUB, JACK));
        deck.push_back(Card(CLUB, QUEEN));
        deck.push_back(Card(CLUB, KING));
        deck.push_back(Card(SPADE, ACE));
        deck.push_back(Card(SPADE, TWO));
        deck.push_back(Card(SPADE, THREE));
        deck.push_back(Card(SPADE, FOUR));
        deck.push_back(Card(SPADE, FIVE));
        deck.push_back(Card(SPADE, SIX));
        deck.push_back(Card(SPADE, SEVEN));
        deck.push_back(Card(SPADE, EIGHT));
        deck.push_back(Card(SPADE, NINE));
        deck.push_back(Card(SPADE, TEN));
        deck.push_back(Card(SPADE, JACK));
        deck.push_back(Card(SPADE, QUEEN));
        deck.push_back(Card(SPADE, KING));

        std::random_shuffle(deck.begin(), deck.end());
    }
}

void DrawCard(Deck& source, Deck& target, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (!source.empty())
        {
            target.push_back(source.back());
            source.pop_back();
        }
    }
}

void RenderHand(SDL_Renderer *Renderer, Deck& hand)
{
    for (int i = 0; i < hand.size(); i++)
    {
        int offset_x = (WINDOW_W_PIXELS / 2) - ((MAX_HAND_SIZE * CARD_W_PIXELS) / 2) - (CARD_GAP_PIXELS * (MAX_HAND_SIZE - 1) / 2);
        int offset_y = WINDOW_H_PIXELS / 2 - CARD_H_PIXELS / 2;
        SDL_Rect r = {offset_x + (i * CARD_W_PIXELS) + (i * CARD_GAP_PIXELS), offset_y, CARD_W_PIXELS, CARD_H_PIXELS};
        
        Card c = hand.at(i);
        
        std::map<CARD_VALUE, std::string> valueStrings = CardTextureMap.at(c.GetSuit());

        std::string texturePath = MEDIA_PATH + valueStrings.at(c.GetValue());

        // TODO: this is loading the texture on every iteration. That's bad.
        // Cache these textures as they are loaded or load them all up front
        SDL_Texture *t = IMG_LoadTexture(Renderer, texturePath.c_str());
        SDL_RenderCopy(Renderer, t, NULL, &r);
        SDL_DestroyTexture(t);
    }
}
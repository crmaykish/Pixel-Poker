#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "card.h"

// CONSTANTS
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

const int DEAL_BUTTON_SCALING = 2;
const int DEAL_BUTTON_W_PIXELS = 320 * DEAL_BUTTON_SCALING;
const int DEAL_BUTTON_H_PIXELS = 64 * DEAL_BUTTON_SCALING;
const int DEAL_BUTTON_GAP = 6;

const int MAX_HAND_SIZE = 5;

const int offset_x = (WINDOW_W_PIXELS / 2) - ((MAX_HAND_SIZE * CARD_W_PIXELS) / 2) - (CARD_GAP_PIXELS * (MAX_HAND_SIZE - 1) / 2);
const int offset_y = WINDOW_H_PIXELS / 2 - CARD_H_PIXELS / 2;

const int deal_button_offset_x = WINDOW_W_PIXELS - DEAL_BUTTON_W_PIXELS - DEAL_BUTTON_GAP;
const int deal_button_offset_y = WINDOW_H_PIXELS - DEAL_BUTTON_H_PIXELS - DEAL_BUTTON_GAP;

const SDL_Rect DealButtonRect = {deal_button_offset_x, deal_button_offset_y, DEAL_BUTTON_W_PIXELS, DEAL_BUTTON_H_PIXELS};

// DEFINITIONS
typedef enum
{
    GAME_STATE_INIT,
    GAME_STATE_WAIT_FOR_BET,
    GAME_STATE_BET,
    GAME_STATE_WAIT_FOR_CARDS,
    GAME_STATE_DEAL,
    GAME_STATE_OVER,
    GAME_STATE_FINISHED,
    GAME_STATE_EXIT
 } GameState;

typedef struct
{
    // UI
    SDL_Window *GraphicsWindow;
    SDL_Renderer *GraphicsRenderer;
    bool SelectedCards[MAX_HAND_SIZE];
    std::vector<int> WinningCards;

    // Game Data
    Deck SourceDeck;
    Deck PlayerHand;
    Deck PlayerDiscard;

    // Game State
    GameState State;
    int lastClickX, lastClickY;
    bool ButtonPressed = false;
    int TotalCoins = 100;
    int LastBet = 10;
    int LastWinnings = 0;

} GameObject;

// FUNCTION PROTOTYPES
void PixelPoker_Init(GameObject *GameObject);
void PixelPoker_Update(GameObject *GameObject);
void PixelPoker_Render(GameObject *GameObject);
void PixelPoker_Close(GameObject *GameObject);

void CreateDeck(Deck& deck);
void DrawCard(Deck& source, Deck& target, int count = 1);

void RenderHand(SDL_Renderer *Renderer, Deck& hand);
void RenderCoins(SDL_Renderer *Renderer, int count);

void HandleInput(GameObject *GameObject);

int CheckWinnings(GameObject *GameObject);

// GLOBAL VARIABLES
std::map<CARD_SUIT, std::map<CARD_VALUE, std::string>> CardTextureMap;
SDL_Texture *BackgroundTexture;
SDL_Texture *CoinTexture;
SDL_Texture *DealButtonTexture;

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

    SDL_SetRenderDrawBlendMode(GameObject->GraphicsRenderer, SDL_BLENDMODE_BLEND);

    // Load background texture
    std::string bgImagePath = MEDIA_PATH + "bg.png";
    BackgroundTexture = IMG_LoadTexture(GameObject->GraphicsRenderer, bgImagePath.c_str());

    // Load the coin texture
    std::string coinImagePath = MEDIA_PATH + "coin.png";
    CoinTexture = IMG_LoadTexture(GameObject->GraphicsRenderer, coinImagePath.c_str());

    // Load the deal button texture
    std::string dealImagePath = MEDIA_PATH + "deal_button.png";
    DealButtonTexture = IMG_LoadTexture(GameObject->GraphicsRenderer, dealImagePath.c_str());

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

    GameObject->State = GAME_STATE_INIT;
}

void PixelPoker_Update(GameObject *GameObject)
{
    HandleInput(GameObject);

    switch (GameObject->State)
    {
    case GAME_STATE_INIT:
        std::cout << "NEW GAME" << std::endl;

        // Clear cards
        for (int i = 0; i < MAX_HAND_SIZE; i++)
        {
            GameObject->SelectedCards[i] = false;
            GameObject->WinningCards.clear();
        }

        // Create a shuffled source deck if its empty
        CreateDeck(GameObject->SourceDeck);
        
        // Discard player hand
        GameObject->PlayerHand.MoveTopCards(GameObject->PlayerDiscard, MAX_HAND_SIZE);

        // Deal cards to the player
        GameObject->SourceDeck.MoveTopCards(GameObject->PlayerHand, MAX_HAND_SIZE);
        
        GameObject->State = GAME_STATE_WAIT_FOR_BET;

        break;

    case GAME_STATE_WAIT_FOR_BET:

        if (GameObject->ButtonPressed)
        {
            GameObject->State = GAME_STATE_BET;
            GameObject->ButtonPressed = false;
        }

        break;

    case GAME_STATE_BET:

        GameObject->TotalCoins -= GameObject->LastBet;

        GameObject->State = GAME_STATE_WAIT_FOR_CARDS;

        break;

    case GAME_STATE_WAIT_FOR_CARDS:

        if (GameObject->ButtonPressed)
        {
            GameObject->State = GAME_STATE_DEAL;
            GameObject->ButtonPressed = false;
        }

        break;

    case GAME_STATE_DEAL:

        // replace selected cards with new ones
        for (int i = 0; i < MAX_HAND_SIZE; i++)
        {
            // TODO: if the source deck is empty, shuffle the discard pile back in
            if (GameObject->SourceDeck.IsEmpty())
            {
                GameObject->PlayerDiscard.MoveTopCards(GameObject->SourceDeck, GameObject->PlayerDiscard.Size());
                GameObject->SourceDeck.Shuffle();
            }

            if (GameObject->SelectedCards[i])
            {
                // discard from the player hand
                GameObject->PlayerHand.MoveCardAt(GameObject->PlayerDiscard, i);

                // draw a new card from the deck
                GameObject->SourceDeck.MoveTopCardTo(GameObject->PlayerHand, i);
            }

            GameObject->SelectedCards[i] = false;
        }

        std::cout << "Cards in draw pile: " << GameObject->SourceDeck.Size() << std::endl;

        GameObject->State = GAME_STATE_OVER;

        break;
    
    case GAME_STATE_OVER:

        std::cout << "GAME OVER | ";

        GameObject->LastWinnings = CheckWinnings(GameObject);

        if (GameObject->LastWinnings > 0)
        {
            std::cout << "WINNER" << std::endl;
            GameObject->TotalCoins += (GameObject->LastBet * GameObject->LastWinnings);
        }
        else
        {
            std::cout << "LOSER" << std::endl;
        }

        GameObject->State = GAME_STATE_FINISHED;

        break;
    case GAME_STATE_FINISHED:

        if (GameObject->ButtonPressed)
        {
            GameObject->State = GAME_STATE_INIT;
            GameObject->ButtonPressed = false;
        }

        break;
    default:
        break;
    }
    
}

void PixelPoker_Render(GameObject *GameObject)
{
    SDL_RenderClear(GameObject->GraphicsRenderer);

    // Render the background image
    SDL_RenderCopy(GameObject->GraphicsRenderer, BackgroundTexture, NULL, NULL);

    switch (GameObject->State)
    {
    case (GAME_STATE_INIT):
        break;
    case (GAME_STATE_WAIT_FOR_BET):
        // Render the deal button
        SDL_RenderCopy(GameObject->GraphicsRenderer, DealButtonTexture, NULL, &DealButtonRect);

        RenderCoins(GameObject->GraphicsRenderer, GameObject->TotalCoins);

        break;
    case (GAME_STATE_BET):
        break;
    case (GAME_STATE_WAIT_FOR_CARDS):
        // Render the deal button
        SDL_RenderCopy(GameObject->GraphicsRenderer, DealButtonTexture, NULL, &DealButtonRect);

        // Render the player's hand
        RenderHand(GameObject->GraphicsRenderer, GameObject->PlayerHand);

        // Render selected cards
        SDL_SetRenderDrawColor(GameObject->GraphicsRenderer, 0xFF, 0x00, 0x00, 0x50);

        for (int i = 0; i < MAX_HAND_SIZE; i++)
        {
            if (GameObject->SelectedCards[i])
            {
                SDL_Rect r = {offset_x + (i * CARD_W_PIXELS) + (i * CARD_GAP_PIXELS), offset_y, CARD_W_PIXELS, CARD_H_PIXELS};
                SDL_RenderFillRect(GameObject->GraphicsRenderer, &r);
            }
        }

        RenderCoins(GameObject->GraphicsRenderer, GameObject->TotalCoins);

        break;

    case (GAME_STATE_DEAL):
        break;
    case (GAME_STATE_FINISHED):
        // Render the deal button
        SDL_RenderCopy(GameObject->GraphicsRenderer, DealButtonTexture, NULL, &DealButtonRect);

        // Render the player's hand
        RenderHand(GameObject->GraphicsRenderer, GameObject->PlayerHand);

        // Highlight winning cards
        SDL_SetRenderDrawColor(GameObject->GraphicsRenderer, 0x00, 0xFF, 0x00, 0x50);

        for (int i = 0; i < GameObject->WinningCards.size(); i++)
        {
            int cardIndex = GameObject->WinningCards[i];

            SDL_Rect r = {offset_x + (cardIndex * CARD_W_PIXELS) + (cardIndex * CARD_GAP_PIXELS), offset_y, CARD_W_PIXELS, CARD_H_PIXELS};
            SDL_RenderFillRect(GameObject->GraphicsRenderer, &r);
        }

        RenderCoins(GameObject->GraphicsRenderer, GameObject->TotalCoins);

        break;
    }

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
        deck.AddNewCard(Card(HEART, ACE));
        deck.AddNewCard(Card(HEART, TWO));
        deck.AddNewCard(Card(HEART, THREE));
        deck.AddNewCard(Card(HEART, FOUR));
        deck.AddNewCard(Card(HEART, FIVE));
        deck.AddNewCard(Card(HEART, SIX));
        deck.AddNewCard(Card(HEART, SEVEN));
        deck.AddNewCard(Card(HEART, EIGHT));
        deck.AddNewCard(Card(HEART, NINE));
        deck.AddNewCard(Card(HEART, TEN));
        deck.AddNewCard(Card(HEART, JACK));
        deck.AddNewCard(Card(HEART, QUEEN));
        deck.AddNewCard(Card(HEART, KING));
        deck.AddNewCard(Card(DIAMOND, ACE));
        deck.AddNewCard(Card(DIAMOND, TWO));
        deck.AddNewCard(Card(DIAMOND, THREE));
        deck.AddNewCard(Card(DIAMOND, FOUR));
        deck.AddNewCard(Card(DIAMOND, FIVE));
        deck.AddNewCard(Card(DIAMOND, SIX));
        deck.AddNewCard(Card(DIAMOND, SEVEN));
        deck.AddNewCard(Card(DIAMOND, EIGHT));
        deck.AddNewCard(Card(DIAMOND, NINE));
        deck.AddNewCard(Card(DIAMOND, TEN));
        deck.AddNewCard(Card(DIAMOND, JACK));
        deck.AddNewCard(Card(DIAMOND, QUEEN));
        deck.AddNewCard(Card(DIAMOND, KING));
        deck.AddNewCard(Card(CLUB, ACE));
        deck.AddNewCard(Card(CLUB, TWO));
        deck.AddNewCard(Card(CLUB, THREE));
        deck.AddNewCard(Card(CLUB, FOUR));
        deck.AddNewCard(Card(CLUB, FIVE));
        deck.AddNewCard(Card(CLUB, SIX));
        deck.AddNewCard(Card(CLUB, SEVEN));
        deck.AddNewCard(Card(CLUB, EIGHT));
        deck.AddNewCard(Card(CLUB, NINE));
        deck.AddNewCard(Card(CLUB, TEN));
        deck.AddNewCard(Card(CLUB, JACK));
        deck.AddNewCard(Card(CLUB, QUEEN));
        deck.AddNewCard(Card(CLUB, KING));
        deck.AddNewCard(Card(SPADE, ACE));
        deck.AddNewCard(Card(SPADE, TWO));
        deck.AddNewCard(Card(SPADE, THREE));
        deck.AddNewCard(Card(SPADE, FOUR));
        deck.AddNewCard(Card(SPADE, FIVE));
        deck.AddNewCard(Card(SPADE, SIX));
        deck.AddNewCard(Card(SPADE, SEVEN));
        deck.AddNewCard(Card(SPADE, EIGHT));
        deck.AddNewCard(Card(SPADE, NINE));
        deck.AddNewCard(Card(SPADE, TEN));
        deck.AddNewCard(Card(SPADE, JACK));
        deck.AddNewCard(Card(SPADE, QUEEN));
        deck.AddNewCard(Card(SPADE, KING));

        deck.Shuffle();
    }
}

void RenderHand(SDL_Renderer *Renderer, Deck& hand)
{
    for (int i = 0; i < hand.Size(); i++)
    {
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

void RenderCoins(SDL_Renderer *Renderer, int count)
{
    // Render coin total
    SDL_Rect coinSrcRect = {0, 0, COIN_W_PIXELS, COIN_H_PIXELS};
    SDL_Rect coinDestRect = {10, 10, COIN_W_PIXELS * COIN_SCALING, COIN_H_PIXELS * COIN_SCALING};
    SDL_RenderCopy(Renderer, CoinTexture, &coinSrcRect, &coinDestRect);
}

void HandleInput(GameObject *GameObject)
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            GameObject->State = GAME_STATE_EXIT;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_GetMouseState(&GameObject->lastClickX, &GameObject->lastClickY);

            std::cout << GameObject->lastClickX << ", " << GameObject->lastClickY << std::endl;
        }
    }

    if (GameObject->lastClickX > 0 && GameObject->lastClickY > 0)
    {
        // Determine if any cards were clicked on
        for (int i = 0; i < MAX_HAND_SIZE; i++)
        {
            SDL_Rect r = {offset_x + (i * CARD_W_PIXELS) + (i * CARD_GAP_PIXELS), offset_y, CARD_W_PIXELS, CARD_H_PIXELS};

            if (GameObject->lastClickX > r.x && GameObject->lastClickX < r.x + r.w && GameObject->lastClickY > r.y && GameObject->lastClickY < r.y + r.h)
            {
                GameObject->SelectedCards[i] = !GameObject->SelectedCards[i];
            }
        }

        // Check if deal button was pressed
        if (GameObject->lastClickX > DealButtonRect.x && GameObject->lastClickX < DealButtonRect.x + DealButtonRect.w && GameObject->lastClickY > DealButtonRect.y && GameObject->lastClickY < DealButtonRect.y + DealButtonRect.h)
        {
            GameObject->ButtonPressed = true;
        }

        GameObject->lastClickX = 0;
        GameObject->lastClickY = 0;
    }
}

int CheckWinnings(GameObject *GameObject)
{
    const int LOSE = 0;
    const int JACKS_OR_BETTER = 1;
    const int TWO_PAIR = 2;
    const int THREE_OF_A_KIND = 3;
    const int STRAIGHT = 4;
    const int FLUSH = 6;
    const int FULL_HOUSE = 9;
    const int FOUR_OF_A_KIND = 25;
    const int STRAIGHT_FLUSH = 50;
    const int ROYAL_FLUSH = 250;

    // Royal Flush


    // Straight Flush


    // Four of a Kind

    
    // Full House

    
    // Flush


    // Straight


    // Three of a Kind


    // Two Pair
    GameObject->WinningCards = GameObject->PlayerHand.IsTwoPair();

    if (GameObject->WinningCards.size() > 0)
    {
        std::cout << "TWO PAIR" << std::endl;
        return TWO_PAIR;
    }

    // Jacks or Better
    GameObject->WinningCards = GameObject->PlayerHand.IsJacksOrBetter();

    if (GameObject->WinningCards.size() > 0)
    {
        std::cout << "ONE PAIR" << std::endl;
        return LOSE;
    }

    return LOSE;
}
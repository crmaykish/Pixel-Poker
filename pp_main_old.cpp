#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "pp_pixel_poker.h"



#include "pp_deck.h"
#include "pp_poker_hand.h"

// FUNCTION PROTOTYPES
void PixelPoker_Init(GameObject *GameObject);
void PixelPoker_Update(GameObject *GameObject);
void PixelPoker_Render(GameObject *GameObject);
void PixelPoker_Close(GameObject *GameObject);

void RenderHand(SDL_Renderer *Renderer, Deck& hand);
void RenderCoins(SDL_Renderer *Renderer, int count);

void RenderText(SDL_Renderer *Renderer, std::string Text, const SDL_Rect *Rect);

// GLOBAL VARIABLES
std::map<PlayingCardSuit, std::map<PlayingCardValue, std::string>> CardTextureMap;
SDL_Texture *BackgroundTexture;
SDL_Texture *CoinTexture;
SDL_Texture *ButtonTexture;
TTF_Font *Font;

// int main()
// {

    // New stuff
    


    // Old stuff
    // GameObject GameObject;

    // PixelPoker_Init(&GameObject);

    // while (GameObject.State != GAME_STATE_EXIT)
    // {
    //     PixelPoker_Update(&GameObject);
    //     PixelPoker_Render(&GameObject);
    // }

    // PixelPoker_Close(&GameObject);

    return 0;
// }

void PixelPoker_Init(GameObject *GameObject)
{
    

    

    

    // Load font
    

    // Load background texture
    std::string bgImagePath = MEDIA_PATH + "bg.png";
    BackgroundTexture = IMG_LoadTexture(GameObject->GraphicsRenderer, bgImagePath.c_str());

    // Load the coin texture
    std::string coinImagePath = MEDIA_PATH + "coin.png";
    CoinTexture = IMG_LoadTexture(GameObject->GraphicsRenderer, coinImagePath.c_str());

    // Load the deal button texture
    std::string dealImagePath = MEDIA_PATH + "deal_button.png";
    ButtonTexture = IMG_LoadTexture(GameObject->GraphicsRenderer, dealImagePath.c_str());

    // Load the card textures
    std::map<PlayingCardValue, std::string> heartTextures;
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

    std::map<PlayingCardValue, std::string> diamondTextures;
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

    std::map<PlayingCardValue, std::string> cloverTextures;
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

    std::map<PlayingCardValue, std::string> spadeTextures;
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
        
        GameObject->StatusText = "READY TO PLAY";
        GameObject->ButtonText = "BET 10";

        GameObject->State = GAME_STATE_WAIT_FOR_BET;

        break;

    case GAME_STATE_WAIT_FOR_BET:

        if (GameObject->ButtonPressed)
        {
            GameObject->StatusText = "SELECT CARDS TO HOLD";
            GameObject->ButtonText = "DRAW";

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

        // Keep only the selected cards
        for (int i = 0; i < MAX_HAND_SIZE; i++)
        {
            // If the source deck is empty, shuffle the discard pile back in
            if (GameObject->SourceDeck.Size() < MAX_HAND_SIZE)
            {
                GameObject->PlayerDiscard.MoveTopCards(GameObject->SourceDeck, GameObject->PlayerDiscard.Size());
                GameObject->SourceDeck.Shuffle();
            }

            if (!GameObject->SelectedCards[i])
            {
                // discard from the player hand
                GameObject->PlayerHand.MoveCardAt(GameObject->PlayerDiscard, i);

                // draw a new card from the deck
                GameObject->SourceDeck.MoveTopCardTo(GameObject->PlayerHand, i);
            }

            GameObject->SelectedCards[i] = false;
        }

        GameObject->State = GAME_STATE_OVER;

        break;
    
    case GAME_STATE_OVER:

        GameObject->LastWinnings = CheckWinnings(GameObject);

        if (GameObject->LastWinnings > 0)
        {
            int winnings = (GameObject->LastBet * GameObject->LastWinnings);
            GameObject->TotalCoins += winnings;
        }

        GameObject->ButtonText = "PLAY AGAIN";

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

    // Render the button
    SDL_RenderCopy(GameObject->GraphicsRenderer, ButtonTexture, NULL, &ButtonRect);

    // Render coin image
    RenderCoins(GameObject->GraphicsRenderer, GameObject->TotalCoins);

    // Render coin count
    RenderText(GameObject->GraphicsRenderer, std::to_string(GameObject->TotalCoins), &CoinMessageRect);

    // Render status message
    RenderText(GameObject->GraphicsRenderer, GameObject->StatusText, &StatusMessageRect);

    // Render button text
    RenderText(GameObject->GraphicsRenderer, GameObject->ButtonText, &ButtonRect);

    switch (GameObject->State)
    {
    case (GAME_STATE_INIT):
        break;
    case (GAME_STATE_WAIT_FOR_BET):
        break;
    case (GAME_STATE_BET):
        break;
    case (GAME_STATE_WAIT_FOR_CARDS):
        // Render the player's hand
        RenderHand(GameObject->GraphicsRenderer, GameObject->PlayerHand);

        // Highlight selected cards
        SDL_SetRenderDrawColor(GameObject->GraphicsRenderer, 0x00, 0x00, 0xFF, 0x50);

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
        // Render the player's hand
        RenderHand(GameObject->GraphicsRenderer, GameObject->PlayerHand);

        // Highlight winning cards
        SDL_SetRenderDrawColor(GameObject->GraphicsRenderer, 0x00, 0xFF, 0x00, 0x50);

        for (auto i : GameObject->WinningCards)
        {
            SDL_Rect r = {offset_x + (i * CARD_W_PIXELS) + (i * CARD_GAP_PIXELS), offset_y, CARD_W_PIXELS, CARD_H_PIXELS};
            SDL_RenderFillRect(GameObject->GraphicsRenderer, &r);
        }

        RenderCoins(GameObject->GraphicsRenderer, GameObject->TotalCoins);

        break;
    }

    SDL_RenderPresent(GameObject->GraphicsRenderer);

    SDL_Delay(1000 / 60);
}


void RenderHand(SDL_Renderer *Renderer, Deck& hand)
{
    for (int i = 0; i < hand.Size(); i++)
    {
        SDL_Rect r = {offset_x + (i * CARD_W_PIXELS) + (i * CARD_GAP_PIXELS), offset_y, CARD_W_PIXELS, CARD_H_PIXELS};
        
        PlayingCard c = hand.CardAt(i);
        
        std::map<PlayingCardValue, std::string> valueStrings = CardTextureMap.at(c.Suit);

        std::string texturePath = MEDIA_PATH + valueStrings.at(c.Value);

        // TODO: this is loading the texture on every iteration. That's bad.
        // Cache these textures as they are loaded or load them all up front
        SDL_Texture *t = IMG_LoadTexture(Renderer, texturePath.c_str());
        SDL_RenderCopy(Renderer, t, NULL, &r);
        SDL_DestroyTexture(t);
    }
}




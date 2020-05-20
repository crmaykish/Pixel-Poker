#include "pp_pixel_poker.h"
#include "pp_logger.h"

#include "commands/pp_command_bet.h"
#include "commands/pp_command_deal.h"
#include "commands/pp_command_card_clicked.h"
#include "commands/pp_command_update_coin_display.h"
#include "commands/pp_command_update_bet_button.h"
#include "commands/pp_command_update_deal_button.h"
#include "commands/pp_command_update_card.h"

void PixelPoker::Init()
{
    Log("Starting Pixel Poker...", LOG_INFO);

    // Set up game state
    game.Init();

    // Set up renderer
    renderer.Init();

    // Set up asset manager
    assetManager.SetRenderer(&renderer);

    // Set up the first scene
    scenes.push_back(Scene());
    Scene &s = scenes.at(0);

    int buttonW = 400;
    int buttonH = 120;
    int buttonOffset = 20;

    int cardGap = WINDOW_W_PIXELS / 120;
    int cardW = (WINDOW_W_PIXELS / 5) - cardGap - (cardGap / 5);
    int cardH = cardW * 1.42;

    // Background Image
    InterfaceStaticImage *background = new InterfaceStaticImage(&assetManager);
    background->SetRectangle(0, 0, WINDOW_W_PIXELS, WINDOW_H_PIXELS);
    background->SetTextureKey(ASSET_IMAGE_BG_0);
    s.AddInterfaceElement(background);

    // Coins Display
    InterfaceText *coinsText = new InterfaceText(&assetManager);
    coinsText->SetRectangle(buttonOffset, buttonOffset, buttonW, buttonH);
    coinsText->SetFontKey(ASSET_FONT_MONO_0);
    coinsText->SetUpdateCommand(new UpdateCoinDisplayCommand(&game, coinsText));
    s.AddInterfaceElement(coinsText);

    // Bet Button
    InterfaceButton *buttonBet = new InterfaceButton(&assetManager);
    buttonBet->SetRectangle(buttonOffset, WINDOW_H_PIXELS - buttonOffset - buttonH, buttonW, buttonH);
    buttonBet->SetDownTextureKey(ASSET_IMAGE_BG_0);
    buttonBet->SetUpTextureKey(ASSET_IMAGE_BTN_UP_0);
    buttonBet->SetFontKey(ASSET_FONT_MONO_0);
    buttonBet->SetText("BET 10");
    buttonBet->Enable();    // TODO: this should be controlled by an update command
    buttonBet->SetUpdateCommand(new UpdateBetButtonCommand(&game, buttonBet));
    buttonBet->SetClickedCommand(new BetCommand(&game));
    s.AddInterfaceElement(buttonBet);

    // Deal Button
    InterfaceButton *buttonDeal = new InterfaceButton(&assetManager);
    buttonDeal->SetRectangle(WINDOW_W_PIXELS - buttonOffset - buttonW, WINDOW_H_PIXELS - buttonOffset - buttonH, buttonW, buttonH);
    buttonDeal->SetDownTextureKey(ASSET_IMAGE_BG_0);
    buttonDeal->SetUpTextureKey(ASSET_IMAGE_BTN_UP_0);
    buttonDeal->SetFontKey(ASSET_FONT_MONO_0);
    buttonDeal->SetClickedCommand(new DealCommand(&game));
    buttonDeal->SetUpdateCommand(new UpdateDealButtonCommand(&game, buttonDeal));
    s.AddInterfaceElement(buttonDeal);

    // Poker Hand
    for (int i = 0; i < 5; i++)
    {
        InterfacePlayingCard *card = new InterfacePlayingCard(&assetManager);
        card->SetRectangle(cardGap + i * (cardGap + cardW), 200, cardW, cardH);
        card->SetIndexInHand(i);
        card->Enable();
        card->SetClickedCommand(new CardClickedCommand(&game, card));
        card->SetUpdateCommand(new UpdatePlayingCardCommand(&game, card));
        s.AddInterfaceElement(card);
    }
}

void PixelPoker::Run()
{
    // Handle user input
    renderer.HandleInput(game);

    // Update UI elements to respond to user input
    GetActiveScene().Update(game);

    // Update game state object
    game.Update();

    // clear the renderer
    // TODO: move this to scene?
    renderer.Clear();

    // Render the active scene
    GetActiveScene().Render(renderer);

    renderer.Present();

    renderer.Sleep();
}

void PixelPoker::Destroy()
{
    // TODO
}

bool PixelPoker::IsRunning()
{
    return (RunState == PP_RUNNING);
}

Scene &PixelPoker::GetActiveScene()
{
    return scenes.at(activeScene);
}
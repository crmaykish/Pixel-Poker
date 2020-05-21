#include "pp_pixel_poker.h"
#include "pp_logger.h"

#include "commands/pp_command_bet.h"
#include "commands/pp_command_deal.h"
#include "commands/pp_command_card_clicked.h"
#include "commands/pp_command_update_coin_display.h"
#include "commands/pp_command_update_bet_button.h"
#include "commands/pp_command_update_deal_button.h"
#include "commands/pp_command_update_messages.h"
#include "commands/pp_command_play_sound.h"

#include "SDL2/SDL_mixer.h"

void PixelPoker::Init()
{
    Log("Starting Pixel Poker...", LOG_INFO);

    // Set up game state
    game.Init();

    // Set up renderer
    renderer.Init();

    // Set up asset manager
    assetManager.SetRenderer(&renderer);

    sounds.Init();
    sounds.SetAssetManager(&assetManager);

    // Preload the sound effects
    // TODO: loading a sound from file and immediately playing fails the first time, preloading fixes it, figure out why
    assetManager.GetSound(ASSET_SOUND_WIN_0);
    assetManager.GetSound(ASSET_SOUND_LOSE_0);
    assetManager.GetSound(ASSET_SOUND_BUTTON_0);
    assetManager.GetSound(ASSET_SOUND_CARD_CLICK_0);

    // Register sound effect commands for winning and losing a hand
    game.RegisterWinCommand(new PlaySoundCommand(&sounds, ASSET_SOUND_WIN_0));
    game.RegisterLoseGameCommand(new PlaySoundCommand(&sounds, ASSET_SOUND_LOSE_0));

    // Set up the first scene
    scenes.push_back(Scene());
    Scene &s = scenes.at(0);

    int e_gap = WINDOW_W_PIXELS / 120;
    int cardW = (WINDOW_W_PIXELS / 5) - e_gap - (e_gap / 5);
    int cardH = cardW * 1.42;

    int buttonW = 400;
    int buttonH = 120;
    int buttonOffset = e_gap;

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

    // Messages Display
    InterfaceText *txtMessages = new InterfaceText(&assetManager);
    txtMessages->SetRectangle(WINDOW_W_PIXELS - buttonW * 1.5 - buttonOffset, buttonOffset, buttonW * 1.5, buttonH);
    txtMessages->SetFontKey(ASSET_FONT_MONO_0);
    txtMessages->SetUpdateCommand(new UpdateMessagesCommand(&game, txtMessages));
    s.AddInterfaceElement(txtMessages);

    PlaySoundCommand *btnClickSoundCommand = new PlaySoundCommand(&sounds, ASSET_SOUND_BUTTON_0);

    // Bet MAX Button
    InterfaceButton *btnBetMax = new InterfaceButton(&assetManager);
    btnBetMax->SetRectangle(buttonOffset, WINDOW_H_PIXELS - buttonOffset - buttonH, buttonW, buttonH);
    btnBetMax->SetDownTextureKey(ASSET_IMAGE_BG_0);
    btnBetMax->SetUpTextureKey(ASSET_IMAGE_BTN_UP_0);
    btnBetMax->SetFontKey(ASSET_FONT_MONO_0);
    btnBetMax->SetText("BET MAX");
    btnBetMax->Enable(); // TODO: this should be controlled by an update command
    btnBetMax->SetUpdateCommand(new UpdateBetButtonCommand(&game, btnBetMax, BET_MAX));
    btnBetMax->RegisterClickedCommand(new BetCommand(&game, &sounds, BET_MAX));
    btnBetMax->RegisterClickedCommand(btnClickSoundCommand);

    s.AddInterfaceElement(btnBetMax);

    // Bet 10 Button
    InterfaceButton *btnBetTen = new InterfaceButton(&assetManager);
    btnBetTen->SetRectangle(buttonOffset, WINDOW_H_PIXELS - buttonOffset - 2 * buttonH, buttonW, buttonH);
    btnBetTen->SetDownTextureKey(ASSET_IMAGE_BG_0);
    btnBetTen->SetUpTextureKey(ASSET_IMAGE_BTN_UP_0);
    btnBetTen->SetFontKey(ASSET_FONT_MONO_0);
    btnBetTen->SetText("BET 10");
    btnBetTen->Enable(); // TODO: this should be controlled by an update command
    btnBetTen->SetUpdateCommand(new UpdateBetButtonCommand(&game, btnBetTen, BET_TEN));
    btnBetTen->RegisterClickedCommand(new BetCommand(&game, &sounds, BET_TEN));
    btnBetTen->RegisterClickedCommand(btnClickSoundCommand);
    s.AddInterfaceElement(btnBetTen);

    // Bet 5 Button
    InterfaceButton *btnBetFive = new InterfaceButton(&assetManager);
    btnBetFive->SetRectangle(buttonOffset + buttonW, WINDOW_H_PIXELS - buttonOffset - buttonH, buttonW, buttonH);
    btnBetFive->SetDownTextureKey(ASSET_IMAGE_BG_0);
    btnBetFive->SetUpTextureKey(ASSET_IMAGE_BTN_UP_0);
    btnBetFive->SetFontKey(ASSET_FONT_MONO_0);
    btnBetFive->SetText("BET 5");
    btnBetFive->Enable(); // TODO: this should be controlled by an update command
    btnBetFive->SetUpdateCommand(new UpdateBetButtonCommand(&game, btnBetFive, BET_FIVE));
    btnBetFive->RegisterClickedCommand(new BetCommand(&game, &sounds, BET_FIVE));
    btnBetFive->RegisterClickedCommand(btnClickSoundCommand);
    s.AddInterfaceElement(btnBetFive);

    // Bet 1 Button
    InterfaceButton *btnBetOne = new InterfaceButton(&assetManager);
    btnBetOne->SetRectangle(buttonOffset + buttonW, WINDOW_H_PIXELS - buttonOffset - 2 * buttonH, buttonW, buttonH);
    btnBetOne->SetDownTextureKey(ASSET_IMAGE_BG_0);
    btnBetOne->SetUpTextureKey(ASSET_IMAGE_BTN_UP_0);
    btnBetOne->SetFontKey(ASSET_FONT_MONO_0);
    btnBetOne->SetText("BET 1");
    btnBetOne->Enable(); // TODO: this should be controlled by an update command
    btnBetOne->SetUpdateCommand(new UpdateBetButtonCommand(&game, btnBetOne, BET_ONE));
    btnBetOne->RegisterClickedCommand(new BetCommand(&game, &sounds, BET_ONE));
    btnBetOne->RegisterClickedCommand(btnClickSoundCommand);
    s.AddInterfaceElement(btnBetOne);

    // Deal Button
    InterfaceButton *buttonDeal = new InterfaceButton(&assetManager);
    buttonDeal->SetRectangle(WINDOW_W_PIXELS - buttonOffset - buttonW, WINDOW_H_PIXELS - buttonOffset - buttonH, buttonW, buttonH);
    buttonDeal->SetDownTextureKey(ASSET_IMAGE_BG_0);
    buttonDeal->SetUpTextureKey(ASSET_IMAGE_BTN_UP_0);
    buttonDeal->SetFontKey(ASSET_FONT_MONO_0);
    buttonDeal->RegisterClickedCommand(new DealCommand(&game));
    buttonDeal->SetUpdateCommand(new UpdateDealButtonCommand(&game, buttonDeal));
    buttonDeal->RegisterClickedCommand(btnClickSoundCommand);
    s.AddInterfaceElement(buttonDeal);

    PlaySoundCommand *cardClickSoundCommand = new PlaySoundCommand(&sounds, ASSET_SOUND_CARD_CLICK_0);

    // Poker Hand
    for (int i = 0; i < 5; i++)
    {
        InterfacePlayingCard *card = new InterfacePlayingCard(&assetManager);
        card->SetRectangle(e_gap + i * (e_gap + cardW), 200, cardW, cardH);
        card->SetIndexInHand(i);
        card->Enable();
        card->RegisterClickedCommand(new CardClickedCommand(&game, card));
        card->RegisterClickedCommand(cardClickSoundCommand);
        s.AddInterfaceElement(card);
    }
}

void PixelPoker::Run()
{
    // Handle user input
    input.HandleInput(game);

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
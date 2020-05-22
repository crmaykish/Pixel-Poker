#include "pp_pixel_poker.h"
#include "pp_logger.h"
#include "pp_settings.h"

#include "commands/pp_command_bet.h"
#include "commands/pp_command_deal.h"
#include "commands/pp_command_card_clicked.h"
#include "commands/pp_command_update_coin_display.h"
#include "commands/pp_command_update_bet_button.h"
#include "commands/pp_command_update_deal_button.h"
#include "commands/pp_command_update_messages.h"
#include "commands/pp_command_play_sound.h"
#include "commands/pp_command_quit.h"

#include "SDL2/SDL_mixer.h"

void PixelPoker::Init()
{
    Log("Starting Pixel Poker...", LOG_INFO);

    settings = LoadSettings();

    // Set up game state
    game.Init();

    // Set up renderer
    renderer.Init(settings);

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

    int e_gap = settings.Resolution.w / 60;

    int cardW = (settings.Resolution.w / 5) - e_gap - (e_gap / 5);
    // int cardH = cardW * 1.42;
    // TODO: set a max ratio on card w/h
    int cardH = (settings.Resolution.h - 5 * e_gap) / 2;

    int buttonW = (settings.Resolution.w - 2 * e_gap) / 3;
    int buttonH = (settings.Resolution.h - 2 * e_gap) / 6;

    Log(std::to_string(buttonW) + " by" + std::to_string(buttonH));

    // Background Image
    InterfaceStaticImage *background = new InterfaceStaticImage(&assetManager);
    background->SetRectangle(0, 0, settings.Resolution.w, settings.Resolution.h);
    background->SetTextureKey(ASSET_IMAGE_BG_0);
    s.AddInterfaceElement(background);

    // Coin Icon
    InterfaceStaticImage *coin = new InterfaceStaticImage(&assetManager);
    coin->SetRectangle(e_gap, e_gap, buttonH - 2 * e_gap, buttonH - 2 * e_gap);
    coin->SetTextureKey(ASSET_IMAGE_CHIP_0);
    s.AddInterfaceElement(coin);

    // Coin Text
    InterfaceText *coinsText = new InterfaceText(&assetManager);
    coinsText->SetRectangle(buttonH, e_gap, buttonH * 1.5 - 2 * e_gap, buttonH - 2 * e_gap);
    coinsText->SetFontKey(ASSET_FONT_MONO_0);
    coinsText->SetUpdateCommand(new UpdateCoinDisplayCommand(&game, coinsText));
    s.AddInterfaceElement(coinsText);

    // Messages Display
    InterfaceText *txtMessages = new InterfaceText(&assetManager);
    txtMessages->SetRectangle(buttonW + e_gap, e_gap, buttonW * 2 - buttonH / 2 - e_gap - buttonH / 2, buttonH - 2 * e_gap);
    txtMessages->SetFontKey(ASSET_FONT_MONO_0);
    txtMessages->SetUpdateCommand(new UpdateMessagesCommand(&game, txtMessages));
    s.AddInterfaceElement(txtMessages);

    PlaySoundCommand *btnClickSoundCommand = new PlaySoundCommand(&sounds, ASSET_SOUND_BUTTON_0);

    // Quit button
    InterfaceButton *btnQuit = new InterfaceButton(&assetManager);
    btnQuit->SetRectangle(settings.Resolution.w - buttonH + e_gap, e_gap, buttonH - 2 * e_gap, buttonH - 2 * e_gap);
    btnQuit->SetDownTextureKey(ASSET_IMAGE_BTN_DOWN_2);
    btnQuit->SetUpTextureKey(ASSET_IMAGE_BTN_UP_2);
    btnQuit->SetFontKey(ASSET_FONT_MONO_0);
    btnQuit->SetText("X");
    btnQuit->Enable(); // TODO: this should be controlled by an update command
    btnQuit->RegisterClickedCommand(btnClickSoundCommand);
    btnQuit->RegisterClickedCommand(new QuitCommand());
    s.AddInterfaceElement(btnQuit);

    // Bet MAX Button
    InterfaceButton *btnBetMax = new InterfaceButton(&assetManager);
    btnBetMax->SetRectangle(e_gap, settings.Resolution.h - e_gap - buttonH + e_gap, buttonW - e_gap, buttonH - e_gap);
    btnBetMax->SetDownTextureKey(ASSET_IMAGE_BTN_DOWN_0);
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
    btnBetTen->SetRectangle(e_gap, settings.Resolution.h - e_gap - 2 * buttonH + e_gap, buttonW - e_gap, buttonH - e_gap);
    btnBetTen->SetDownTextureKey(ASSET_IMAGE_BTN_DOWN_0);
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
    btnBetFive->SetRectangle(e_gap + buttonW, settings.Resolution.h - e_gap - buttonH + e_gap, buttonW - e_gap, buttonH - e_gap);
    btnBetFive->SetDownTextureKey(ASSET_IMAGE_BTN_DOWN_0);
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
    btnBetOne->SetRectangle(e_gap + buttonW, settings.Resolution.h - e_gap - 2 * buttonH + e_gap, buttonW - e_gap, buttonH - e_gap);
    btnBetOne->SetDownTextureKey(ASSET_IMAGE_BTN_DOWN_0);
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
    buttonDeal->SetRectangle(settings.Resolution.w - e_gap - buttonW, settings.Resolution.h - e_gap - 2 * buttonH + e_gap, buttonW, 2 * buttonH - e_gap);
    buttonDeal->SetDownTextureKey(ASSET_IMAGE_BTN_DOWN_1);
    buttonDeal->SetUpTextureKey(ASSET_IMAGE_BTN_UP_1);
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
        card->SetRectangle(e_gap + i * (e_gap + cardW), (settings.Resolution.h / 6) + e_gap, cardW, cardH);
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
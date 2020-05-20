#include "pp_pixel_poker.h"
#include "pp_logger.h"

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

    // TODO: instantiate a few commands in the game init instead of here
    // GameCommand *hello = new HelloCommand();

    // TODO: just have commands set flags instead of doing the work themselves
    // then let the main game update code do the work

    // TODO: create commands for updating UI elements as well? or just let that happen in Update()



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

    InterfaceText *coinsText = new InterfaceText(&assetManager);
    coinsText->SetRectangle(buttonOffset, buttonOffset, buttonW, buttonH);
    coinsText->SetFontKey(ASSET_FONT_MONO_0);

    // TODO: It seems circular and weird to set a command and pass a reference to a member of this object
    coinsText->SetUpdateCommand(new UpdateCoinTextCommand(&game, coinsText->GetText()));
    s.AddInterfaceElement(coinsText);

    // Bet Button
    InterfaceButton *buttonBet = new InterfaceButton(&assetManager);
    buttonBet->SetRectangle(buttonOffset, WINDOW_H_PIXELS - buttonOffset - buttonH, buttonW, buttonH);
    buttonBet->SetDownTextureKey(ASSET_IMAGE_BG_0);
    buttonBet->SetUpTextureKey(ASSET_IMAGE_BTN_UP_0);
    buttonBet->SetFontKey(ASSET_FONT_MONO_0);

    std::string *betString = new std::string("BET 10");

    buttonBet->SetUpdateCommand(new UpdateStaticTextCommand(&game, betString));

    buttonBet->SetClickedCommand(new BetCommand(&game));
    s.AddInterfaceElement(buttonBet);

    // Deal Button
    InterfaceButton *buttonDeal = new InterfaceButton(&assetManager);
    buttonDeal->SetRectangle(WINDOW_W_PIXELS - buttonOffset - buttonW, WINDOW_H_PIXELS - buttonOffset - buttonH, buttonW, buttonH);
    buttonDeal->SetDownTextureKey(ASSET_IMAGE_BG_0);
    buttonDeal->SetUpTextureKey(ASSET_IMAGE_BTN_UP_0);
    buttonDeal->SetFontKey(ASSET_FONT_MONO_0);
    buttonDeal->SetClickedCommand(new DealCommand(&game));
    buttonDeal->SetUpdateCommand(new UpdateDealButtonTextCommand(&game, buttonDeal->GetText()));
    s.AddInterfaceElement(buttonDeal);

    // Poker Hand
    for (int i = 0; i < 5; i++)
    {
        InterfacePlayingCard *card = new InterfacePlayingCard(&assetManager);
        card->SetRectangle(cardGap + i * (cardGap + cardW), 200, cardW, cardH);

        card->SetIndexInHand(i);

        CardClickedCommand *com = new CardClickedCommand(&game);
        com->SetCardIndex(i);

        card->SetClickedCommand(com);
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
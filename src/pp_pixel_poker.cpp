#include "pp_pixel_poker.h"

void PixelPoker::Init()
{
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

    int cardW = 120;
    int cardH = 200;
    int cardGap = 10;

    // Background Image
    InterfaceStaticImage *background = new InterfaceStaticImage();
    background->SetRect(0, 0, WINDOW_W_PIXELS, WINDOW_H_PIXELS);
    background->SetTexture(assetManager.GetTexture(TEXTURE_BG_0));
    
    s.AddInterfaceElement(background);

    InterfaceText *coinsText = new InterfaceText();
    coinsText->SetRect(buttonOffset, buttonOffset, buttonW, buttonH);
    coinsText->SetFont(assetManager.GetFont(FONT_UI_0));

    coinsText->SetUpdateCommand(new UpdateCoinTextCommand(coinsText->GetText()));
    s.AddInterfaceElement(coinsText);

    // Bet Button
    InterfaceButton *buttonBet = new InterfaceButton();
    buttonBet->SetRect(buttonOffset, WINDOW_H_PIXELS - buttonOffset - buttonH, buttonW, buttonH);
    buttonBet->SetTexturePressed(assetManager.GetTexture(TEXTURE_BG_0));
    buttonBet->SetTextureUnpressed(assetManager.GetTexture(BUTTON_UNPRESSED_0));
    buttonBet->SetFont(assetManager.GetFont(FONT_UI_0));
    buttonBet->SetText("BET");
    buttonBet->SetCommand(new BetCommand());
    s.AddInterfaceElement(buttonBet);

    // Deal Button
    InterfaceButton *buttonDeal = new InterfaceButton();
    buttonDeal->SetRect(WINDOW_W_PIXELS - buttonOffset - buttonW, WINDOW_H_PIXELS - buttonOffset - buttonH, buttonW, buttonH);
    buttonDeal->SetTexturePressed(assetManager.GetTexture(TEXTURE_BG_0));
    buttonDeal->SetTextureUnpressed(assetManager.GetTexture(BUTTON_UNPRESSED_0));
    buttonDeal->SetFont(assetManager.GetFont(FONT_UI_0));
    buttonDeal->SetText("DEAL");
    buttonDeal->SetCommand(new DealCommand());
    s.AddInterfaceElement(buttonDeal);

    // Poker Hand
    for (int i = 0; i < 5; i++)
    {
        InterfacePlayingCard *card = new InterfacePlayingCard();
        card->SetRect(i * (cardGap + cardW), 200, cardW, cardH);
        
        card->SetTexturePressed(assetManager.GetTexture(BUTTON_UNPRESSED_0));
        card->SetTextureUnpressed(assetManager.GetTexture(BUTTON_UNPRESSED_0));
        card->SetFont(assetManager.GetFont(FONT_UI_0));
        card->SetText("CARD");

        // I don't love passing this in here
        card->SetAssetManager(&assetManager);
        card->SetIndex(i);
        card->SetCommand(new CardClickedCommand(i));
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
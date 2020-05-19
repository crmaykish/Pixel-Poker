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

    int buttonW = 400;
    int buttonH = 120;
    int buttonOffset = 20;

    // Background Image
    InterfaceStaticImage *background = new InterfaceStaticImage();
    background->SetRect(0, 0, WINDOW_W_PIXELS, WINDOW_H_PIXELS);
    background->SetTexture(assetManager.GetTexture(TEXTURE_BG_0));
    
    s.AddInterfaceElement(background);

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
    GetActiveScene().Render(game, renderer);

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
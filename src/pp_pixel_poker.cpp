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

    GameCommand *hello = new HelloCommand();

    for (int i = 0; i < 4; i++)
    {
        InterfaceButton *bigButton = new InterfaceButton();
        bigButton->SetRect(10 + (i * 300), 10, 300, 100);
        bigButton->SetTexturePressed(assetManager.GetTexture(TEXTURE_BG_0));
        bigButton->SetTextureUnpressed(assetManager.GetTexture(BUTTON_UNPRESSED_0));
        bigButton->SetCommand(hello);

        s.AddInterfaceElement(bigButton);
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
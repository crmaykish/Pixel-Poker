#include <iostream>
#include "pp_pixel_poker.h"

int main()
{
    PixelPoker game = PixelPoker();

    std::cout << "Starting Pixel Poker..." << std::endl;

    game.Init();

    while (game.IsRunning())
    {
        game.Run();
    }

    game.Destroy();

    std::cout << "Pixel Poker stopped." << std::endl;

    return 0;
}
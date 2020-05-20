#include "pp_pixel_poker.h"

int main()
{
    PixelPoker game = PixelPoker();

    game.Init();

    while (game.IsRunning())
    {
        game.Run();
    }

    game.Destroy();

    return 0;
}
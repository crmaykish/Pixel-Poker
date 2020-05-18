#ifndef PP_PIXEL_POKER
#define PP_PIXEL_POKER

#include <vector>

#include "pp_game_state.h"
#include "pp_renderer.h"
#include "pp_scene.h"

/**
 * @brief Top-level Pixel Poker game object
 */
class PixelPoker
{
    private:
        GameState game;
        Renderer renderer;
        std::vector<Scene> scenes;
    public:
        void Init();
        void Run();
        void Destroy();
        bool IsRunning();
};

#endif
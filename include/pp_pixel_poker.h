#include "pp_game_state.h"
#include "pp_renderer.h"
#include "pp_interface.h"

/**
 * @brief Top-level Pixel Poker game object
 */
class PixelPoker
{
    private:
        Game game;
        Renderer renderer;
        std::vector<Scene> scenes;
    public:
        void Init();
        void Run();
        void Destroy();
};
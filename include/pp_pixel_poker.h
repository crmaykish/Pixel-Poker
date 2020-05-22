#ifndef PP_PIXEL_POKER
#define PP_PIXEL_POKER

#include <vector>

#include "pp_game_state.h"
#include "pp_renderer.h"
#include "pp_input.h"
#include "pp_asset_manager.h"
#include "pp_sound_player.h"
#include "pp_scene.h"

/**
 * @brief State of the Pixel Poker application
 */
enum PixelPokerRunState
{
    PP_RUNNING,
    PP_EXIT
};

/**
 * @brief Top-level Pixel Poker game object
 */
class PixelPoker
{
private:
    PixelPokerRunState RunState;
    Settings settings;
    GameState game;
    Renderer renderer;
    Input input;
    SoundPlayer sounds;
    AssetManager assetManager;
    std::vector<Scene> scenes;
    int activeScene;

    Scene &GetActiveScene();

public:
    void Init();
    void Run();
    void Destroy();
    bool IsRunning();
};

#endif
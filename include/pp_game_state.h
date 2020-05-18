#ifndef PP_GAME_STATE_H
#define PP_GAME_STATE_H

#include "pp_point.h"

struct GameStateObject
{
    Point LastClickedPosition;
};

class GameState
{
    public:
        GameStateObject State;

        void Init();
        void Update();
        void Destroy();
};

#endif

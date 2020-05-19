#ifndef PP_COMMAND_H
#define PP_COMMAND_H

#include <iostream>
#include "pp_game_state.h"

class GameCommand
{
    public:
        virtual void Execute(GameState &gameState) = 0;
};

class HelloCommand : public GameCommand
{
    public:
        void Execute(GameState &gameState)
        {
            std::cout << "HELLO" << std::endl;
        }
};

#endif
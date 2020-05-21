#ifndef PP_COMMAND_H
#define PP_COMMAND_H

#include <vector>
#include "pp_renderer.h"
#include "pp_sound_player.h"

class Command
{
public:
    virtual void Execute() = 0;
    
    static void HandleCommandList(std::vector<Command *> commands)
    {
        for (auto c : commands)
        {
            if (c != NULL)
            {
                c->Execute();
            }
        }
    }
};

class RenderCommand : public Command
{
protected:
    Renderer *Render;

public:
    RenderCommand(Renderer *render);
};

class SoundCommand : public Command
{
protected:
    SoundPlayer *Sounds;

public:
    SoundCommand(SoundPlayer *sounds);
};

#endif // PP_COMMAND_H

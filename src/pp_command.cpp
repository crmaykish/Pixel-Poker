#include "pp_command.h"

RenderCommand::RenderCommand(Renderer *render)
{
    Render = render;
}

SoundCommand::SoundCommand(SoundPlayer *sounds)
{
    Sounds = sounds;
}

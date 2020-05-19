#ifndef PP_SCENE_H
#define PP_SCENE_H

#include <vector>
#include "pp_interface.h"
#include "pp_game_state.h"

class Scene
{
private:
    std::vector<InterfaceElement*> ElementList;

public:
    void AddInterfaceElement(InterfaceElement *element)
    {
        ElementList.push_back(element);
    }

    void Update(GameState &game)
    {
        for (auto e : ElementList)
        {
            e->Update(game);
        }
    }

    void Render(GameState &game, Renderer &renderer)
    {
        for (auto e : ElementList)
        {
            e->Render(game, renderer);
        }
    }
};

#endif
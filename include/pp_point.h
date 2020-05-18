#ifndef PP_POINT_H
#define PP_POINT_H

#include <SDL2/SDL.h>

struct Point
{
    int position[2];
};

bool PointInRect(Point *p, SDL_Rect *rect)
{
    return (
        p->position[0] >= rect->x &&
        p->position[0] <= rect->x + rect->w &&
        p->position[1] >= rect->y &&
        p->position[1] <= rect->y + rect->h);
}

#endif

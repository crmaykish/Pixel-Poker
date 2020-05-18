#ifndef PP_POINT_H
#define PP_POINT_H

#include <SDL2/SDL.h>

struct Point
{
    int position[2];
};

bool PointInRect(Point *p, SDL_Rect *rect);

#endif

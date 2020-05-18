#include "pp_point.h"

bool PointInRect(Point *p, SDL_Rect *rect)
{
    return (
        p->position[0] >= rect->x &&
        p->position[0] <= rect->x + rect->w &&
        p->position[1] >= rect->y &&
        p->position[1] <= rect->y + rect->h);
}
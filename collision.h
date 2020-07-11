#pragma once
#include <SDL2/SDL.h>

class Collision
{
public:
    static bool AABB(const SDL_Rect& A, const SDL_Rect& B);
//    static bool AABB(const ColliderComponent& A, const ColliderComponent& B);
};

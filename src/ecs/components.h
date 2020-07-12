#pragma once
#include "../vector2d.h"
#include <vector>
#include "ecs.h"
#include <SDL2/SDL.h>

struct CTransform
{
    Vector2D position;
    Vector2D scale;
    int layer;
};

struct CTile
{
    std::vector<Entity> entities;
    bool bIsWalkable;
};

struct CSprite
{
    SDL_Texture* texture;
    SDL_Rect src;
    SDL_Rect dest;
};

struct CStats
{
    int health;
    int mana;
    int ki;
    int stamina;
    int speed;
};

struct CAIController
{
    bool bIsActive;
    bool bIsMoving;
    Vector2D targetPosition;
};

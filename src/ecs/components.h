#pragma once
#include "../vector3d.h"
#include "../vector2d.h"
#include <vector>
#include "ecs.h"
#include <SDL2/SDL.h>

struct CTransform
{
    std::shared_ptr<Entity> tile;
    Vector3D position;
    Vector2D scale;
    int layer;
    bool bIsDirty;

    CTransform()
    {
        scale.x = scale.y = 1;
        bIsDirty = false;
        layer = 0;
    }
    CTransform(Vector3D position_)
    {
        position = position_;
        scale.x = scale.y = 1;
        bIsDirty = true;
        layer = 0;
    }
    CTransform(Vector3D position_, std::shared_ptr<Entity> tile_)
    {
        tile = tile_;
        position = position_;
        scale.x = scale.y = 1;
        bIsDirty = true;
        layer = 0;
    }
};

struct CTile
{
    std::vector<std::shared_ptr<Entity>> entities;
    Vector2D position;
    bool bIsWalkable;
    float heightOffset;
};

struct CCreature
{

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
    Vector3D moveDirection;
};

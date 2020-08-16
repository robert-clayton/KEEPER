#pragma once
#include "../math/float3.h"
#include "../math/float2.h"
#include "../math/int2.h"
#include <vector>
#include "ecs.h"
#include <SDL2/SDL.h>

struct CTransform
{
    Entity tile;
    float3 position;
    float2 scale;
    int layer;
    bool bIsDirty;

    CTransform()
    {
        scale.x = scale.y = 1;
        bIsDirty = false;
        layer = 0;
    }
    CTransform(float3 position_)
    {
        position = position_;
        scale.x = scale.y = 1;
        bIsDirty = true;
        layer = 0;
    }
    CTransform(float3 position_, Entity tile_)
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
    std::set<Entity> entities;
    int2 position;
    bool bIsWalkable;
    float cost;

    CTile()
    {
        this->bIsWalkable = true;
        this->cost = 1;
    }

    CTile(int2 position)
    {
        this->position = position;
        this->bIsWalkable = true;
        this->cost = 1;
    }

    CTile(std::set<Entity> entities, int2 position, bool bIsWalkable, float cost)
    {
        this->entities = entities;
        this->position = position;
        this->bIsWalkable = bIsWalkable;
        this->cost = cost;
    }

    CTile(int2 position, bool bIsWalkable, float cost)
    {
        this->position = position;
        this->bIsWalkable = bIsWalkable;
        this->cost = cost;
    }
};

struct CCreature
{

};

struct CSprite
{
    SDL_Texture* texture;
    SDL_Rect src;
    SDL_Rect dest;
    float2 renderOffset;
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
    float3 moveDirection;
};

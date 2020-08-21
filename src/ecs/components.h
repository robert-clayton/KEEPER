#pragma once
#include "../math/float3.h"
#include "../math/float2.h"
#include "../math/int2.h"
#include <vector>
#include "ecs.h"
#include <SDL.h>

struct CTransform
{
    float3 position;
    float2 scale;
    int layer;
    bool bIsDirty;

    CTransform()
    {
        this->position = float3();
        this->scale.x = scale.y = 1;
        this->layer = 0;
        this->bIsDirty = false;
    }
    CTransform(float3 position)
    {
        this->position = position;
        this->scale.x = scale.y = 1;
        this->layer = 0;
        this->bIsDirty = true;
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
    int2 renderOffset;
    int renderLayer;

    CSprite()
    {
        this->texture = nullptr;
        this->src = {};
        this->dest = {};
        this->renderOffset = int2();
        this->renderLayer = 0;
    }

    CSprite(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, int2 renderOffset = int2(), int renderLayer = 0)
    {
        this->texture = texture;
        this->src = src;
        this->dest = dest;
        this->renderOffset = renderOffset - int2(dest.w / 2, dest.h);
        this->renderLayer = renderLayer;
    }
};

struct CStats
{
    int health;
    int mana;
    int ki;
    int stamina;
    int speed;

    CStats()
    {
        this->health = 5;
        this->mana = 0;
        this->ki = 0;
        this->stamina = 5;
        this->speed = 150;
    }
};

struct CAIController
{
    bool bIsActive;
    bool bIsMoving;
    float3 moveDirection;
    Entity tile;
    std::vector<Entity> movePath;

    CAIController(bool bIsActive=true)
    {
        this->bIsActive = bIsActive;
        this->bIsMoving = false;
        this->moveDirection = float3();
        this->tile = 1;
        this->movePath = std::vector<Entity>();
    }

    CAIController(Entity tile)
    {
        this->bIsActive = true;
        this->bIsMoving = false;
        this->moveDirection = float3();
        this->tile = tile;
        this->movePath = std::vector<Entity>();
    }
};

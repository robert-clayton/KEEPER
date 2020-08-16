#pragma once
#include "../vector3d.h"
#include "../vector2d.h"
#include <vector>
#include "ecs.h"
#include <SDL2/SDL.h>

struct CTransform
{
    Entity tile;
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
    CTransform(Vector3D position_, Entity tile_)
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
    Vector2D position;
    bool bIsWalkable;
    float cost;

    CTile()
    {
        bIsWalkable = true;
        cost = 1;
    }

    CTile(Vector2D position)
    {
        this->position = position;
        bIsWalkable = true;
        cost = 1;
    }

    CTile(std::set<Entity> entities, Vector2D position, bool bIsWalkable, float cost)
    {
        this->entities = entities;
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
    Vector2D renderOffset;
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

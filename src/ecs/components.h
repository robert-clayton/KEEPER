#pragma once
#include "../math/float3.h"
#include "../math/float2.h"
#include "../math/int2.h"
#include <vector>
#include "ecs.h"
#include <SDL.h>
#include <map>
#include <bitset>

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
    // TODO: Hold creature state variables
    // face direction
};

struct CSprite
{

    std::unordered_map<int, SDL_Rect> sprites;
    int activeSpriteKey;
    SDL_Texture* sheet;
    SDL_Rect dest;
    int2 renderOffset;
    int renderLayer;
    bool animated;

    CSprite()
    {
        this->sprites = std::unordered_map<int, SDL_Rect>();
        this->activeSpriteKey = 0;
        this->sheet = nullptr;
        this->dest = {};
        this->renderOffset = int2();
        this->renderLayer = 0;
        this->animated = false;
    }

    CSprite(SDL_Texture* sheet, SDL_Rect size, SDL_Rect dest, int2 renderOffset = int2(), int renderLayer = 0)
    {
        this->sprites = std::unordered_map<int, SDL_Rect>();
        this->activeSpriteKey = 1;
        this->sheet = sheet;
        this->dest = dest;
        this->renderOffset = renderOffset - int2(dest.w / 2, dest.h);
        this->renderLayer = renderLayer;
        this->animated = false;

        this->sprites[0] = SDL_Rect{ size.w, 0, size.w, size.h }; // visual down
        this->sprites[1] = size; // visual down left
        this->sprites[2] = SDL_Rect{ size.w * 2, 0, size.w, size.h }; // visual left
        this->sprites[3] = SDL_Rect{ size.w * 3, 0, size.w, size.h }; // visual up right
        this->sprites[4] = SDL_Rect{ size.w * 4, 0, size.w, size.h }; // visual up
        this->sprites[5] = SDL_Rect{ size.w * 3, 0, size.w, size.h }; // visual up left
        this->sprites[6] = SDL_Rect{ size.w * 2, 0, size.w, size.h }; // visual right
        this->sprites[7] = size; // visual down right
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
        this->speed = 1500;
    }
};

struct CAIController
{
    bool bIsActive;
    bool bIsMoving;
    float3 moveDirection;
    Entity tile;
    int direction;
    std::vector<Entity> movePath;

    CAIController(bool bIsActive=true)
    {
        this->bIsActive = bIsActive;
        this->bIsMoving = false;
        this->moveDirection = float3();
        this->tile = 1;
        this->direction = 0;
        this->movePath = std::vector<Entity>();
    }

    CAIController(Entity tile)
    {
        this->bIsActive = true;
        this->bIsMoving = false;
        this->moveDirection = float3();
        this->tile = tile;
        this->direction = 0;
        this->movePath = std::vector<Entity>();
    }
};

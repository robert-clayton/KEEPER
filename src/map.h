#pragma once
#include <vector>
#include <SDL.h>
#include "ecs/ecs.h"
#include <map>

class float3;
class int2;

struct Node
{
    Entity* tile;
    Entity* prevTile;
    float gCost; //Exact
    float hCost; //Heuristic
    float fCost; //g + h -> used

    Node()
    {
        tile = prevTile = nullptr;
        gCost = hCost = fCost = FLT_MAX;
    }
};

class Map
{
public:
    std::vector<SDL_Texture*> textures;
    Entity map[25][25];

    Map();
    ~Map();

    void LoadMap(int arr[25][25]);
    Entity GetRandomTile();
    float3 GetRandomTilePos();
    float3 TileToWorldSpace(const int& x, const int& y);
    float3 TileToWorldSpace(const int2& position);
    int2 WorldToTileSpace(const float3& position);
    bool TileAt(Entity& tile, const float3& position);
    bool TileAt(Entity& tile, const int2& position);
    bool FindPath(std::vector<Entity>& Path, const Entity& start, const Entity& dest);

private:
    std::vector<Entity> MakePath(const std::map<Entity, Entity>& cameFrom, const Entity& dest);
    void PrintNodes(const std::map<Entity, float>& cost, const int2& current, const int2& start, const int2& dest);
};

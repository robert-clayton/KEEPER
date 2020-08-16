#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include "ecs/ecs.h"

class float3;

struct Node
{
    Entity* tile;
    Entity* prevTile;
    float gCost; //Exact
    float hCost; //Heuristic
    float fCost; //g + h -> used

    Node()
    {
        gCost = hCost = fCost = __FLT_MAX__;
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
    void DrawMap();
    Entity GetRandomTile();
    float3 GetRandomTilePos();
    float3 TileToWorldSpace(const int& x, const int& y);
    float3 TileToWorldSpace(const float3& position);
    int2 WorldToTileSpace(const float3& position);
    bool TileAt(Entity& tile, const float3& position);
    bool FindPath(std::vector<Entity>& Path, Entity& start, Entity& dest);

private:
    std::vector<Entity> MakePath(std::array<std::array<Node, 25>, 25> allMap, Entity& dest);
};

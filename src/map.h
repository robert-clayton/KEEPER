#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include "ecs/ecs.h"

class Vector3D;

class Map
{
public:
    static int heightOffset;
    std::vector<SDL_Texture*> textures;
    std::shared_ptr<Entity> map[25][25];

    Map();
    ~Map();

    void LoadMap(int arr[25][25]);
    void DrawMap();
    std::shared_ptr<Entity> GetRandomTile();
    Vector3D GetRandomTilePos();
    Vector3D TileToWorldSpace(const int& x, const int& y);
    Vector3D TileToWorldSpace(const Vector3D& position);
    Vector2D WorldToTileSpace(const Vector3D& position);
    std::shared_ptr<Entity> TileAt(const Vector3D& position);
};

#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include "ecs/ecs.h"

class Map
{
public:
    Map();
    ~Map();

    void LoadMap(int arr[80][25]);
    void DrawMap();
    class Vector3D GetRandomTilePos();
    static class Vector3D TileToWorldSpace(const int& x, const int& y);
    static class Vector3D TileToWorldSpace(const class Vector3D& position);
    static class Vector3D WorldToTileSpace(const class Vector3D& position);
private:
    static int heightOffset;
    std::vector<SDL_Texture*> textures;
    Entity map[80][25];
};

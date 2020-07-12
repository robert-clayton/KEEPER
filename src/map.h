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
    class Vector2D GetRandomTilePos();
    static class Vector2D TileToWorldSpace(const int& x, const int& y);
    static class Vector2D TileToWorldSpace(const class Vector2D& position);
    static class Vector2D WorldToTileSpace(const class Vector2D& position);
private:
    std::vector<SDL_Texture*> textures;
    Entity map[80][25];
};

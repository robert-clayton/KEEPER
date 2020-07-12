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
    Vector2D GetRandomTilePos();
private:
    std::vector<SDL_Texture*> textures;
    Entity map[80][25];
};

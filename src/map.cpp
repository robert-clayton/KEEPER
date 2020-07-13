#include "map.h"
#include "game.h"
#include <random>
#include "vector3d.h"

extern Coordinator coordinator;

int Map::heightOffset;

int lvl1[25][25] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Map::Map()
{
    textures.emplace_back(Game::sRenderer->LoadTexture("tile_water.png"));
    textures.emplace_back(Game::sRenderer->LoadTexture("tile_sand.png"));

    LoadMap(lvl1);
}

Map::~Map()
{
    for (SDL_Texture* texture : textures)
    {
        SDL_DestroyTexture(texture);
    }
}

void Map::LoadMap(int arr[80][25])
{
    Entity tile;
    SDL_Rect srcRect = SDL_Rect{.x=50, .y=50, .w=500, .h=500};
    SDL_Rect destRect = SDL_Rect{.w=80, .h=80};
    heightOffset = destRect.h / 2;
    for (int row = 0; row < 25; row++)
    {
        for (int col = 0; col < 25; col++)
        {
            tile = coordinator.CreateEntity();
            map[row][col] = std::make_shared<Entity>(tile);
            coordinator.AddComponent(tile, CTile{.position = Vector2D(row, col), .bIsWalkable = true, .heightOffset = 40});
            coordinator.AddComponent(tile, CTransform(TileToWorldSpace(row, col), std::make_shared<Entity>(tile)));
            coordinator.AddComponent(tile, CSprite{
                            .texture = textures.at(arr[row][col]),
                            .src = srcRect,
                            .dest = destRect,
                        });
        }
    }
}

std::shared_ptr<Entity> Map::GetRandomTile()
{
    std::uniform_int_distribution<int> randX(0, 24);
    std::uniform_int_distribution<int> randY(0, 24);
    return map[randX(Game::generator)][randY(Game::generator)];
}

Vector3D Map::GetRandomTilePos()
{
    std::uniform_int_distribution<int> randX(0, 24);
    std::uniform_int_distribution<int> randY(0, 24);
    Vector3D pos = coordinator.GetComponent<CTransform>(*map[randX(Game::generator)][randY(Game::generator)]).position;
    return Vector3D(pos.x, pos.y, 0);
}

Vector3D Map::TileToWorldSpace(const int& x, const int& y)
{
    return Vector3D((x - y) * 40, (y + x) * 20, 0);
}

Vector3D Map::TileToWorldSpace(const Vector3D& position)
{
    return TileToWorldSpace(position.x, position.y);
}

Vector2D Map::WorldToTileSpace(const Vector3D& position)
{
    return Vector2D(
                (int)((position.x / 40 + position.y / 20) / 2),
                (int)(position.y / 20 - (position.x / 40 + position.y / 20) / 2)
                );
}

std::shared_ptr<Entity> Map::TileAt(const Vector3D& position)
{
    Vector2D location = WorldToTileSpace(position);
    if ((int)location.x >= 0 && (int)location.x < 25 && (int)location.y >= 0 && (int)location.y < 25)
        return map[(int)location.x][(int)location.y];
    else
        return nullptr;
}

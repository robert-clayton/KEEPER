#include "map.h"
#include "game.h"
#include <random>
#include <array>
#include "math/float3.h"
#include "math/int2.h"
#include <stack>
#include <sstream>

extern Coordinator coordinator;

int lvl1[25][25] = {
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
//    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
//    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
//    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
//    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
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
        SDL_DestroyTexture(texture);
}

void Map::LoadMap(int arr[25][25])
{
    Entity tile;
    SDL_Rect srcRect = SDL_Rect{50, 50, 500, 500};
    SDL_Rect destRect = SDL_Rect{0, 0, 80, 80};
    int2 renderOffset = int2(0, 60);
    for (int row = 0; row < 14; row++)
    {
        for (int col = 0; col < 25; col++)
        {
            tile = coordinator.CreateEntity();
            map[row][col] = tile;
            coordinator.AddComponent(tile, CTile(int2(row, col), true, 1 + 2 * (bool)arr[row][col]));
            coordinator.AddComponent(tile, CTransform(
                TileToWorldSpace(row, col) 
                - float3(0.0f,0.0f,arr[row][col] * 15.0f * Game::GetRandomScalar())
            ));
            coordinator.AddComponent(tile, CSprite(
                textures.at(arr[row][col]),
                srcRect, destRect, renderOffset, 0
            ));
        }
    }
}

Entity Map::GetRandomTile()
{
    std::uniform_int_distribution<int> randX(0, 13);
    std::uniform_int_distribution<int> randY(0, 24);
    return map[randX(Game::generator)][randY(Game::generator)];
}

float3 Map::GetRandomTilePos()
{
    std::uniform_int_distribution<int> randX(0, 13);
    std::uniform_int_distribution<int> randY(0, 24);
    float3 pos = coordinator.GetComponent<CTransform>(map[randX(Game::generator)][randY(Game::generator)]).position;
    return float3(pos.x, pos.y, 0);
}

float3 Map::TileToWorldSpace(const int& x, const int& y)
{
    return float3((y - x) * 40.0f, (y + x) * 20.0f, 0.0f);
}

float3 Map::TileToWorldSpace(const int2& position)
{
    return TileToWorldSpace(position.x, position.y);
}

int2 Map::WorldToTileSpace(const float3& position)
{
    //TODO: Make this not as dirty
    float3 newPos = position + float2(0,20.0f);
    return int2(
        (int)((newPos.y / 20 - newPos.x / 40) / 2),
        (int)(newPos.y / 20 - (newPos.y / 20 - newPos.x / 40) / 2)
        );
}

bool Map::TileAt(Entity& tile, const float3& position)
{
    int2 location = WorldToTileSpace(position);
    if (location.x >= 0 && location.x < 14 && location.y >= 0 && location.y < 25)
    {
        tile = map[location.x][location.y];
        return true;
    }
    return false;
}

bool Map::TileAt(Entity& tile, const int2& position)
{
    if (position.x >= 0 && position.x < 14 && position.y >= 0 && position.y < 25)
    {
        tile = map[position.x][position.y];
        return true;
    }
    return false;
}

bool Map::FindPath(std::vector<Entity>& Path, const Entity& start, const Entity& dest)
{
    std::map<Entity, Entity> cameFrom;
    std::map<Entity, float> gCost{ {start, 0.0f} };
    std::map<Entity, float> fCost{ {start, 0.0f} };
    auto cmp = [&fCost](Entity a, Entity b) { return fCost.at(a) < fCost.at(b); };
    std::set<Entity, decltype(cmp)> openSet{ { start }, cmp };

    Entity current;
    int2 curTilePos;
    int2 destTilePos = coordinator.GetComponent<CTile>(dest).position;
    Entity* neighbor;
    CTile* neighborTile;
    std::set<Entity>::iterator iter;
    float gCostTemp = 0.0f;
    while (!openSet.empty())
    {
        iter = openSet.begin();
        if (*iter == dest) {
            Path = MakePath(cameFrom, dest);
            return true;
        }
        current = *iter;
        openSet.erase(iter);
        curTilePos = coordinator.GetComponent<CTile>(current).position;
        for (int x = -1; x <= 1; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                if (curTilePos.x + x < 0 || curTilePos.x + x > 13 || curTilePos.y + y < 0 || curTilePos.y + y > 24)
                    continue;
                neighbor = &map[curTilePos.x + x][curTilePos.y + y];
                neighborTile = &coordinator.GetComponent<CTile>(*neighbor);
                if (!neighborTile->bIsWalkable)
                    continue;
                gCostTemp = gCost[current] + neighborTile->cost;
                if (!gCost.count(*neighbor) || gCostTemp < gCost[*neighbor])
                {
                    cameFrom[*neighbor] = current;
                    gCost[*neighbor] = gCostTemp;
                    fCost[*neighbor] = gCost[*neighbor] + neighborTile->position.DistanceTo(destTilePos);
                    if (!openSet.count(*neighbor))
                        openSet.emplace(*neighbor);
                }
            }
        }
    }
    return false;
}

std::vector<Entity> Map::MakePath(const std::map<Entity, Entity>& cameFrom, const Entity& dest)
{
    Entity current = dest;
    std::vector<Entity> path{ dest };
    while (cameFrom.count(current))
    {
        current = cameFrom.at(current);
        path.emplace(path.begin(), current);
    }
    return path;
}

void Map::PrintNodes(const std::map<Entity, float>& gCost, const int2& current, const int2& start, const int2& dest)
{
    std::ostringstream oss;
    oss << "\n";
    for (int x = 0; x < 14; x++)
    {
        for (int y = 0; y < 25; y++)
        {
            if (int2(x, y) == start)
                oss << "S";
            else if (int2(x, y) == dest)
                oss << "D";
            else if (!gCost.count(map[x][y]))
                oss << ",";
            else
                oss << (int)gCost.at(map[x][y]);
            if (int2(x, y) == current)
                oss << "X";
            oss << "\t";
        }
        oss << "\n";
    }
    SDL_Log("%s", oss.str().c_str());
}


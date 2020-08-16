#include "map.h"
#include "game.h"
#include <random>
#include "math/float3.h"
#include "stack"

extern Coordinator coordinator;

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

void Map::LoadMap(int arr[25][25])
{
    Entity tile;
    SDL_Rect srcRect = SDL_Rect{.x=50, .y=50, .w=500, .h=500};
    SDL_Rect destRect = SDL_Rect{.w=80, .h=80};
    for (int row = 0; row < 25; row++)
    {
        for (int col = 0; col < 25; col++)
        {
            tile = coordinator.CreateEntity();
            map[row][col] = tile;
            coordinator.AddComponent(tile, CTile(int2(row, col)));
            coordinator.AddComponent(tile, CTransform(TileToWorldSpace(row, col), tile));
            coordinator.AddComponent(tile, CSprite{
                            .texture = textures.at(arr[row][col]),
                            .src = srcRect,
                            .dest = destRect,
                            .renderOffset = float2(0,40),
                        });
        }
    }
}

Entity Map::GetRandomTile()
{
    std::uniform_int_distribution<int> randX(0, 24);
    std::uniform_int_distribution<int> randY(0, 24);
    return map[randX(Game::generator)][randY(Game::generator)];
}

float3 Map::GetRandomTilePos()
{
    std::uniform_int_distribution<int> randX(0, 24);
    std::uniform_int_distribution<int> randY(0, 24);
    float3 pos = coordinator.GetComponent<CTransform>(map[randX(Game::generator)][randY(Game::generator)]).position;
    return float3(pos.x, pos.y, 0);
}

float3 Map::TileToWorldSpace(const int& x, const int& y)
{
    return float3((x - y) * 40, (y + x) * 20, 0);
}

float3 Map::TileToWorldSpace(const float3& position)
{
    return TileToWorldSpace(position.x, position.y);
}

int2 Map::WorldToTileSpace(const float3& position)
{
    return int2(
                (int)((position.x / 40 + position.y / 20) / 2),
                (int)(position.y / 20 - (position.x / 40 + position.y / 20) / 2)
                );
}

bool Map::TileAt(Entity& tile, const float3& position)
{
    int2 location = WorldToTileSpace(position);
    if (location.x >= 0 && location.x < 25 && location.y >= 0 && location.y < 25)
    {
        tile = map[location.x][location.y];
        return true;
    }
    return false;
}


bool Map::FindPath(std::vector<Entity>& Path, Entity& start, Entity& dest)
{
    CTile* startTile = &coordinator.GetComponent<CTile>(start);
    CTile* destTile = &coordinator.GetComponent<CTile>(dest);
    if (!destTile->bIsWalkable || startTile->position == destTile->position)
        return false;
    bool checkedList[25][25] = { false };

    std::array<std::array<Node, 25>, 25> allMap;
    for (int x = 0; x < 25; x++)
    {
        for (int y = 0; y < 25; y++)
        {
            allMap[x][y].tile = &map[x][y];
            
        }
    }

    allMap[startTile->position.x][startTile->position.y].gCost = 0.0f;
    allMap[startTile->position.x][startTile->position.y].hCost = 0.0f;
    allMap[startTile->position.x][startTile->position.y].fCost = 0.0f;
    allMap[startTile->position.x][startTile->position.y].tile = &start;

    std::vector<Node> openList;
    openList.emplace_back(allMap[startTile->position.x][startTile->position.y]);
    Node curNode;
    int2 *pos;
    while (!openList.empty() && openList.size() < 25 * 25)
    {
        do
        {
            float temp = __FLT_MAX__;
            std::vector<Node>::iterator iterNode;
            for (std::vector<Node>::iterator it = openList.begin(); it != openList.end(); it = next(it))
            {
                Node nextNode = *it;
                if (nextNode.fCost < temp)
                {
                    temp = nextNode.fCost;
                    iterNode = it;
                }
            }
            curNode = *iterNode;
            openList.erase(iterNode);
        } while (!coordinator.GetComponent<CTile>(*curNode.tile).bIsWalkable);
        
        pos = &coordinator.GetComponent<CTile>(*curNode.tile).position;
        checkedList[pos->x][pos->y] = true;

        //Check neighbors
        for (int xMod = -1; xMod <= 1; xMod++)
        {
            for (int yMod = -1; yMod <= 1; yMod++)
            {
                float gNew, hNew, fNew;
                CTile newTile = coordinator.GetComponent<CTile>(map[pos->x+xMod][pos->y+yMod]);
                if (newTile.bIsWalkable)
                {
                    // If dest, make path and return true
                    if (dest == map[pos->x+xMod][pos->y+yMod])
                    {
                        allMap[pos->x+xMod][pos->y+xMod].prevTile = curNode.tile; 
                        Path = MakePath(allMap, dest);
                        return true;
                    }
                    // If curNode not checked yet, find costs
                    else if (checkedList[pos->x+xMod][pos->y+yMod] == false)
                    {
                        gNew = curNode.gCost + 1.0f;
                        hNew = newTile.position.DistanceTo(destTile->position);
                        fNew = gNew + hNew;

                        // If better than old cost
                        if (allMap[pos->x+xMod][pos->y+yMod].fCost == __FLT_MAX__ ||
                            allMap[pos->x+xMod][pos->y+yMod].fCost > fNew)
                        {
                            allMap[pos->x+xMod][pos->y+yMod].gCost = gNew;
                            allMap[pos->x+xMod][pos->y+yMod].hCost = hNew;
                            allMap[pos->x+xMod][pos->y+yMod].fCost = fNew;
                            allMap[pos->x+xMod][pos->y+yMod].prevTile = curNode.tile;
                            openList.emplace_back(allMap[pos->x+xMod][pos->y+yMod]);
                        }
                    }
                }
            }
        }
    }
    return false;
}

std::vector<Entity> Map::MakePath(std::array<std::array<Node, 25>, 25> allMap, Entity& dest)
{
    CTile* destTile = &coordinator.GetComponent<CTile>(dest);
    int2* pos = &destTile->position;
    std::stack<Node> path;
    std::vector<Entity> usablePath;

    while (allMap[pos->x][pos->y].tile && coordinator.GetComponent<CTile>(*allMap[pos->x][pos->y].prevTile).position != destTile->position)
    {
        path.push(allMap[pos->x][pos->y]);
        pos = &coordinator.GetComponent<CTile>(*allMap[pos->x][pos->y].prevTile).position;
    }
    path.push(allMap[pos->x][pos->y]);

    while (!path.empty())
    {
        Node top = path.top();
        path.pop();
        usablePath.emplace_back(*top.tile);
    }
    return usablePath;
}
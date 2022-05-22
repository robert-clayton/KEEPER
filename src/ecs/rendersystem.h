#pragma once
#include "ecs.h"
#include "components.h"
#include <SDL_image.h>
#include <map>
#include <set>

class SRenderer : public System
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::map<std::string, SDL_Texture*> textures;
    std::map<int, std::map<int, std::set<CSprite*>>> renderLayers;
    std::string assetPath = "res/";

public:
    void Update(const float deltaSeconds);
    void UpdateSpritePositions(const std::vector<Entity> entityVec);
    void CreateWindowRenderer(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
    SDL_Texture* LoadTexture(const char* fileName);
    int GetTextureCount(const char* fileName, int tileWidth);
    void DrawTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, bool flip = false);
    void Clean();
    void SetZoom(float zoom);
};

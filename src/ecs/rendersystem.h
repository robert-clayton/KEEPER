#pragma once
#include "ecs.h"
#include "components.h"
#include <SDL2/SDL_image.h>

class SRenderer : public System
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    void Update(float deltaSeconds);

    void CreateWindowRenderer(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
    SDL_Texture* LoadTexture(const char *fileName);
    void DrawTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Clean();
    void SetZoom(float zoom);
    Vector2D WorldToScreenSpace(Vector2D position);
};

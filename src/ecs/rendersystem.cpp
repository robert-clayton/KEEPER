#include "rendersystem.h"
#include "../game.h"
#include <algorithm>
#include <SDL_image.h>

extern Coordinator coordinator;

void SRenderer::Update(float deltaSeconds)
{
    (void)deltaSeconds;
    SDL_RenderClear(renderer);
    for (auto const& entity : entities)
    {
        auto& transform = coordinator.GetComponent<CTransform>(entity);
        auto& sprite = coordinator.GetComponent<CSprite>(entity);

        if (transform.bIsDirty || Game::camera.bIsDirty)
        {
            sprite.dest.x = transform.position.x
                    + sprite.renderOffset.x
                    - sprite.dest.w / 2
                    - Game::camera.position.x;
            sprite.dest.y = transform.position.y
                    + sprite.renderOffset.y
                    + transform.position.z
                    - sprite.dest.h / 2
                    - Game::camera.position.y;
            transform.bIsDirty = false;
        }
        DrawTexture(sprite.texture, sprite.src, sprite.dest);
    }
    if (Game::camera.bIsDirty)
    {
        SetZoom(Game::camera.zoom);
        Game::camera.bIsDirty = false;
    }
    SDL_RenderPresent(renderer);
}

void SRenderer::CreateWindowRenderer(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
    window = SDL_CreateWindow(title, xPos, yPos, width, height, SDL_WINDOW_FULLSCREEN * fullscreen);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

SDL_Texture* SRenderer::LoadTexture(const char *fileName)
{
    std::string assetPath = "E:/Repos/KEEPER/assets/";
    assetPath += fileName;
    SDL_Surface* tempSurface = IMG_Load(assetPath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    assert(texture && "Texture unable to be loaded!");
    return texture;
}

void SRenderer::DrawTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
    (void)flip;
    SDL_RenderCopy(renderer, tex, &src, &dest);
}

void SRenderer::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void SRenderer::SetZoom(float zoom)
{
    SDL_RenderSetScale(renderer, zoom, zoom);
}

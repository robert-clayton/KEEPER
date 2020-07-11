#pragma once
#include "ecs.h"
#include "components.h"
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <iostream>

extern Coordinator coordinator;

class SRenderer : public System
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    static bool LayerComparison(const CTransform& a, const CTransform& b)
    {
        return a.layer < b.layer;
    }

public:
    void Update(float deltaSeconds)
    {
        (void)deltaSeconds;
        SDL_RenderClear(renderer);

        for (auto const& entity : entities)
        {
            auto& transform = coordinator.GetComponent<CTransform>(entity);
            auto& sprite = coordinator.GetComponent<CSprite>(entity);
            sprite.dest.x = transform.position.x;
            sprite.dest.y = transform.position.y;
            DrawTexture(sprite.texture, sprite.src, sprite.dest);
        }
        SDL_RenderPresent(renderer);
    }

    void CreateWindowRenderer(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
    {
        window = SDL_CreateWindow(title, xPos, yPos, width, height, SDL_WINDOW_FULLSCREEN * fullscreen);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }

    SDL_Texture* LoadTexture(const char *fileName)
    {
        std::string assetPath = "/home/robert/Documents/Repos/djd/assets/";
        assetPath += fileName;
        SDL_Surface* tempSurface = IMG_Load(assetPath.c_str());
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
        return texture;
    }

    void DrawTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip = SDL_FLIP_NONE)
    {
        (void)flip;
        SDL_RenderCopy(renderer, tex, &src, &dest);
    }

    void Clean()
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
    }

};

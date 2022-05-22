#include "rendersystem.h"
#include "../game.h"
#include <fstream>
#include <SDL_render.h>

extern Coordinator coordinator;

void SRenderer::Update(const float deltaSeconds)
{
    (void)deltaSeconds;
    SDL_RenderClear(renderer);
    renderLayers.clear();
    

    const auto& chunkedEntities = Game::SplitVectorToNChunks(
        std::vector<Entity>{entities.begin(), entities.end()},
        std::thread::hardware_concurrency()
    );
    for (const auto& entityVec : chunkedEntities)
        futures.push_back(Game::threadPool.enqueue([&] { UpdateSpritePositions(entityVec); }));
    for (auto& fut : futures)
        fut.get();
    futures.clear();

    for (const auto& layer : renderLayers)
        for (const auto& sublayer : layer.second)
            for (const auto& sprite : sublayer.second)
                DrawTexture(sprite->sheet, sprite->sprites[sprite->activeSpriteKey], sprite->dest, sprite->activeSpriteKey > 4);
    
    if (Game::camera.bIsDirty)
    {
        SetZoom(Game::camera.zoom);
        Game::camera.bIsDirty = false;
    }

    SDL_RenderPresent(renderer);
}

void SRenderer::UpdateSpritePositions(const std::vector<Entity> entityVec)
{
    for (const auto& entity : entityVec)
    {
        auto& transform = coordinator.GetComponent<CTransform>(entity);
        auto& sprite = coordinator.GetComponent<CSprite>(entity);

        if (transform.bIsDirty || Game::camera.bIsDirty)
        {
            sprite.dest.x = transform.position.x
                + sprite.renderOffset.x
                - Game::camera.position.x;
            sprite.dest.y = transform.position.y
                + sprite.renderOffset.y
                + transform.position.z
                - Game::camera.position.y;
            transform.bIsDirty = false;
        }
        mtx.lock();
        renderLayers[sprite.renderLayer][sprite.dest.y].insert(&sprite);
        mtx.unlock();
    }
}

void SRenderer::CreateWindowRenderer(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
    window = SDL_CreateWindow(title, xPos, yPos, width, height, SDL_WINDOW_FULLSCREEN * fullscreen);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

SDL_Texture* SRenderer::LoadTexture(const char *fileName)
{
    std::string fullPath = assetPath + fileName;
    if (textures.count(fullPath))
        return textures[fullPath];
    
    SDL_Surface* tempSurface = IMG_Load(fullPath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    textures[fullPath] = texture;
    SDL_FreeSurface(tempSurface);

    assert(texture && "Texture unable to be loaded!");
    return texture;
}

void SRenderer::DrawTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, bool flip)
{
    if (flip)
        SDL_RenderCopyEx(renderer, tex, &src, &dest, 0.0f, nullptr, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopy(renderer, tex, &src, &dest);
}

void SRenderer::Clean()
{
    for (auto texturePair: textures)
        SDL_DestroyTexture(texturePair.second);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void SRenderer::SetZoom(float zoom)
{
    SDL_RenderSetScale(renderer, zoom, zoom);
}


int SRenderer::GetTextureCount(const char* fileName, int tileWidth)
{
    SDL_Texture* texture;
    std::string fullPath = assetPath + fileName;
    std::ifstream file(fullPath);
    unsigned int width, height;
    file.seekg(16);
    file.read((char*)&width, 4);
    file.read((char*)&height, 4);
    // width = ntohl(width);
    // height = ntohl(height);
    SDL_Log("%d %d -> %d sprites on sheet at %s", width, height, width / tileWidth, fullPath.c_str());
    return width / tileWidth;
}
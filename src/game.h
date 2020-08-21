#pragma once

#include <SDL.h>
#include <map>
#include <functional>
#include <vector>
#include <random>
#include "ecs/systems.h"
#include "threadpool.h"

using EventCallback = std::function<void(SDL_Event const&)>;

struct Camera
{
    float2 position;
    float zoom;
    bool bIsDirty;
};

class Game
{
private:
    bool bIsMouseButtonDown = false;
    bool bIsDragging = false;
public:
    static std::shared_ptr<SRenderer> sRenderer;
    static std::shared_ptr<SController> sController;
    static std::shared_ptr<SAnimation> sAnimation;
    static std::map<SDL_EventType, std::vector<EventCallback>> registeredCallbacks;
    static std::default_random_engine generator;
    static bool bIsRunning;
    static std::unique_ptr<class Map> map;
    static Camera camera;
    static ThreadPool threadPool;

    void Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
    void Update(float deltaSeconds);
    void Render(float deltaSeconds);
    void Clean();
    void HandleEvents();
    static void RegisterEvent(SDL_EventType type, EventCallback callback);
    static float GetRandomScalar(float max = 1.0f);
    static float2 ScreenToWorldSpace(const class float2& position);
    static float2 MouseEventToWorldSpace(const SDL_Event& event);
    
    template<typename T>
    static std::vector<std::vector<T>> SplitVectorToNChunks(const std::vector<T>& vec, size_t n);
    
    template<typename T>
    static std::vector<std::vector<T>> ChunkVectorToSize(const std::vector<T>& source, size_t chunkSize);
};

template<typename T>
inline std::vector<std::vector<T>> Game::ChunkVectorToSize(const std::vector<T>& source, size_t chunkSize)
{
    std::vector<std::vector<T>> result;
    result.reserve((source.size() + chunkSize - 1) / chunkSize);

    auto start = source.begin();
    auto end = source.end();

    while (start != end) {
        auto next = std::distance(start, end) >= chunkSize
            ? start + chunkSize
            : end;

        result.emplace_back(start, next);
        start = next;
    }
    return result;
}

template<typename T>
inline std::vector<std::vector<T>> Game::SplitVectorToNChunks(const std::vector<T>& vec, size_t n)
{
    std::vector<std::vector<T>> outVec;
    size_t length = vec.size() / n;
    size_t remain = vec.size() % n;

    size_t begin = 0;
    size_t end = 0;

    for (size_t i = 0; i < std::min(n, vec.size()); ++i)
    {
        end += (remain > 0) ? (length + !!(remain--)) : length;
        outVec.push_back(std::vector<T>(vec.begin() + begin, vec.begin() + end));
        begin = end;
    }
    return outVec;
}

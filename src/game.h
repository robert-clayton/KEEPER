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
};

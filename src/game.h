#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <functional>
#include <vector>
#include <random>
#include "ecs/systems.h"

using EventCallback = std::function<void(SDL_Event const&)>;

struct Camera
{
    Vector2D position;
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

    void Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
    void Update(float deltaSeconds);
    void Render(float deltaSeconds);
    void Clean();
    void HandleEvents();
    static void RegisterEvent(SDL_EventType type, EventCallback callback);
    static Vector2D ScreenToWorldSpace(const class Vector2D& position);
    static Vector2D MouseEventToWorldSpace(const SDL_Event& event);
};

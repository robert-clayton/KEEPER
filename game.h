#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <functional>
#include <vector>
#include "ecs/systems.h"

using EventCallback = std::function<void(SDL_Event const&)>;

class Game
{
public:
    static std::shared_ptr<SRenderer> sRenderer;
    static std::shared_ptr<SController> sController;
    static std::map<SDL_EventType, std::vector<EventCallback>> registeredCallbacks;
    static bool bIsRunning;
    static SDL_Rect camera;

    void Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
    void Update(float deltaSeconds);
    void Render(float deltaSeconds);
    void Clean();
    void HandleEvents();
    static void RegisterEvent(SDL_EventType type, EventCallback callback);
};
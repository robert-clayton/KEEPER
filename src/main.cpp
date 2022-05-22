#include "game.h"
#include <iostream>
#include <emscripten.h>
#include <SDL.h>

Game *game = nullptr;
float deltaSeconds = 0.0f;

void runMainLoop()
{
    if (!game->bIsRunning)
    {
        game->Clean();
        emscripten_cancel_main_loop();
    }
    Uint32 frameStart = SDL_GetTicks();

    game->HandleEvents();
    game->Update(deltaSeconds);
    game->Render(deltaSeconds);

    Uint32 frameDifference = SDL_GetTicks() - frameStart;
    deltaSeconds = frameDifference / 1000.0f;
}

void runApplication()
{
    game = new Game();
    game->Init("KEEPER", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, false);
    emscripten_set_main_loop(runMainLoop, 60, 1);
}

int main(int argv, char** args)
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0)
    {
        std::cout << "Successfully initialized SDL!" << std::endl;
        runApplication();
    }
    else
        std::cout << "Failed to initialize SDL!" << std::endl;

    return 0;
}

#include "game.h"
#include <iostream>

Game *game = nullptr;

int main()
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    Uint32 frameDifference;
    float deltaSeconds = 0.0f;

    game = new Game();
    game->Init("Keeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, false);
    while (game->bIsRunning)
    {
        frameStart = SDL_GetTicks();

        game->HandleEvents();
        game->Update(deltaSeconds);
        game->Render(deltaSeconds);

        frameDifference = SDL_GetTicks() - frameStart;
        if (frameDelay > frameDifference)
        {
            SDL_Delay(frameDelay - frameDifference);
            deltaSeconds = (frameDelay - frameDifference) / 1000.0f;
        }
        else
            deltaSeconds = frameDifference / 1000.0f;
        std::cout << frameDifference << "ms" << std::endl;
    }
    game->Clean();
    return 0;
}

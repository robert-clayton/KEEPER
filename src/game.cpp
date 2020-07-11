#include "game.h"
#include <SDL2/SDL_image.h>
#include "ecs/components.h"
#include "ecs/systems.h"
#include "ecs/ecs.h"
#include <random>
#include <map.h>

using EventCallback = std::function<void(SDL_Event const&)>;

Coordinator coordinator;
std::shared_ptr<SRenderer> Game::sRenderer;
std::shared_ptr<SController> Game::sController;
std::map<SDL_EventType, std::vector<EventCallback>> Game::registeredCallbacks;
bool Game::bIsRunning = false;
SDL_Rect Game::camera;;

void Game::Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
    camera = {0,0,width,height};
    // ECS
    coordinator.Init();
    coordinator.RegisterComponent<CTransform>();
    coordinator.RegisterComponent<CSprite>();
    coordinator.RegisterComponent<CStats>();
    coordinator.RegisterComponent<CAIController>();
    sController = coordinator.RegisterSystem<SController>();
    sRenderer = coordinator.RegisterSystem<SRenderer>();

    // SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        sRenderer->CreateWindowRenderer(title, xPos, yPos, width, height, fullscreen);
        bIsRunning = true;
    }
    else
        bIsRunning = false;

    // Event registering
    RegisterEvent(SDL_QUIT, [](SDL_Event const& event){
        (void)event;
        bIsRunning = false;
    });
    RegisterEvent(SDL_KEYUP, [](SDL_Event const& event){
        if (event.key.keysym.sym == SDLK_ESCAPE)
            bIsRunning = false;
    });


    Signature signature;
    signature.set(coordinator.GetComponentType<CTransform>());
    signature.set(coordinator.GetComponentType<CAIController>());
    signature.set(coordinator.GetComponentType<CStats>());
    coordinator.SetSystemSignature<SController>(signature);

    signature.reset();
    signature.set(coordinator.GetComponentType<CTransform>());
    signature.set(coordinator.GetComponentType<CSprite>());
    coordinator.SetSystemSignature<SRenderer>(signature);

    std::vector<Entity> entities(100);
    std::default_random_engine generator;
    std::uniform_real_distribution<float> randPosX(0.0f, width);
    std::uniform_real_distribution<float> randPosY(0.0f, height);
    std::uniform_int_distribution<int> randInt(0, 1);
    for (auto& entity : entities)
    {
        entity = coordinator.CreateEntity();
        coordinator.AddComponent(entity, CAIController{
                    .bIsActive = true,
                    .bIsMoving = false,
                    .targetPosition = Vector2D()
                    });
        coordinator.AddComponent(entity, CStats{
                    .health = 100,
                    .mana = 0,
                    .ki = 0,
                    .stamina = 100,
                    .speed = 5
                    });
        coordinator.AddComponent(
                    entity,
                    CTransform{
                        .position = Vector2D(randPosX(generator), randPosY(generator)),
                        .scale = Vector2D(1,1),
                        .layer = 1
                    });

        coordinator.AddComponent(
                    entity,
                    CSprite{
                        .texture = sRenderer->LoadTexture("deer_sheet.png"),
                        .src = SDL_Rect{
                            .x = 0,
                            .y = 0,
                            .w = 8,
                            .h = 8
                        },
                        .dest = SDL_Rect{
                            .x = 0,
                            .y = 0,
                            .w = 40,
                            .h = 40,
                        }
                    });
    }
}

void Game::RegisterEvent(SDL_EventType type, EventCallback callback)
{
    registeredCallbacks[type].push_back(callback);
}

void Game::HandleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        for (EventCallback& callback : registeredCallbacks[static_cast<SDL_EventType>(event.type)])
            callback(event);
    }
}

void Game::Update(float deltaSeconds)
{
    sController->Update(deltaSeconds);
}

void Game::Render(float deltaSeconds)
{
    sRenderer->Update(deltaSeconds);
}

void Game::Clean()
{
    sRenderer->Clean();
    SDL_Quit();
    std::cout << "Game Cleaned!" << std::endl;
}

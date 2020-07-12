#include "game.h"
#include <SDL2/SDL_image.h>
#include "ecs/components.h"
#include "ecs/systems.h"
#include "ecs/ecs.h"
#include <random>
#include <map.h>

using EventCallback = std::function<void(SDL_Event const&)>;

Coordinator coordinator;
Camera Game::camera;
std::shared_ptr<SRenderer> Game::sRenderer;
std::shared_ptr<SController> Game::sController;
std::map<SDL_EventType, std::vector<EventCallback>> Game::registeredCallbacks;
std::default_random_engine Game::generator;
std::unique_ptr<Map> Game::map;
bool Game::bIsRunning = false;

void Game::Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
//    camera = {Vector2D(-width, 0), 1, true};
    camera = {Vector2D(0, 0), 1, true};
    // ECS
    coordinator.Init();
    coordinator.RegisterComponent<CTransform>();
    coordinator.RegisterComponent<CSprite>();
    coordinator.RegisterComponent<CStats>();
    coordinator.RegisterComponent<CAIController>();
    coordinator.RegisterComponent<CTile>();
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

    // Event registration
    RegisterEvent(SDL_QUIT, [](SDL_Event const& event){
        (void)event;
        bIsRunning = false;
    });
    RegisterEvent(SDL_MOUSEBUTTONDOWN, [this](SDL_Event const& event){
        (void)event;
        this->bIsMouseButtonDown = true;
    });
    RegisterEvent(SDL_MOUSEBUTTONUP, [this](SDL_Event const& event){
        if (!this->bIsDragging)
            std::cout << coordinator.GetComponent<CTile>(*map->TileAt(ScreenToWorldSpace(Vector2D(event.motion.x, event.motion.y)))).position << std::endl;
        this->bIsMouseButtonDown = false;
        this->bIsDragging = false;
    });
    RegisterEvent(SDL_MOUSEMOTION, [this](SDL_Event const& event){
        camera.position += Vector2D(-event.motion.xrel, -event.motion.yrel) / camera.zoom * bIsMouseButtonDown;
        camera.bIsDirty = (camera.bIsDirty && !bIsMouseButtonDown) || bIsMouseButtonDown;
        this->bIsDragging = bIsMouseButtonDown;
    });
    RegisterEvent(SDL_MOUSEWHEEL, [](SDL_Event const& event){
        camera.zoom *= (.9 * (float)(event.wheel.y < 0)) + (1.1 * (float)(event.wheel.y > 0));
        camera.bIsDirty = true;
    });
    RegisterEvent(SDL_KEYDOWN, [](SDL_Event const& event){
        switch(event.key.keysym.sym)
        {
        case SDLK_w:
            camera.position.y -= 100;
            camera.bIsDirty = true;
            break;
        case SDLK_s:
            camera.position.y += 100;
            camera.bIsDirty = true;
            break;
        case SDLK_a:
            camera.position.x -= 100;
            camera.bIsDirty = true;
            break;
        case SDLK_d:
            camera.position.x += 100;
            camera.bIsDirty = true;
            break;
        default:
            break;
        }
    });
    RegisterEvent(SDL_KEYUP, [](SDL_Event const& event){
        switch(event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            bIsRunning = false;
            break;
        default:
            break;
        }
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

    map = coordinator.make_unique<Map>();

    std::vector<Entity> entities(1);
    for (auto& entity : entities)
    {
        entity = coordinator.CreateEntity();
        coordinator.AddComponent(entity, CAIController{
                    .bIsActive = true,
                    .bIsMoving = false
                    });
        coordinator.AddComponent(entity, CStats{
                    .health = 100,
                    .mana = 0,
                    .ki = 0,
                    .stamina = 100,
                    .speed = 50
                    });
        coordinator.AddComponent(entity, CTransform(map->GetRandomTilePos()));
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

Vector2D Game::ScreenToWorldSpace(const Vector2D& position)
{
    return (position / camera.zoom) + camera.position;
}

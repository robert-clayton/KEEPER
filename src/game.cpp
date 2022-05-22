#include "game.h"
#include <SDL_image.h>
#include "ecs/components.h"
#include "ecs/systems.h"
#include "ecs/ecs.h"
#include "math/float2.h"
#include <vector>
#include <random>
#include "map.h"

using EventCallback = std::function<void(SDL_Event const&)>;

Coordinator coordinator;
Camera Game::camera;
std::shared_ptr<SRenderer> Game::sRenderer;
std::shared_ptr<SController> Game::sController;
std::shared_ptr<SAnimation> Game::sAnimation;
std::map<SDL_EventType, std::vector<EventCallback>> Game::registeredCallbacks;
std::default_random_engine Game::generator;
std::unique_ptr<Map> Game::map;
ThreadPool Game::threadPool;
bool Game::bIsRunning = false;

void Game::Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{

    camera = {float2(0, 0), 1, true};
    // ECS
    coordinator.Init();
    coordinator.RegisterComponent<CTransform>();
    coordinator.RegisterComponent<CSprite>();
    coordinator.RegisterComponent<CStats>();
    coordinator.RegisterComponent<CAIController>();
    coordinator.RegisterComponent<CTile>();
    sController = coordinator.RegisterSystem<SController>();
    sAnimation = coordinator.RegisterSystem<SAnimation>();
    sRenderer = coordinator.RegisterSystem<SRenderer>();

    // SDL
    
    sRenderer->CreateWindowRenderer(title, xPos, yPos, width, height, fullscreen);
    bIsRunning = true;

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
        {
            Entity tile;
            bool bTileExists = map->TileAt(tile, ScreenToWorldSpace(float2((float)event.motion.x, (float)event.motion.y)));
            if (bTileExists)
            {
                coordinator.GetComponent<CSprite>(tile).sheet = map->textures.at(1);
            }
        }
        this->bIsMouseButtonDown = false;
        this->bIsDragging = false;
    });
    
    RegisterEvent(SDL_MOUSEMOTION, [this](SDL_Event const& event){
        camera.position += float2((float)-event.motion.xrel, (float)-event.motion.yrel) / camera.zoom * bIsMouseButtonDown;
        camera.bIsDirty = (camera.bIsDirty && !bIsMouseButtonDown) || bIsMouseButtonDown;
        this->bIsDragging = bIsMouseButtonDown;
    });
    RegisterEvent(SDL_MOUSEWHEEL, [](SDL_Event const& event){
        camera.zoom *= (.9f * (float)(event.wheel.y < 0)) + (1.1f * (float)(event.wheel.y > 0));
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
    signature.set(coordinator.GetComponentType<CSprite>());
    signature.set(coordinator.GetComponentType<CAIController>());
    coordinator.SetSystemSignature<SAnimation>(signature);

    signature.reset();
    signature.set(coordinator.GetComponentType<CTransform>());
    signature.set(coordinator.GetComponentType<CSprite>());
    coordinator.SetSystemSignature<SRenderer>(signature);

    map = coordinator.make_unique<Map>();

    std::vector<Entity> entities(10);
    for (auto& entity : entities)
    {
        entity = coordinator.CreateEntity();
        coordinator.AddComponent(entity, CStats());
        Entity tile = map->GetRandomTile();
        while (!coordinator.GetComponent<CTile>(tile).bIsWalkable)
            tile = map->GetRandomTile();
        coordinator.AddComponent(entity, CTransform(coordinator.GetComponent<CTransform>(tile).position));
        coordinator.AddComponent(entity, CSprite(
            sRenderer->LoadTexture("char.png"),
            SDL_Rect{ 0, 0, 100, 300 },
            SDL_Rect{ 0, 0, 25, 50 },
            int2(), 1
        ));
        coordinator.GetComponent<CTile>(tile).entities.emplace(entity);
        coordinator.AddComponent(entity, CAIController(tile));
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
    sAnimation->Update(deltaSeconds);
}

void Game::Render(float deltaSeconds)
{
    sRenderer->Update(deltaSeconds);
}

void Game::Clean()
{
    sRenderer->Clean();
    SDL_Log("Game cleaned!");
    SDL_Quit();
}

float Game::GetRandomScalar(float max)
{
    return static_cast<float>(rand()) / (static_cast<float> (RAND_MAX) / max);
}

float2 Game::ScreenToWorldSpace(const float2& position)
{
    return (position / camera.zoom) + camera.position;
}

float2 Game::MouseEventToWorldSpace(const SDL_Event& event)
{
    return ScreenToWorldSpace(float2((float)event.motion.x, (float)event.motion.y));
}

#include "controllersystem.h"
#include "components.h"
#include "../game.h"
#include "../map.h"
#include <vector>


void SController::Update(const float deltaSeconds)
{
    const auto& chunkedEntities = Game::SplitVectorToNChunks(
        std::vector<Entity>{entities.begin(), entities.end()}, 
        std::thread::hardware_concurrency()
    );
    for (const auto& entityVec : chunkedEntities)
        DoMovement(entityVec, deltaSeconds);
    //     futures.push_back(Game::threadPool.enqueue([&] { DoMovement(entityVec, deltaSeconds); }));
    // for (auto& fut : futures)
    //     fut.get();
    // futures.clear();    
}

const void SController::DoMovement(const std::vector<Entity>& entityVec, const float deltaSeconds)
{
    for (const auto& entity : entityVec)
    {
        auto& transform = coordinator.GetComponent<CTransform>(entity);
        auto& aiController = coordinator.GetComponent<CAIController>(entity);
        auto& stats = coordinator.GetComponent<CStats>(entity);

        if (!aiController.bIsMoving)
        {
            // Get new path if needed
            if (aiController.movePath.empty())
                if (!Game::map->FindPath(aiController.movePath, aiController.tile, Game::map->GetRandomTile()))
                    return;

            // Get next tile in path and start moving to it
            aiController.direction = GetDirectionValue(aiController.tile, aiController.movePath.front());
            mtx.lock();
            coordinator.GetComponent<CTile>(aiController.tile).entities.erase(entity);
            aiController.tile = aiController.movePath.front();
            aiController.movePath.erase(aiController.movePath.begin());
            coordinator.GetComponent<CTile>(aiController.tile).entities.emplace(entity);
            mtx.unlock();
            aiController.moveDirection = transform.position.DirectionTo(
                coordinator.GetComponent<CTransform>(aiController.tile).position);

            aiController.bIsMoving = true;
        }
        if (transform.position.DistanceTo(coordinator.GetComponent<CTransform>(aiController.tile).position) < stats.speed * deltaSeconds)
        {
            aiController.bIsMoving = false;
            aiController.moveDirection.Zero();
            transform.position = coordinator.GetComponent<CTransform>(aiController.tile).position;
        }
        else
        {
            transform.position += aiController.moveDirection * stats.speed * deltaSeconds;
            transform.bIsDirty = true;
        }
    }
}

const int SController::GetDirectionValue(Entity src, Entity dest)
{
    int2 srcPos = coordinator.GetComponent<CTile>(src).position;
    int2 destPos = coordinator.GetComponent<CTile>(dest).position;

    if (srcPos.x == destPos.x && srcPos.y < destPos.y) // Visual down right
        return 7;
    if (srcPos.x == destPos.x && srcPos.y > destPos.y) // Visual up right
        return 3;
    
    if (srcPos.x > destPos.x && srcPos.y > destPos.y) // Visual up
        return 4;
    if (srcPos.x > destPos.x && srcPos.y == destPos.y) // Visual up left
        return 5;
    if (srcPos.x > destPos.x && srcPos.y < destPos.y) // Visual right
        return 6;
    if (srcPos.x < destPos.x && srcPos.y > destPos.y) // Visual left
        return 2;
    if (srcPos.x < destPos.x && srcPos.y == destPos.y) // Visual down left
        return 1;
    if (srcPos.x < destPos.x && srcPos.y < destPos.y) // Visual down
        return 0;
    
    return 1;
}
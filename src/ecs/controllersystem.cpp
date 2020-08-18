#include "controllersystem.h"
#include "components.h"
#include "../game.h"
#include "../map.h"
#include <iostream>
#include <vector>

void SController::Update(float deltaSeconds)
{
    /*
    for (auto const& entity : entities)
        futures.push_back(Game::threadPool.enqueue([&] { DoMovement(entity, deltaSeconds); }));
    for (auto& fut : futures)
        fut.get();
    futures.clear();
    */
    for (auto const& entity : entities)
        DoMovement(entity, deltaSeconds);
}

void SController::DoMovement(const Entity entity, float deltaSeconds)
{
    auto& transform = coordinator.GetComponent<CTransform>(entity);
    auto& aiController = coordinator.GetComponent<CAIController>(entity);
    auto& stats = coordinator.GetComponent<CStats>(entity);
    
    if (!aiController.bIsMoving)
    {
        // Get new path if needed
        if (aiController.movePath.empty())
            if (!Game::map->FindPath(aiController.movePath, transform.tile, Game::map->GetRandomTile()))
                return;
        
        // Get next tile in path and start moving to it

        coordinator.GetComponent<CTile>(transform.tile).entities.erase(entity);
        transform.tile = aiController.movePath.front();
        aiController.movePath.erase(aiController.movePath.begin());
        coordinator.GetComponent<CTile>(transform.tile).entities.emplace(entity);
        aiController.moveDirection = transform.position.DirectionTo(
            coordinator.GetComponent<CTransform>(transform.tile).position);

        aiController.bIsMoving = true;
    }
    if (transform.position.DistanceTo(coordinator.GetComponent<CTransform>(transform.tile).position) < stats.speed * deltaSeconds)
    {
        aiController.bIsMoving = false;
        aiController.moveDirection.Zero();
        transform.position = coordinator.GetComponent<CTransform>(transform.tile).position;
    }
    else
    {
        transform.position += aiController.moveDirection * stats.speed * deltaSeconds;
        transform.bIsDirty = true;
    }
}
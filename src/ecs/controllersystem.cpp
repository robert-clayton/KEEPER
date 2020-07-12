#include "controllersystem.h"
#include "components.h"
#include "../game.h"
#include "../map.h"

void SController::Update(float deltaSeconds)
{
    for (auto const& entity : entities)
    {
        auto& transform = coordinator.GetComponent<CTransform>(entity);
        auto& aiController = coordinator.GetComponent<CAIController>(entity);
        auto& stats = coordinator.GetComponent<CStats>(entity);
        if (!aiController.bIsMoving)
        {
            aiController.targetPosition = Game::map->GetRandomTilePos();
            aiController.moveDirection = transform.position.DirectionTo(aiController.targetPosition);
            aiController.bIsMoving = true;
        }
        if (transform.position.DistanceTo(aiController.targetPosition) < stats.speed * deltaSeconds)
        {
            aiController.bIsMoving = false;
            aiController.moveDirection.Zero();
            transform.position = aiController.targetPosition;
        }
        else
        {
            transform.position += aiController.moveDirection * stats.speed * deltaSeconds;
            transform.bIsDirty = true;
        }
    }
}

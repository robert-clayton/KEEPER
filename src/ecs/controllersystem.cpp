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
            transform.tile = Game::map->GetRandomTile();
            aiController.moveDirection = transform.position.DirectionTo(
                        coordinator.GetComponent<CTransform>(*transform.tile).position);
            aiController.bIsMoving = true;
        }
        if (transform.position.DistanceTo(coordinator.GetComponent<CTransform>(*transform.tile).position) < stats.speed * deltaSeconds)
        {
            aiController.bIsMoving = false;
            aiController.moveDirection.Zero();
            transform.position = coordinator.GetComponent<CTransform>(*transform.tile).position;
        }
        else
        {
            transform.position += aiController.moveDirection * stats.speed * deltaSeconds;
            transform.bIsDirty = true;
        }
    }
}

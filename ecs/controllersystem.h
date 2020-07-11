#pragma once
#include "ecs.h"
#include <vector>
#include <cmath>
#include "components.h"
#include <random>

extern Coordinator coordinator;

class SController : public System
{
public:
    void Update(float deltaSeconds)
    {
        std::default_random_engine engine;
        std::uniform_real_distribution<float> newPos(-50, 50);
        for (auto const& entity : entities)
        {
            auto& transform = coordinator.GetComponent<CTransform>(entity);
            auto& aiController = coordinator.GetComponent<CAIController>(entity);
            auto& stats = coordinator.GetComponent<CStats>(entity);
            if (!aiController.bIsMoving)
            {
                aiController.targetPosition = Vector2D(
                            transform.position.x + newPos(engine),
                            transform.position.y + newPos(engine));
                aiController.bIsMoving = true;
            }
            Vector2D velocity = transform.position.DirectionTo(aiController.targetPosition) * stats.speed * deltaSeconds;
            transform.position += velocity;
        }
    }
};

#include "animationsystem.h"
#include "components.h"
#include "../game.h"

void SAnimation::Update(const float deltaSeconds)
{
    for (const Entity& entity : entities)
    {
        auto& sprite = coordinator.GetComponent<CSprite>(entity);
        auto& controller = coordinator.GetComponent<CAIController>(entity);

        sprite.activeSpriteKey = controller.direction;
    }
}

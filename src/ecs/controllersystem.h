#pragma once
#include "ecs.h"

extern Coordinator coordinator;

class SController : public System
{
public:
    void Update(const float deltaSeconds);
private:
    const void DoMovement(const std::vector<Entity>& entityVec, const float deltaSeconds);
    static const int GetDirectionValue(Entity src, Entity dest);
};

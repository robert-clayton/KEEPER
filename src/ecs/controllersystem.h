#pragma once
#include "ecs.h"

extern Coordinator coordinator;

class SController : public System
{
public:
    void Update(float deltaSeconds);
private:
    void DoMovement(const Entity entity, float deltaSeconds);
};

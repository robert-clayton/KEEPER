#pragma once
#include "ecs.h"
#include "../threadpool.h"
#include <future>

extern Coordinator coordinator;

class SController : public System
{
public:
    void Update(const float deltaSeconds);
private:
    std::vector<std::future<void>> futures;
    const void DoMovement(const std::vector<Entity>& entityVec, const float deltaSeconds);
    void DoMovement(const Entity entity, const float deltaSeconds);
};

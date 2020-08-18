#pragma once
#include "ecs.h"
#include "../threadpool.h"
#include <future>

extern Coordinator coordinator;

class SController : public System
{
public:
    void Update(float deltaSeconds);
private:
    std::vector<std::future<void>> futures;
    void DoMovement(const Entity entity, float deltaSeconds);
};

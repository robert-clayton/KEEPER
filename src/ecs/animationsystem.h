#pragma once
#include "ecs.h"
#include <vector>
#include <bitset>

class SAnimation : public System
{
public:
    void Update(const float deltaSeconds);
};

#pragma once

#include "global/definitions.hpp"

class PhysicsSystem
{
public:
    PhysicsSystem();
    ~PhysicsSystem();

    static void FixedUpdate();
};

// ORDER:
// 1) Apply force
// 2) Detect collision
// 3) Resolve collision
// 4) Correct position

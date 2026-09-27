#pragma once

#include "global/definitions.hpp"
#include "components/Collider/ColliderComponent.hpp"

class PhysicsSolver
{
public:
    PhysicsSolver();
    ~PhysicsSolver();

    static void ResolveCollision(CollisionManifold colMani);
    static void CorrectPosition(CollisionManifold colMani);
};

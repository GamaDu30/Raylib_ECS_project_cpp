#include "PhysicsSystem.hpp"
#include "components/RigidBodyComponent.hpp"
#include "components/Collider/ColliderComponent.hpp"
#include "global/gameObject.hpp"
#include "Physics/PhysicsSolver.hpp"

PhysicsSystem::PhysicsSystem()
{
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::FixedUpdate()
{
    // 1) Integrate forces of all RigidBody
    for (RigidBodyComponent *rb : ComponentBase::GetInstancesOfType<RigidBodyComponent>())
    {
        rb->IntegrateForces();
    }

    // 2) Apply forces of all Rigidbody
    for (RigidBodyComponent *rb : ComponentBase::GetInstancesOfType<RigidBodyComponent>())
    {
        rb->ApplyForces();
    }

    // 3) Get all collisions
    std::vector<CollisionManifold> colManifolds = ColliderComponent::GetAllCollisions();

    // 4) Resolve velocity
    for (CollisionManifold colMani : colManifolds)
    {
        PhysicsSolver::ResolveCollision(colMani);
    }

    // 5) Resolve positions
    for (CollisionManifold colMani : colManifolds)
    {
        PhysicsSolver::CorrectPosition(colMani);
    }
}
#include "PhysicsSolver.hpp"
#include "components/RigidBodyComponent.hpp"
#include "global/gameObject.hpp"

PhysicsSolver::PhysicsSolver()
{
}

PhysicsSolver::~PhysicsSolver()
{
}

void PhysicsSolver::ResolveCollision(CollisionManifold colMani)
{
    if (colMani.object1 == nullptr ||
        colMani.object2 == nullptr ||
        colMani.penetration < 0.0f)
    {
        return;
    }

    RigidBodyComponent *rb1 = colMani.object1->GetComponent<RigidBodyComponent>();
    RigidBodyComponent *rb2 = colMani.object2->GetComponent<RigidBodyComponent>();

    const float inverseMass1 = rb1 != nullptr && rb1->GetMass() > 0.0f
                                   ? 1.0f / rb1->GetMass()
                                   : 0.0f;
    const float inverseMass2 = rb2 != nullptr && rb2->GetMass() > 0.0f
                                   ? 1.0f / rb2->GetMass()
                                   : 0.0f;
    const float inverseMassSum = inverseMass1 + inverseMass2;

    if (inverseMassSum == 0.0f)
    {
        return;
    }

    const raylib::Vector2 velocity1 = rb1 != nullptr ? rb1->GetVelocity() : raylib::Vector2::Zero();
    const raylib::Vector2 velocity2 = rb2 != nullptr ? rb2->GetVelocity() : raylib::Vector2::Zero();
    const raylib::Vector2 relativeVelocity = velocity1 - velocity2;

    const float velocityAlongNormal =
        Vector2DotProduct(relativeVelocity, colMani.normal);

    // The normal is oriented from object2 toward object1.
    // A positive projection means the objects are already separating.
    if (velocityAlongNormal >= 0.0f)
    {
        return;
    }

    const float restitution = rb1 != nullptr && rb2 != nullptr
                                  ? std::min(rb1->GetRestitution(), rb2->GetRestitution())
                                  : 0.0f;

    const float impulseMagnitude =
        -(1.0f + restitution) * velocityAlongNormal / inverseMassSum;
    const raylib::Vector2 impulse = colMani.normal * impulseMagnitude;

    if (rb1 != nullptr)
    {
        rb1->SetVelocity(velocity1 + impulse * inverseMass1);
    }

    if (rb2 != nullptr)
    {
        rb2->SetVelocity(velocity2 - impulse * inverseMass2);
    }
}

void PhysicsSolver::CorrectPosition(CollisionManifold colMani)
{
    if (colMani.object1 == nullptr ||
        colMani.object2 == nullptr ||
        colMani.penetration <= 0.0f)
    {
        return;
    }

    RigidBodyComponent *rb1 = colMani.object1->GetComponent<RigidBodyComponent>();
    RigidBodyComponent *rb2 = colMani.object2->GetComponent<RigidBodyComponent>();

    const float inverseMass1 = rb1 != nullptr && rb1->GetMass() > 0.0f
                                   ? 1.0f / rb1->GetMass()
                                   : 0.0f;
    const float inverseMass2 = rb2 != nullptr && rb2->GetMass() > 0.0f
                                   ? 1.0f / rb2->GetMass()
                                   : 0.0f;
    const float inverseMassSum = inverseMass1 + inverseMass2;

    if (inverseMassSum == 0.0f)
    {
        return;
    }

    constexpr float penetrationSlop = 0.01f;
    constexpr float correctionPercent = 0.8f;

    const float correctionMagnitude =
        std::max(colMani.penetration - penetrationSlop, 0.0f) /
        inverseMassSum * correctionPercent;
    const raylib::Vector2 correction = colMani.normal * correctionMagnitude;

    if (inverseMass1 > 0.0f)
    {
        raylib::Vector3 &position1 = colMani.object1->GetTransform()->GetPos();
        position1 += raylib::Vector3(
            correction.x * inverseMass1,
            correction.y * inverseMass1,
            0.0f);
    }

    if (inverseMass2 > 0.0f)
    {
        raylib::Vector3 &position2 = colMani.object2->GetTransform()->GetPos();
        position2 -= raylib::Vector3(
            correction.x * inverseMass2,
            correction.y * inverseMass2,
            0.0f);
    }
}

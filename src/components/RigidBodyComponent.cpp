#include "RigidBodyComponent.hpp"
#include "global/gameObject.hpp"

RigidBodyComponent::RigidBodyComponent()
{
}

RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::Init(GameObject *owner)
{
    Component::Init(owner);
    m_transform = owner->GetTransform();
    UseGravity(true);
}

void RigidBodyComponent::OnUpdate()
{
}

void RigidBodyComponent::OnFixedUpdate()
{
    if (m_transform == nullptr)
    {
        return;
    }
}

void RigidBodyComponent::Destroy()
{
}

void RigidBodyComponent::IntegrateForces()
{
    float deltaTime = GetFrameTime();

    m_velocity += m_acceleration * deltaTime;

    if (m_momentOfInertia > 0.0f)
    {
        float angularAcceleration =
            m_torque / m_momentOfInertia;

        m_angularVelocity +=
            angularAcceleration * deltaTime;
    }

    m_angularVelocity *=
        1.0f / (1.0f + m_angularDrag * deltaTime);

    m_torque = 0.0f;
}

void RigidBodyComponent::ApplyForces()
{
    float deltaTime = GetFrameTime();

    m_transform->GetPos() += raylib::Vector3(
        m_velocity.x,
        m_velocity.y,
        0.0f);

    m_transform->GetRotation() +=
        m_angularVelocity;
}

void RigidBodyComponent::AddForce(raylib::Vector2 forceToAdd)
{
    m_velocity += forceToAdd;
}

void RigidBodyComponent::UseGravity(bool useGravity)
{
    m_hasGravity = useGravity;
    m_acceleration.y = m_hasGravity ? GRAVITY_FORCE : 0.f;
}

void RigidBodyComponent::SetVelocity(raylib::Vector2 velocity)
{
    m_velocity = velocity;
}

raylib::Vector2 RigidBodyComponent::GetVelocity()
{
    return m_velocity;
}

void RigidBodyComponent::SetAngularVelocity(float value)
{
    m_angularVelocity = value;
}

float RigidBodyComponent::GetAngularVelocity()
{
    return m_angularVelocity;
}

void RigidBodyComponent::SetMass(float value)
{
    m_mass = value;
}

float RigidBodyComponent::GetMass()
{
    return m_mass;
}

void RigidBodyComponent::SetRestitution(float value)
{
    m_restitution = value;
}

float RigidBodyComponent::GetRestitution()
{
    return m_restitution;
}

void RigidBodyComponent::AddTorque(float torque)
{
    m_torque += torque;
}

void RigidBodyComponent::SetMomentOfInertia(float value)
{
    m_momentOfInertia = value;
}

float RigidBodyComponent::GetMomentOfInertia()
{
    return m_momentOfInertia;
}
#pragma once

#include "Component.hpp"

class TransformComponent;

class RigidBodyComponent : public Component<RigidBodyComponent>
{
    bool m_hasGravity = true;
    float m_gravityScale = 1.f;

    raylib::Vector2 m_velocity = raylib::Vector2::Zero();
    raylib::Vector2 m_acceleration = raylib::Vector2::Zero();

    float m_angularVelocity = 0;
    float m_angularDrag = 0.f;

    float m_torque = 0.0f;
    float m_momentOfInertia = 1.0f;

    float m_mass = 1.f;
    float m_drag = 0.f;
    float m_restitution = 0.f;

    TransformComponent *m_transform;

public:
    RigidBodyComponent();
    ~RigidBodyComponent();

    virtual void Init(GameObject *owner) override;
    virtual void OnUpdate() override;
    virtual void OnFixedUpdate() override;
    virtual void Destroy() override;

    void IntegrateForces();
    void ApplyForces();

    void AddForce(raylib::Vector2 forceToAdd);

    void UseGravity(bool useGravity);

    void SetVelocity(raylib::Vector2 velocity);
    raylib::Vector2 GetVelocity();

    void SetAngularVelocity(float value);
    float GetAngularVelocity();

    void SetMass(float value);
    float GetMass();

    void SetRestitution(float value);
    float GetRestitution();

    void AddTorque(float torque);
    void SetMomentOfInertia(float value);
    float GetMomentOfInertia();
};

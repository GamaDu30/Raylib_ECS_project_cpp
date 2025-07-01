#pragma once
#include "global/definitions.hpp"
#include "global/gameObject.hpp"

class ColliderComponent;

class Bird : public GameObject
{
    float m_velocity;
    float m_velocityMax;
    float m_gravity;
    float m_jumpForce;
    float targetRotation;

public:
    Bird(std::string name = "") : GameObject(name) {}
    ~Bird() {}

    void Start() override;
    void Update() override;

    void OnCollisionEnter(ColliderComponent *collider) override;
};
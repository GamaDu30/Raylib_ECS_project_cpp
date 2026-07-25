#pragma once
#include "global/definitions.hpp"
#include "global/gameObject.hpp"
#include <cstdint>

class ColliderComponent;

class Bird : public GameObject
{
    float m_velocity;
    float m_velocityMax;
    float m_gravity;
    float m_jumpForce;
    float targetRotation;
    std::uint64_t m_jumpInputId = 0;

public:
    Bird(std::string name = "") : GameObject(name) {}
    ~Bird() override;

    void Start() override;
    void Update() override;

    void OnCollisionEnter(ColliderComponent *collider) override;
};
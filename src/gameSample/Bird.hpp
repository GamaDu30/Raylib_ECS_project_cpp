#pragma once
#include "global/definitions.hpp"
#include "global/gameObject.hpp"
#include "gameSample/GameManager.hpp"

class ColliderComponent;

class Bird : public GameObject
{
    float m_velocity;
    float m_velocityMax;
    float m_gravity;
    float m_jumpForce;
    float targetRotation;

public:
    Bird(std::string name = "");
    ~Bird() override;

    void Start() override;
    void Update() override;
    void Reset();

    void OnCollisionEnter(ColliderComponent *collider) override;

    void OnGameStateChange(GameState oldState, GameState newState);
};
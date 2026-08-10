#pragma once
#include "global/definitions.hpp"
#include "global/gameObject.hpp"
#include "gameSample/GameManager.hpp"

class ColliderComponent;
class CameraComponent;

enum BirdState
{
    ALIVE,
    DEAD
};

class Bird : public GameObject
{
    raylib::Vector2 m_velocity;
    float m_velocityMax;
    float m_gravity;
    float m_jumpForce;
    float targetRotation;

    BirdState m_state = BirdState::ALIVE;

public:
    Bird(std::string name = "");
    ~Bird() override;

    void Start() override;
    void Update() override;
    void Reset();

    void OnCollisionEnter(ColliderComponent *collider) override;

    void OnGameStateChange(GameState oldState, GameState newState);

    void Jump();
};